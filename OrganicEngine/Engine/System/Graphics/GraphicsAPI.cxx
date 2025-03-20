#include "GraphicsAPI.hxx"
#include "Texture.hxx"
#include <d3d11.h>

using namespace Engine::Graphic;

void DirectX11GraphicsFactory::Initialize(HWND hWnd, uint16 width, uint16 height)
{
	FalseCheck(m_Device.Initialize());

	m_SwapChain.Create();
}

void DirectX11GraphicsFactory::RenderFrame()
{
	m_SwapChain.Present();
}

void DirectX11GraphicsFactory::Cleanup()
{
}

void DirectX11GraphicsFactory::SetRenderTarget(uint16 num, iRenderTarget** ppViews, iDepstStencil* pView) {
	static ID3D11RenderTargetView* rtvs[4];

	if (num > 4) num = 4;
	for (UINT i = 0; i < num; ++i)
		rtvs[i] = ppViews[i]->GetView().p11RTV;
	GetDeviceContext().p11DC->OMSetRenderTargets(num, rtvs, pView ? pView->GetView().p11DSV : nullptr);

	// ビューポートの設定
	D3D11_VIEWPORT vp;
	vp.TopLeftX = 0.0f;
	vp.TopLeftY = 0.0f;
	vp.Width = (float)ppViews[0]->GetWidth();
	vp.Height = (float)ppViews[0]->GetHeight();
	vp.MinDepth = 0.0f;
	vp.MaxDepth = 1.0f;
	GetDeviceContext().p11DC->RSSetViewports(1, &vp);
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

GraphicsManager& GraphicsManager::CreateGraphicsAPI()
{
	if (m_GraphicsAPI) return *this;
#ifdef DIRECTX11_PRJ
	m_GraphicsAPI = std::make_unique<DirectX11GraphicsFactory>();
#elif defined(DIRECTX12_PRJ)
	m_GraphicsAPI = std::make_unique<DirectX12Graphics>();
#endif // DIRECTX11_PRJ
	return *this;
}
