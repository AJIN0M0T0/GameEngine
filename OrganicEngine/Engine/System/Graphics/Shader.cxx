#include "Shader.hxx"
#include <d3dcompiler.h>
#include "GraphicsAPI.hxx"

#pragma comment(lib, "d3dcompiler.lib")

using namespace Engine::Graphic;

HRESULT DirectX11Shader::Load(const std::string& Path)
{
	
	if(m_isComplete)
		return MB_OK;

	HRESULT hr = E_FAIL;

	// ファイルを読み込む
	FILE* fp;
	fopen_s(&fp, ("Assets/Shader/" + Path + ".cso").c_str(), "rb");
	if (!fp) { return hr; }

	// ファイルのサイズを調べる
	int fileSize = 0;
	fseek(fp, 0, SEEK_END);
	fileSize = ftell(fp);

	// メモリに読み込み
	fseek(fp, 0, SEEK_SET);
	char* pData = new char[fileSize];
	fread(pData, fileSize, 1, fp);
	fclose(fp);

	// シェーダー作成
	hr = Make(pData, fileSize);

	// 終了処理
	if (pData) { delete[] pData; }

	m_isComplete = true;

	return hr;
}
HRESULT DirectX11Shader::Compile(const std::string& code)
{
	if(m_isComplete)
		return MB_OK;

	static const char* pTargetList[] =
	{
		"vs_5_0",
		"gs_5_0",
		"hs_5_0",
		"ds_5_0",
		"ps_5_0"
	};

	HRESULT hr;
	ID3DBlob* pBlob = nullptr;
	ID3DBlob* error = nullptr;
	UINT compileFlag = D3DCOMPILE_DEBUG | D3DCOMPILE_SKIP_OPTIMIZATION;
	hr = D3DCompile(code.c_str(), code.length(), nullptr, nullptr, nullptr,
		"main", pTargetList[(int)m_kind], compileFlag, 0, &pBlob, &error);
	if (FAILED(hr)) { return hr; }

	// シェーダ作成
	hr = Make(pBlob->GetBufferPointer(), (UINT)pBlob->GetBufferSize());
	if(pBlob) pBlob->Release();
	pBlob = nullptr;
	if(error) error->Release();
	error = nullptr;

	m_isComplete = true;

	return hr;
}
void DirectX11Shader::WriteBuffer(uint16 slot, void* pData)
{
	if (slot < m_pBuffers.size())
		GraphicsManager::GetInstance()->GetDeviceContext().p11DC
			->UpdateSubresource(m_pBuffers[slot], 0, nullptr, pData, 0, 0);
}
void DirectX11Shader::SetTexture(uint16 slot, iTexture* pTexture)
{
	if (slot >= m_pTextures.size()) { return; }
	ID3D11ShaderResourceView* pTex = pTexture ? pTexture->GetResource().p11SRV : nullptr;
	m_pTextures[slot] = pTex;
	ID3D11DeviceContext* pContext = GraphicsManager::GetInstance()->GetDeviceContext().p11DC;
	switch (m_kind)
	{
	case Engine::Graphic::iShader::ShaderType::Vertex:
		pContext->VSSetShaderResources(slot, 1, &pTex); break;
	case Engine::Graphic::iShader::ShaderType::Hull:
		pContext->HSSetShaderResources(slot, 1, &pTex); break;
	case Engine::Graphic::iShader::ShaderType::Domain:
		pContext->DSSetShaderResources(slot, 1, &pTex); break;
	case Engine::Graphic::iShader::ShaderType::Pixel:
		pContext->PSSetShaderResources(slot, 1, &pTex); break;
	}
}
HRESULT DirectX11Shader::Make(void* pData, uint16 size)
{
	HRESULT hr;
	ID3D11Device* pDevice = static_cast<ID3D11Device*>(GraphicsManager::GetInstance()->GetDevice().p11D);

	// 解析用のリフレクション作成
	ID3D11ShaderReflection* pReflection;
	hr = D3DReflect(pData, size, IID_PPV_ARGS(&pReflection));
	if (FAILED(hr)) { return hr; }

	// 定数バッファ作成
	D3D11_SHADER_DESC shaderDesc;
	pReflection->GetDesc(&shaderDesc);
	m_pBuffers.resize(shaderDesc.ConstantBuffers, nullptr);
	for (UINT i = 0; i < shaderDesc.ConstantBuffers; ++i)
	{
		// シェーダーの定数バッファの情報を取得
		D3D11_SHADER_BUFFER_DESC shaderBufDesc;
		ID3D11ShaderReflectionConstantBuffer* cbuf = pReflection->GetConstantBufferByIndex(i);
		cbuf->GetDesc(&shaderBufDesc);

		// 作成するバッファの情報
		D3D11_BUFFER_DESC bufDesc = {};
		bufDesc.ByteWidth = shaderBufDesc.Size;
		bufDesc.Usage = D3D11_USAGE_DEFAULT;
		bufDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;

		// バッファの作成
		hr = pDevice->CreateBuffer(&bufDesc, nullptr, &m_pBuffers[i]);
		if (FAILED(hr)) { return hr; }
	}
	// テクスチャ領域作成
	m_pTextures.resize(shaderDesc.BoundResources, nullptr);

	return MakeShader(pData, size);
}

DirectX11VertexShader::DirectX11VertexShader()
	: DirectX11Shader()
	, iVertexShader()
	, m_pVS(nullptr)
	, m_pInputLayout(nullptr)
{
}
DirectX11VertexShader::~DirectX11VertexShader()
{/*
	if(m_pVS)delete m_pVS;
	m_pVS = nullptr;*/
}
void DirectX11VertexShader::Bind()
{
	ID3D11DeviceContext* pContext = GraphicsManager::GetInstance()->GetDeviceContext().p11DC;
	pContext->VSSetShader(m_pVS, NULL, 0);
	pContext->IASetInputLayout(m_pInputLayout);
	for (int i = 0; i < m_pBuffers.size(); ++i)
		pContext->VSSetConstantBuffers(i, 1, &m_pBuffers[i]);
	for (int i = 0; i < m_pTextures.size(); ++i)
		pContext->VSSetShaderResources(i, 1, &m_pTextures[i]);
}
HRESULT DirectX11VertexShader::MakeShader(void* pData, uint16 size)
{
	HRESULT hr;
	ID3D11Device* pDevice = GraphicsManager::GetInstance()->GetDevice().p11D;

	// シェーダー作成
	hr = pDevice->CreateVertexShader(pData, size, NULL, &m_pVS);
	if (FAILED(hr)) { return hr; }

	/*
	シェーダ作成時にシェーダリフレクションを通してインプットレイアウトを取得
	セマンティクスの配置などから識別子を作成
	識別子が登録済→再利用、なければ新規作成
	https://blog.techlab-xe.net/dxc-shader-reflection/
	*/

	ID3D11ShaderReflection* pReflection;
	D3D11_SHADER_DESC shaderDesc;
	D3D11_INPUT_ELEMENT_DESC* pInputDesc;
	D3D11_SIGNATURE_PARAMETER_DESC sigDesc;

	DXGI_FORMAT formats[][4] =
	{
		{
			DXGI_FORMAT_R32_UINT,
			DXGI_FORMAT_R32G32_UINT,
			DXGI_FORMAT_R32G32B32_UINT,
			DXGI_FORMAT_R32G32B32A32_UINT,
		}, {
			DXGI_FORMAT_R32_SINT,
			DXGI_FORMAT_R32G32_SINT,
			DXGI_FORMAT_R32G32B32_SINT,
			DXGI_FORMAT_R32G32B32A32_SINT,
		}, {
			DXGI_FORMAT_R32_FLOAT,
			DXGI_FORMAT_R32G32_FLOAT,
			DXGI_FORMAT_R32G32B32_FLOAT,
			DXGI_FORMAT_R32G32B32A32_FLOAT,
		},
	};

	hr = D3DReflect(pData, size, IID_PPV_ARGS(&pReflection));
	if (FAILED(hr)) { return hr; }

	pReflection->GetDesc(&shaderDesc);
	pInputDesc = new D3D11_INPUT_ELEMENT_DESC[shaderDesc.InputParameters];
	for (UINT i = 0; i < shaderDesc.InputParameters; ++i)
	{
		pReflection->GetInputParameterDesc(i, &sigDesc);
		pInputDesc[i].SemanticName = sigDesc.SemanticName;
		pInputDesc[i].SemanticIndex = sigDesc.SemanticIndex;

		// http://marupeke296.com/TIPS_No17_Bit.html
		BYTE elementCount = sigDesc.Mask;
		elementCount = (elementCount & 0x05) + ((elementCount >> 1) & 0x05);
		elementCount = (elementCount & 0x03) + ((elementCount >> 2) & 0x03);

		switch (sigDesc.ComponentType)
		{
		case D3D_REGISTER_COMPONENT_UINT32:
			pInputDesc[i].Format = formats[0][elementCount - 1];
			break;
		case D3D_REGISTER_COMPONENT_SINT32:
			pInputDesc[i].Format = formats[1][elementCount - 1];
			break;
		case D3D_REGISTER_COMPONENT_FLOAT32:
			pInputDesc[i].Format = formats[2][elementCount - 1];
			break;
		}
		pInputDesc[i].InputSlot = 0;
		pInputDesc[i].AlignedByteOffset = i == 0 ? 0 : D3D11_APPEND_ALIGNED_ELEMENT;
		pInputDesc[i].InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
		pInputDesc[i].InstanceDataStepRate = 0;
	}

	hr = pDevice->CreateInputLayout(
		pInputDesc, shaderDesc.InputParameters,
		pData, size, &m_pInputLayout
	);

	delete[] pInputDesc;
	return hr;
}

DirectX11PixelShader::DirectX11PixelShader()
	: DirectX11Shader()
	, iPixelShader()
	, m_pPS(nullptr)
{
}
DirectX11PixelShader::~DirectX11PixelShader()
{
	if (m_pPS)delete m_pPS;
	m_pPS = nullptr;
}
void DirectX11PixelShader::Bind()
{
	ID3D11DeviceContext* pContext = GraphicsManager::GetInstance()->GetDeviceContext().p11DC;
	pContext->PSSetShader(m_pPS, nullptr, 0);
	for (int i = 0; i < m_pBuffers.size(); ++i)
		pContext->PSSetConstantBuffers(i, 1, &m_pBuffers[i]);
	for (int i = 0; i < m_pTextures.size(); ++i)
		pContext->PSSetShaderResources(i, 1, &m_pTextures[i]);
}
HRESULT DirectX11PixelShader::MakeShader(void* pData, uint16 size)
{
	return GraphicsManager::GetInstance()->GetDevice().p11D->CreatePixelShader(pData, size, NULL, &m_pPS);
}

DirectX11HullShader::DirectX11HullShader()
	: DirectX11Shader()
	, iHullShader()
	, m_pHS(nullptr)
{
}
DirectX11HullShader::~DirectX11HullShader()
{
	if (m_pHS)delete m_pHS;
	m_pHS = nullptr;
}
void DirectX11HullShader::Bind()
{
	ID3D11DeviceContext* pContext = GraphicsManager::GetInstance()->GetDeviceContext().p11DC;
	pContext->HSSetShader(m_pHS, nullptr, 0);
	pContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_4_CONTROL_POINT_PATCHLIST);
	for (int i = 0; i < m_pBuffers.size(); ++i)
		pContext->HSSetConstantBuffers(i, 1, &m_pBuffers[i]);
	for (int i = 0; i < m_pTextures.size(); ++i)
		pContext->HSSetShaderResources(i, 1, &m_pTextures[i]);
}
void DirectX11HullShader::Unbind()
{
	GraphicsManager::GetInstance()->GetDeviceContext().p11DC->HSSetShader(nullptr, nullptr, 0);
}
HRESULT DirectX11HullShader::MakeShader(void* pData, uint16 size)
{
	return GraphicsManager::GetInstance()->GetDevice().p11D->CreateHullShader(pData, size, NULL, &m_pHS);
}

DirectX11DomainShader::DirectX11DomainShader()
	: DirectX11Shader()
	, iDomainShader()
	, m_pDS(nullptr)
{
}
DirectX11DomainShader::~DirectX11DomainShader()
{
	if (m_pDS)delete m_pDS;
	m_pDS = nullptr;
}
void DirectX11DomainShader::Bind()
{
	ID3D11DeviceContext* pContext = GraphicsManager::GetInstance()->GetDeviceContext().p11DC;
	pContext->DSSetShader(m_pDS, nullptr, 0);
	for (int i = 0; i < m_pBuffers.size(); ++i)
		pContext->DSSetConstantBuffers(i, 1, &m_pBuffers[i]);
	for (int i = 0; i < m_pTextures.size(); ++i)
		pContext->DSSetShaderResources(i, 1, &m_pTextures[i]);
}
void DirectX11DomainShader::Unbind()
{
	GraphicsManager::GetInstance()->GetDeviceContext().p11DC->DSSetShader(nullptr, nullptr, 0);
}
HRESULT DirectX11DomainShader::MakeShader(void* pData, uint16 size)
{
	return GraphicsManager::GetInstance()->GetDevice().p11D->CreateDomainShader(pData, size, NULL, &m_pDS);
}

DirectX11GeometryShader::DirectX11GeometryShader()
	: DirectX11Shader()
	, iGeometryShader()
	, m_pGS(nullptr)
{
}
DirectX11GeometryShader::~DirectX11GeometryShader()
{
	if (m_pGS)delete m_pGS;
	m_pGS = nullptr;
}
void DirectX11GeometryShader::Bind()
{
	ID3D11DeviceContext* pContext = GraphicsManager::GetInstance()->GetDeviceContext().p11DC;
	pContext->GSSetShader(m_pGS, nullptr, 0);
	for (int i = 0; i < m_pBuffers.size(); ++i)
		pContext->GSSetConstantBuffers(i, 1, &m_pBuffers[i]);
	for (int i = 0; i < m_pTextures.size(); ++i)
		pContext->GSSetShaderResources(i, 1, &m_pTextures[i]);
}
void DirectX11GeometryShader::Unbind()
{
	ID3D11DeviceContext* pContext = GraphicsManager::GetInstance()->GetDeviceContext().p11DC;
	ID3D11ShaderResourceView* pSRV = nullptr;
	pContext->GSSetShaderResources(0, 1, &pSRV);
	pContext->GSSetShader(nullptr, nullptr, 0);
}
HRESULT DirectX11GeometryShader::MakeShader(void* pData, uint16 size)
{
	return GraphicsManager::GetInstance()->GetDevice().p11D->CreateGeometryShader(pData, size, NULL, &m_pGS);
}

DirectX11ComputeShader::DirectX11ComputeShader()
	: DirectX11Shader()
	, iComputeShader()
	, m_pCS(nullptr)
{
}
DirectX11ComputeShader::~DirectX11ComputeShader()
{
	if (m_pCS)delete m_pCS;
	m_pCS = nullptr;
}
void DirectX11ComputeShader::Bind()
{
	ID3D11DeviceContext* pContext = GraphicsManager::GetInstance()->GetDeviceContext().p11DC;
	pContext->CSSetShader(m_pCS, nullptr, 0);
	for (int i = 0; i < m_pBuffers.size(); ++i)
		pContext->CSSetConstantBuffers(i, 1, &m_pBuffers[i]);
	for (int i = 0; i < m_pTextures.size(); ++i)
		pContext->CSSetShaderResources(i, 1, &m_pTextures[i]);
}
void DirectX11ComputeShader::Unbind()
{
	ID3D11DeviceContext* pContext = GraphicsManager::GetInstance()->GetDeviceContext().p11DC;
	ID3D11UnorderedAccessView* pUAV = nullptr;
	ID3D11ShaderResourceView* pSRV = nullptr;

	pContext->CSSetUnorderedAccessViews(0, 1, &pUAV, nullptr);
	pContext->CSSetShaderResources(0, 1, &pSRV);
	GraphicsManager::GetInstance()->GetDeviceContext().p11DC->CSSetShader(nullptr, nullptr, 0);
}
void DirectX11ComputeShader::Dispatch(uint32 num, iUnorderedAccessView** ppUAV, uint32 thread)
{
	ID3D11DeviceContext* pContext = GraphicsManager::GetInstance()->GetDeviceContext().p11DC;
	ID3D11UnorderedAccessView* ptr[4];
	if (num > 4) num = 4;
	for (int i = 0; i < num; ++i)
		ptr[i] = ppUAV[i]->GetUAV().p11UAV;
	pContext->CSSetUnorderedAccessViews(0, num, ptr, nullptr);
	pContext->Dispatch(thread, 1, 1);
}
HRESULT DirectX11ComputeShader::MakeShader(void* pData, uint16 size)
{
	return GraphicsManager::GetInstance()->GetDevice().p11D->CreateComputeShader(pData, size, NULL, &m_pCS);
}



iVertexShader* DirectX11ShaderFactory::CreateVertexShader()
{
	return New(DirectX11VertexShader);
}
iPixelShader* DirectX11ShaderFactory::CreatePixelShader()
{
	return New(DirectX11PixelShader);
}
iHullShader* DirectX11ShaderFactory::CreateHullShader()
{
	return New(DirectX11HullShader);
}
iDomainShader* DirectX11ShaderFactory::CreateDomainShader()
{
	return New(DirectX11DomainShader);
}
iGeometryShader* DirectX11ShaderFactory::CreateGeometryShader()
{
	return New(DirectX11GeometryShader);
}
iComputeShader* DirectX11ShaderFactory::CreateComputeShader()
{
	return New(DirectX11ComputeShader);
}


ShaderManager::ShaderManager()
	: m_pFactory(nullptr)
{
}
ShaderManager::~ShaderManager()
{
	if (m_pFactory)delete m_pFactory;
	m_pFactory = nullptr;
}
void ShaderManager::SetFactory(iShaderFactory* Factory)
{
	m_pFactory = Factory;
}
std::shared_ptr<iVertexShader> ShaderManager::LoadVertexShader(const std::string& Tag)
{
	std::string tag = "vs_" + Tag;
	if (m_shaders.count(tag) && !m_shaders[tag].expired()) {
		return std::dynamic_pointer_cast<iVertexShader>(m_shaders[tag].lock());
	}
	std::shared_ptr<iVertexShader> pShader = std::shared_ptr<iVertexShader>(m_pFactory->CreateVertexShader());
	m_shaders[tag] = pShader;
	return pShader;
}
std::shared_ptr<iPixelShader> ShaderManager::LoadPixelShader(const std::string& Tag)
{
	std::string tag = "ps_" + Tag;
	if (m_shaders.count(tag) && !m_shaders[tag].expired()) {
		return std::dynamic_pointer_cast<iPixelShader>(m_shaders[tag].lock());
	}
	std::shared_ptr<iPixelShader> pShader = std::shared_ptr<iPixelShader>(m_pFactory->CreatePixelShader());
	m_shaders[tag] = pShader;
	return pShader;
}
std::shared_ptr<iHullShader> ShaderManager::LoadHullShader(const std::string& Tag)
{
	std::string tag = "hs_" + Tag;
	if (m_shaders.count(tag) && !m_shaders[tag].expired()) {
		return std::dynamic_pointer_cast<iHullShader>(m_shaders[tag].lock());
	}
	std::shared_ptr<iHullShader> pShader = std::shared_ptr<iHullShader>(m_pFactory->CreateHullShader());
	m_shaders[tag] = pShader;
	return pShader;
}
std::shared_ptr<iDomainShader> ShaderManager::LoadDomainShader(const std::string& Tag)
{
	std::string tag = "ds_" + Tag;
	if (m_shaders.count(tag) && !m_shaders[tag].expired()) {
		return std::dynamic_pointer_cast<iDomainShader>(m_shaders[tag].lock());
	}
	std::shared_ptr<iDomainShader> pShader = std::shared_ptr<iDomainShader>(m_pFactory->CreateDomainShader());
	m_shaders[tag] = pShader;
	return pShader;
}
std::shared_ptr<iGeometryShader> ShaderManager::LoadGeometryShader(const std::string& Tag)
{
	std::string tag = "gs_" + Tag;
	if (m_shaders.count(tag) && !m_shaders[tag].expired()) {
		return std::dynamic_pointer_cast<iGeometryShader>(m_shaders[tag].lock());
	}
	std::shared_ptr<iGeometryShader> pShader = std::shared_ptr<iGeometryShader>(m_pFactory->CreateGeometryShader());
	m_shaders[tag] = pShader;
	return pShader;
}
std::shared_ptr<iComputeShader> ShaderManager::LoadComputeShader(const std::string& Tag)
{
	std::string tag = "cs_" + Tag;
	if (m_shaders.count(tag) && !m_shaders[tag].expired()) {
		return std::dynamic_pointer_cast<iComputeShader>(m_shaders[tag].lock());
	}
	std::shared_ptr<iComputeShader> pShader = std::shared_ptr<iComputeShader>(m_pFactory->CreateComputeShader());
	m_shaders[tag] = pShader;
	return pShader;
}
