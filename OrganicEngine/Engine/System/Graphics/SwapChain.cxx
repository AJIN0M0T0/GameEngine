#include "SwapChain.hxx"

// =-=-= インクルード部 =-=-=
#include <dxgi1_2.h>
#include <d3d11.h>
#include "../Window.hxx"
#include "GraphicsAPI.hxx"

// =-=-= 名前空間 =-=-=
using namespace Engine::Graphic;

void DirectX11SwapChain::Create()
{
	HRESULT hr = E_FAIL;
	std::pair<UINT, UINT> m_BufferSize = Window::GetInstance().GetScreenSize();
	IDXGIFactory2* factory;

	hr = CreateDXGIFactory1(IID_PPV_ARGS(&factory));
	if (FAILED(hr)) return;

	DXGI_SWAP_CHAIN_DESC1 sd;
	ZeroMemory(&sd, sizeof(sd));
	sd.Width = m_BufferSize.first;						// バックバッファの幅
	sd.Height = m_BufferSize.second;						// バックバッファの高さ
	sd.Format = DXGI_FORMAT_R8G8B8A8_UNORM;	// バックバッファフォーマット(R,G,B,A)
	sd.Stereo = FALSE;									// ステレオ表示の有無
	sd.SampleDesc.Count = 1;							// マルチサンプルの数
	sd.SampleDesc.Quality = 0;							//
	sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;	// バックバッファの使用方法
	sd.BufferCount = 2;									// バックバッファの数
	sd.SwapEffect = DXGI_SWAP_EFFECT_FLIP_DISCARD;		// バックバッファの交換方法
	sd.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;

	HResultCheck( factory->CreateSwapChainForHwnd(
		static_cast<ID3D11Device*>(GraphicsFactory::GetInstance()->GetiDevice()->GetDevice())
		, Window::GetInstance().GetHWND()
		, &sd
		, nullptr, nullptr
		, &m_swapChain));
}

void DirectX11SwapChain::Present()
{
	m_swapChain->Present(0, 0);
}

void DirectX12SwapChain::Create()
{
}
void DirectX12SwapChain::Present()
{
}
