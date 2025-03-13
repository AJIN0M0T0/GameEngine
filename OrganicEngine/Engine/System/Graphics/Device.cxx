#include "Device.hxx"

// =-=-= インクルード部 =-=-=
#include <d3d11.h>
#include <d3d12.h>

#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "dxgi.lib")

using namespace Engine::Graphic;

bool DirectX11Device::Initialize()
{
	D3D_DRIVER_TYPE driverTypes[] =
	{
		D3D_DRIVER_TYPE_HARDWARE,
		D3D_DRIVER_TYPE_WARP,
		D3D_DRIVER_TYPE_REFERENCE,
	};
	UINT numDriverTypes = ARRAYSIZE(driverTypes);

	D3D_FEATURE_LEVEL featureLevels[] =
	{
		D3D_FEATURE_LEVEL_11_1,
		D3D_FEATURE_LEVEL_11_0,
		D3D_FEATURE_LEVEL_10_1,
		D3D_FEATURE_LEVEL_10_0,
		D3D_FEATURE_LEVEL_9_3,
		D3D_FEATURE_LEVEL_9_2,
		D3D_FEATURE_LEVEL_9_1,
	};
	UINT numFeatureLevels = ARRAYSIZE(featureLevels);
	D3D_DRIVER_TYPE driverType;
	D3D_FEATURE_LEVEL featureLevel;

	// 適切なデバイスの選択
	IDXGIFactory* pFactory = nullptr;
	HRESULT hr = CreateDXGIFactory(__uuidof(IDXGIFactory), (void**)&pFactory);
	if (FAILED(hr)) {
		//std::cerr << "Failed to create DXGI Factory" << std::endl;
		return false;
	}
	IDXGIAdapter* pAdapter = nullptr;
	IDXGIAdapter* pBestAdapter = nullptr;
	SIZE_T bestVideoMemory = 0;
	for (UINT i = 0; pFactory->EnumAdapters(i, &pAdapter) != DXGI_ERROR_NOT_FOUND; ++i) {
		DXGI_ADAPTER_DESC desc;
		pAdapter->GetDesc(&desc);

		// ビデオメモリ量で最も優れたアダプターを選択
		if (desc.DedicatedVideoMemory > bestVideoMemory) {
			bestVideoMemory = desc.DedicatedVideoMemory;
			if (pBestAdapter) pBestAdapter->Release();
			pBestAdapter = pAdapter;
			pBestAdapter->AddRef();
		}

		pAdapter->Release();
	}

	pFactory->Release();

	for (UINT driverTypeIndex = 0; driverTypeIndex < numDriverTypes; ++driverTypeIndex)
	{
		driverType = driverTypes[driverTypeIndex];
		hr = D3D11CreateDevice(
			pBestAdapter
			, driverType
			, nullptr
			, 0
			, featureLevels
			, numFeatureLevels
			, D3D11_SDK_VERSION
			, &m_Device
			, &featureLevel
			, &m_DeviceContext
		);
		if (SUCCEEDED(hr)){
			break;
		}
	}
	if (FAILED(hr)) {
		//std::cerr << "Failed to create D3D11 Device" << std::endl;
		return false;
	}

	//-------------------------------------------------------------------------------------
		//--- カリング設定
	D3D11_RASTERIZER_DESC rasterizer = {};
	D3D11_CULL_MODE cull[] = {
		D3D11_CULL_NONE,
		D3D11_CULL_FRONT,
		D3D11_CULL_BACK
	};
	rasterizer.FillMode = D3D11_FILL_SOLID;
	rasterizer.FrontCounterClockwise = true;
	for (int i = 0; i < 3; ++i)
	{
		rasterizer.CullMode = cull[i];
		hr = m_Device->CreateRasterizerState(&rasterizer, &m_pRasterizerState[i]);
		if (FAILED(hr)) { return hr; }
	}
	switch (D3D11_CULL_NONE)
	{
	case D3D11_CULL_NONE:  m_DeviceContext->RSSetState(m_pRasterizerState[0]); break;
	case D3D11_CULL_FRONT: m_DeviceContext->RSSetState(m_pRasterizerState[1]); break;
	case D3D11_CULL_BACK:  m_DeviceContext->RSSetState(m_pRasterizerState[2]); break;
	}

	//--- 深度テスト
	// https://tositeru.github.io/ImasaraDX11/part/ZBuffer-and-depth-stencil
	D3D11_DEPTH_STENCIL_DESC dsDesc = {};
	dsDesc.DepthEnable = true;
	dsDesc.DepthFunc = D3D11_COMPARISON_LESS_EQUAL;
	dsDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
	dsDesc.StencilEnable = true;
	dsDesc.StencilReadMask = D3D11_DEFAULT_STENCIL_READ_MASK;
	dsDesc.StencilWriteMask = D3D11_DEFAULT_STENCIL_WRITE_MASK;
	dsDesc.FrontFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;
	dsDesc.FrontFace.StencilDepthFailOp = D3D11_STENCIL_OP_KEEP;
	dsDesc.FrontFace.StencilPassOp = D3D11_STENCIL_OP_INCR;
	dsDesc.FrontFace.StencilFunc = D3D11_COMPARISON_GREATER_EQUAL;
	dsDesc.BackFace = dsDesc.FrontFace;
	bool enablePattern[] = { true, true, false };
	D3D11_DEPTH_WRITE_MASK maskPattern[] = {
		D3D11_DEPTH_WRITE_MASK_ALL,
		D3D11_DEPTH_WRITE_MASK_ZERO,
		D3D11_DEPTH_WRITE_MASK_ZERO,
	};
	enum DepthState
	{
		DEPTH_ENABLE_WRITE_TEST,
		DEPTH_ENABLE_TEST,
		DEPTH_DISABLE,
		DEPTH_MAX
	};
	for (int i = 0; i < DEPTH_MAX; ++i)
	{
		dsDesc.DepthEnable = dsDesc.StencilEnable = enablePattern[i];
		dsDesc.DepthWriteMask = maskPattern[i];
		hr = m_Device->CreateDepthStencilState(&dsDesc, &m_pDepthStencilState[i]);
		if (FAILED(hr)) { return hr; }
	}
	m_DeviceContext->OMSetDepthStencilState(m_pDepthStencilState[DEPTH_ENABLE_WRITE_TEST],0);

	//--- アルファブレンディング
// https://pgming-ctrl.com/directx11/blend/
	D3D11_BLEND_DESC blendDesc = {};
	blendDesc.AlphaToCoverageEnable = FALSE;
	blendDesc.IndependentBlendEnable = FALSE;
	blendDesc.RenderTarget[0].BlendEnable = TRUE;
	blendDesc.RenderTarget[0].BlendOp = D3D11_BLEND_OP_ADD;
	blendDesc.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP_ADD;
	blendDesc.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_ONE;
	blendDesc.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_ZERO;
	blendDesc.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;
	D3D11_BLEND blend[BLEND_MAX][2] = {
		{D3D11_BLEND_ONE, D3D11_BLEND_ZERO},
		{D3D11_BLEND_SRC_ALPHA, D3D11_BLEND_INV_SRC_ALPHA},
		{D3D11_BLEND_ONE, D3D11_BLEND_ONE},
		{D3D11_BLEND_SRC_ALPHA, D3D11_BLEND_ONE},
		{D3D11_BLEND_ZERO, D3D11_BLEND_INV_SRC_COLOR},
		{D3D11_BLEND_INV_DEST_COLOR, D3D11_BLEND_ONE},
	};
	for (int i = 0; i < BLEND_MAX; ++i)
	{
		blendDesc.RenderTarget[0].SrcBlend = blend[i][0];
		blendDesc.RenderTarget[0].DestBlend = blend[i][1];
		hr = m_Device->CreateBlendState(&blendDesc, &m_pBlendState[i]);
		if (FAILED(hr)) { return hr; }
	}
	if (BLEND_ALPHA < 0 || BLEND_ALPHA >= BLEND_MAX) return false;
	FLOAT blendFactor[4] = { D3D11_BLEND_ZERO, D3D11_BLEND_ZERO, D3D11_BLEND_ZERO, D3D11_BLEND_ZERO };
	m_DeviceContext->OMSetBlendState(m_pBlendState[BLEND_ALPHA], blendFactor, 0xffffffff);

	// サンプラー
	D3D11_SAMPLER_DESC samplerDesc = {};
	D3D11_FILTER filter[] = {
		D3D11_FILTER_MIN_MAG_MIP_LINEAR,
		D3D11_FILTER_MIN_MAG_MIP_POINT,
	};
	samplerDesc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
	samplerDesc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
	samplerDesc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
	for (int i = 0; i < SAMPLER_MAX; ++i)
	{
		samplerDesc.Filter = filter[i];
		hr = m_Device->CreateSamplerState(&samplerDesc, &m_pSamplerState[i]);
		if (FAILED(hr)) { return hr; }
	}
	if (SAMPLER_LINEAR < 0 || SAMPLER_LINEAR >= SAMPLER_MAX) return false;
	m_DeviceContext->VSSetSamplers(0, 1, &m_pSamplerState[SAMPLER_LINEAR]);
	m_DeviceContext->PSSetSamplers(0, 1, &m_pSamplerState[SAMPLER_LINEAR]);
	m_DeviceContext->HSSetSamplers(0, 1, &m_pSamplerState[SAMPLER_LINEAR]);
	m_DeviceContext->DSSetSamplers(0, 1, &m_pSamplerState[SAMPLER_LINEAR]);

	return true;
}
void DirectX11Device::CreateRenderTarget()
{
}


bool DirectX12Device::Initialize()
{
	return false;
}
void DirectX12Device::CreateRenderTarget()
{
}
