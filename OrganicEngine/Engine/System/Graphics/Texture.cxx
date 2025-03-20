#include "Texture.hxx"
#include "../../../Resource/DirectXTex/TextureLoad.h"
#include <d3d11.h>
#include <dxgi1_4.h>
#include <DirectXMath.h>
#include "GraphicsAPI.hxx"
//#include "../../Math/Vectors.hxx"
#include "../Window.hxx"

#pragma comment(lib, "d3d11.lib")

using namespace Engine::Graphic;

iTexture::iTexture()
	: m_width(0)
	, m_height(0)
{
}

DirectX11Texture::DirectX11Texture()
	: m_pSRV(nullptr)
	, m_pTex(nullptr)
{
}
DirectX11Texture::~DirectX11Texture()
{
	delete m_pTex;
	m_pTex = nullptr;
}
HRESULT DirectX11Texture::Create(const char* fileName)
{
	m_pSRV = TextureManager::GetInstance().LoadTexture(fileName);
	m_width = m_pSRV.get()->second.x;
	m_height = m_pSRV->second.y;
	return MB_OK;
}
HRESULT DirectX11Texture::Create(DXGI_FORMAT format, uint16 width, uint16 height, const void* pData)
{
	D3D11_TEXTURE2D_DESC desc = MakeTexDesc(format, width, height);
	return CreateResource(desc, pData);
}
D3D11_TEXTURE2D_DESC DirectX11Texture::MakeTexDesc(DXGI_FORMAT format, uint16 width, uint16 height)
{
	D3D11_TEXTURE2D_DESC desc = {};
	desc.Usage = D3D11_USAGE_DEFAULT;
	desc.Format = format;
	desc.BindFlags = D3D11_BIND_SHADER_RESOURCE;
	desc.Width = width;
	desc.Height = height;
	desc.MipLevels = 1;
	desc.ArraySize = 1;
	desc.SampleDesc.Count = 1;
	return desc;
}
HRESULT DirectX11Texture::CreateResource(D3D11_TEXTURE2D_DESC& desc, const void* pData)
{
	HRESULT hr = E_FAIL;
	m_pSRV.reset(new SRV_data);

	// テクスチャ作成
	D3D11_SUBRESOURCE_DATA data = {};
	data.pSysMem = pData;
	data.SysMemPitch = desc.Width * 4;
	hr = GraphicsManager::GetInstance()->GetDevice().p11D
		->CreateTexture2D(&desc, pData ? &data : nullptr, &m_pTex);
	if (FAILED(hr)) { return hr; }

	// 設定
	D3D11_SHADER_RESOURCE_VIEW_DESC srvDesc = {};
	switch (desc.Format)
	{
	default:						srvDesc.Format = desc.Format;			break;
	case DXGI_FORMAT_R32_TYPELESS: 	srvDesc.Format = DXGI_FORMAT_R32_FLOAT;	break;
	}
	srvDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
	srvDesc.Texture2D.MipLevels = 1;
	// 生成
	hr = GraphicsManager::GetInstance()->GetDevice().p11D
		->CreateShaderResourceView(m_pTex, &srvDesc, &m_pSRV->first.p11SRV);
	if (SUCCEEDED(hr))
	{
		m_width = desc.Width;
		m_height = desc.Height;
	}
	return hr;
}


DirectX11RenderTarget::DirectX11RenderTarget() 
	: m_pRTV(nullptr)
{

}
DirectX11RenderTarget::~DirectX11RenderTarget()
{
	delete m_pRTV;
	m_pRTV = nullptr;
}
void DirectX11RenderTarget::Clear()
{
	Math::fVec4 color = { 0.0f, 0.0f, 0.0f, 1.0f };
	Clear(color);
}
void DirectX11RenderTarget::Clear(const Math::fVec4& Color)
{
	GraphicsManager::GetInstance()->GetDeviceContext().p11DC->ClearRenderTargetView(m_pRTV, Color.v);
}
HRESULT DirectX11RenderTarget::Create(DXGI_FORMAT format, uint16 width, uint16 height)
{
	D3D11_TEXTURE2D_DESC desc = MakeTexDesc(format, width, height);
	desc.BindFlags |= D3D11_BIND_RENDER_TARGET;
	return CreateResource(desc);
}
HRESULT DirectX11RenderTarget::CreateFormScreen()
{
	HRESULT hr;

	// バックバッファのポインタを取得
	ID3D11Texture2D* pBackBuffer = NULL;
	hr = GraphicsManager::GetInstance()->GetSwapChain().p11SC->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&m_pTex);
	if (FAILED(hr)) { return hr; }

	// バックバッファへのポインタを指定してレンダーターゲットビューを作成
	D3D11_RENDER_TARGET_VIEW_DESC rtvDesc = {};
	rtvDesc.ViewDimension = D3D11_RTV_DIMENSION_TEXTURE2D;
	rtvDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM_SRGB;
	rtvDesc.Texture2D.MipSlice = 0;
	hr = GraphicsManager::GetInstance()->GetDevice().p11D
		->CreateRenderTargetView(m_pTex, &rtvDesc, &m_pRTV);
	if (SUCCEEDED(hr))
	{
		D3D11_TEXTURE2D_DESC desc;
		m_pTex->GetDesc(&desc);
		m_width = desc.Width;
		m_height = desc.Height;
	}
	return hr;
}
HRESULT DirectX11RenderTarget::CreateResource(D3D11_TEXTURE2D_DESC& desc, const void* pData)
{
	// テクスチャリソース作成
	HRESULT hr = DirectX11Texture::CreateResource(desc, nullptr);
	if (FAILED(hr)) { return hr; }

	// 設定
	D3D11_RENDER_TARGET_VIEW_DESC rtvDesc = {};
	rtvDesc.Format = desc.Format;
	rtvDesc.ViewDimension = D3D11_RTV_DIMENSION_TEXTURE2D;

	// 生成
	return GraphicsManager::GetInstance()->GetDevice().p11D
		->CreateRenderTargetView(m_pTex, &rtvDesc, &m_pRTV);
}



DirectX11DepstStencil::DirectX11DepstStencil()
	: m_pDSV(nullptr)
{
}
DirectX11DepstStencil::~DirectX11DepstStencil()
{
	delete m_pDSV;
	m_pDSV = nullptr;
}
void DirectX11DepstStencil::Clear()
{
	GraphicsManager::GetInstance()->GetDeviceContext().p11DC
		->ClearDepthStencilView(m_pDSV, D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);
}
HRESULT DirectX11DepstStencil::Create(uint16 width, uint16 height, bool useStencil)
{
	// https://docs.microsoft.com/ja-jp/windows/win32/direct3d11/d3d10-graphics-programming-guide-depth-stencil#compositing
	D3D11_TEXTURE2D_DESC desc = MakeTexDesc(useStencil ? DXGI_FORMAT_R24G8_TYPELESS : DXGI_FORMAT_R32_TYPELESS, width, height);
	desc.BindFlags |= D3D11_BIND_DEPTH_STENCIL;
	return CreateResource(desc);
}
HRESULT DirectX11DepstStencil::CreateResource(D3D11_TEXTURE2D_DESC& desc, const void* pData)
{
	// ステンシル使用判定
	bool useStencil = (desc.Format == DXGI_FORMAT_R24G8_TYPELESS);

	// リソース生成
	desc.BindFlags |= D3D11_BIND_DEPTH_STENCIL;
	HRESULT hr = DirectX11Texture::CreateResource(desc, nullptr);
	if (FAILED(hr)) { return hr; }

	// 設定
	D3D11_DEPTH_STENCIL_VIEW_DESC dsvDesc = {};
	dsvDesc.Format = useStencil ? DXGI_FORMAT_D24_UNORM_S8_UINT : DXGI_FORMAT_D32_FLOAT;
	dsvDesc.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;

	// 生成
	return GraphicsManager::GetInstance()->GetDevice().p11D->CreateDepthStencilView(m_pTex, &dsvDesc, &m_pDSV);
}



SRV_data* DirectX11TextureFactory::CreateSRV(const std::string& path)
{
	HRESULT hr = S_OK;
	SRV_data* data = New(SRV_data);

	// 文字変換
	wchar_t wPath[MAX_PATH];
	size_t wLen = 0;
	MultiByteToWideChar(0, 0, path.c_str(), -1, wPath, MAX_PATH);

	// ファイル別読み込み
	DirectX::TexMetadata mdata;
	DirectX::ScratchImage image;
	if (strstr(path.c_str(), ".tga"))
		hr = DirectX::LoadFromTGAFile(wPath, &mdata, image);
	else
		hr = DirectX::LoadFromWICFile(wPath, DirectX::WIC_FLAGS::WIC_FLAGS_NONE, &mdata, image);
	if (FAILED(hr)) {
		return nullptr;
	}

	// シェーダリソース生成
	hr = CreateShaderResourceView(GraphicsManager::GetInstance()->GetDevice().p11D
		, image.GetImages(), image.GetImageCount(), mdata, &data->first.p11SRV);
	if (SUCCEEDED(hr))
	{
		data->second.x= (UINT)mdata.width;
		data->second.y = (UINT)mdata.height;
	}
	return data;
}
iTexture* DirectX11TextureFactory::CreateTexture()
{
	return New(DirectX11Texture);
}



void TextureManager::SetFactory(iTextureFactory* Factory)
{
	m_factory = Factory;
}
std::shared_ptr<SRV_data> TextureManager::LoadTexture(const std::string& Path) {
	if (m_srv.count(Path) && !m_srv[Path].expired()) {
		return m_srv[Path].lock();
	}
	std::shared_ptr<SRV_data> texture
		= std::shared_ptr<SRV_data>(NullptrCheck(m_factory->CreateSRV(Path)));
	m_srv[Path] = texture;
	return texture;
}
std::shared_ptr<iTexture> TextureManager::CreateTexture()
{
	return std::shared_ptr<iTexture>(NullptrCheck(m_factory->CreateTexture()));
}
std::shared_ptr<iTexture> TextureManager::CreateTexture(const std::string& Path)
{
	if (m_Textures.count(Path) && !m_Textures[Path].expired()) {
		return m_Textures[Path].lock();
	}
	std::shared_ptr<iTexture> texture = std::shared_ptr<iTexture>(NullptrCheck(m_factory->CreateTexture()));
	m_Textures[Path] = texture;
	return texture;
}
std::shared_ptr<iRenderTarget> TextureManager::RecordRenderTarget(const std::string& RecordName)
{
	if (m_RenderTargets.count(RecordName) && !m_RenderTargets[RecordName].expired()) {
		return m_RenderTargets[RecordName].lock();
	}
	std::shared_ptr<iRenderTarget> texture = std::shared_ptr<iRenderTarget>(NullptrCheck(m_factory->CreateRenderTarget()));
	m_RenderTargets[RecordName] = texture;
	return texture;
}
std::shared_ptr<iDepstStencil> TextureManager::RecordDepstStencil(const std::string& RecordName)
{
	if (m_DepstStencils.count(RecordName) && !m_DepstStencils[RecordName].expired()) {
		return m_DepstStencils[RecordName].lock();
	}
	std::shared_ptr<iDepstStencil> texture = std::shared_ptr<iDepstStencil>(NullptrCheck(m_factory->CreateDepstStencil()));
	m_DepstStencils[RecordName] = texture;
	return texture;
}
TextureManager::TextureManager()
	: m_factory(nullptr)
{
	m_factory = Graphic::GraphicsManager::GetInstance()->GetiTextureFactory();
	m_defaultRTV = RecordRenderTarget("default");

	Engine::Window& window = Engine::Window::GetInstance();
	m_defaultRTV->CreateFormScreen();
	m_defaultDSV = RecordDepstStencil("default");
	m_defaultDSV->Create(window.GetScreenSize().first, window.GetScreenSize().second, false);
}
TextureManager::~TextureManager()
{
	m_defaultDSV.reset();
	m_defaultRTV.reset();

	//delete m_factory;
	m_factory = nullptr;
}
