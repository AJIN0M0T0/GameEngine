#include "GraphicsAPI.hxx"

using namespace Engine::Graphic

void GraphicsDirectX11::Initialize(HWND hWnd, int16 width, int16 height)
{
	m_Device.Initialize();
	m_SwapChain.Initialize(hWnd, width, height);
	m_CommandQueue.Initialize();
}

void GraphicsDirectX11::RenderFrame()
{
	m_SwapChain.Present();
}

void GraphicsDirectX11::Cleanup()
{
	m_CommandQueue.Cleanup();
	m_SwapChain.Cleanup();
	m_Device.Cleanup();
}

void DirectX12Graphics::Initialize(HWND hWnd, int16 width, int16 height)
{
	m_Device.Initialize();
	m_SwapChain.Initialize(hWnd, width, height);
	m_CommandQueue.Initialize();
}

void DirectX12Graphics::RenderFrame()
{
	m_SwapChain.Present();
}

void DirectX12Graphics::Cleanup()
{
	m_CommandQueue.Cleanup();
	m_SwapChain.Cleanup();
	m_Device.Cleanup();
}
