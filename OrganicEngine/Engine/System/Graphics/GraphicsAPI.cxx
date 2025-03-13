#include "GraphicsAPI.hxx"

using namespace Engine::Graphic;

void GraphicsDirectX11::Initialize(HWND hWnd, int16 width, int16 height)
{
	m_Device.Initialize();

	m_SwapChain.Create();
}

void GraphicsDirectX11::RenderFrame()
{
	m_SwapChain.Present();
}

void GraphicsDirectX11::Cleanup()
{
}

void DirectX12Graphics::Initialize(HWND hWnd, int16 width, int16 height)
{
	m_Device.Initialize();
}

void DirectX12Graphics::RenderFrame()
{
	m_SwapChain.Present();
}

void DirectX12Graphics::Cleanup()
{
}

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
