//	ファイル名	：Device.hxx
//	  概  要	：
//	作	成	者	：daigo
//	 作成日時	：2025/02/28 21:22:16
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/

// =-=-= インクルードガード部 =-=-=
#ifndef _____Device_HXX_____
#define _____Device_HXX_____

// =-=-= インクルード部 =-=-=

// 前方定義
struct ID3D11Device;
struct ID3D11DeviceContext;
struct ID3D11RasterizerState;
struct ID3D11DepthStencilState;
struct ID3D11SamplerState;
struct ID3D11BlendState;
struct ID3D12Device;

namespace Engine::Graphic {
	enum BlendMode
	{
		BLEND_NONE,
		BLEND_ALPHA,
		BLEND_ADD,
		BLEND_ADDALPHA,
		BLEND_SUB,
		BLEND_SCREEN,
		BLEND_MAX
	};

	enum SamplerState
	{
		SAMPLER_LINEAR,
		SAMPLER_POINT,
		SAMPLER_MAX
	};

	enum DepthState
	{
		DEPTH_ENABLE_WRITE_TEST,
		DEPTH_ENABLE_TEST,
		DEPTH_DISABLE,
		DEPTH_MAX
	};

	class iDevice
	{
	public:
		virtual ~iDevice() = default;

		virtual bool Initialize() = 0;
		virtual void CreateRenderTarget() = 0;
		virtual void* GetDevice()const = 0;
		virtual void* GetDeviceContext()const = 0;
	};

	class DirectX11Device 
		: public iDevice
	{
	public:
		bool Initialize() override;
		void CreateRenderTarget() override;

		inline void* GetDevice()const override { return m_Device; }
		inline void* GetDeviceContext()const override { return m_DeviceContext; }
	private:
		ID3D11Device* m_Device;
		ID3D11DeviceContext* m_DeviceContext;
		ID3D11RasterizerState* m_pRasterizerState[3];
		ID3D11BlendState* m_pBlendState[BLEND_MAX];
		ID3D11SamplerState* m_pSamplerState[SAMPLER_MAX];
		ID3D11DepthStencilState* m_pDepthStencilState[DEPTH_MAX];
	};

	class DirectX12Device 
		: public iDevice 
	{
	public:
		bool Initialize() override;
		void CreateRenderTarget() override;
		inline void* GetDevice()const override { return m_Device; };
	private:
		ID3D12Device* m_Device;
	};
}

#endif // !_____Device_HXX_____
