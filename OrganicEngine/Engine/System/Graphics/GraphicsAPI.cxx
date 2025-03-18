#include "GraphicsAPI.hxx"
#include "Texture.hxx"
#include <d3d11.h>

using namespace Engine::Graphic;

void GraphicsDirectX11::Initialize(HWND hWnd, uint16 width, uint16 height)
{
	FalseCheck(m_Device.Initialize());

	m_SwapChain.Create();
}

void GraphicsDirectX11::RenderFrame()
{
	m_SwapChain.Present();
}

void GraphicsDirectX11::Cleanup()
{
}

void GraphicsDirectX11::SetRenderTarget(uint16 num, iRenderTarget** ppViews, iDepstStencil* pView) {
	static ID3D11RenderTargetView* rtvs[4];

	if (num > 4) num = 4;
	for (UINT i = 0; i < num; ++i)
		rtvs[i] = static_cast<ID3D11RenderTargetView*>(ppViews[i]->GetView());
	static_cast<ID3D11DeviceContext*>(m_Device.GetDeviceContext())->OMSetRenderTargets(num, rtvs, pView ? static_cast<ID3D11DepthStencilView*>(pView->GetView()) : nullptr);

	// ビューポートの設定
	D3D11_VIEWPORT vp;
	vp.TopLeftX = 0.0f;
	vp.TopLeftY = 0.0f;
	vp.Width = (float)ppViews[0]->GetWidth();
	vp.Height = (float)ppViews[0]->GetHeight();
	vp.MinDepth = 0.0f;
	vp.MaxDepth = 1.0f;
	static_cast<ID3D11DeviceContext*>(m_Device.GetDeviceContext())->RSSetViewports(1, &vp);
}

//void DirectX12Graphics::Initialize(HWND hWnd, int16 width, int16 height)
//{
//	m_Device.Initialize();
//}
//
//void DirectX12Graphics::RenderFrame()
//{
//	m_SwapChain.Present();
//}
//
//void DirectX12Graphics::Cleanup()
//{
//}

GraphicsFactory& GraphicsFactory::CreateGraphicsAPI()
{
	if (m_GraphicsAPI) return *this;
#ifdef DIRECTX11_PRJ
	m_GraphicsAPI = std::make_unique<GraphicsDirectX11>();
#elif defined(DIRECTX12_PRJ)
	m_GraphicsAPI = std::make_unique<DirectX12Graphics>();
#endif // DIRECTX11_PRJ
	return *this;
}
