//	ファイル名	：Direct3D.hxx
//	  概  要	：
//	作	成	者	：daigo
//	 作成日時	：2025/02/23 21:02:51
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/

// =-=-= インクルードガード部 =-=-=
#ifndef _____Direct3D_HXX_____
#define _____Direct3D_HXX_____

// =-=-= インクルード部 =-=-=
#include "../../Defines.hxx"
#include "../Singleton.hxx"

#include "Device.hxx"
#include "SwapChain.hxx"
#include "CommandQueue.hxx"
#include "Texture.hxx"
#include "Shader.hxx"



#ifdef SHIPPING
#include <Windows.h>
#endif // SHIPPING

namespace Engine::Graphic {
	class iGraphicsFactory
	{
	public:
		virtual ~iGraphicsFactory() = default;

		virtual void Initialize(HWND hWnd, uint16 width, uint16 height) = 0;
		virtual void RenderFrame() = 0;
		virtual void Cleanup() = 0;

		virtual convDevice GetDevice() = 0;
		virtual convDeviceContext GetDeviceContext() = 0;
		virtual convSwapChain GetSwapChain() = 0;

		virtual iTextureFactory* GetiTextureFactory() = 0;
		virtual iShaderFactory* GetiShaderFactory() = 0;

		virtual void SetRenderTarget(uint16 num, iRenderTarget** ppViews, iDepstStencil* pView) = 0;
	};

	class DirectX11GraphicsFactory
		:public iGraphicsFactory
	{
	public:
		void Initialize(HWND hWnd, uint16 width, uint16 height) override;
		void RenderFrame() override;
		void Cleanup() override;

		inline convDevice GetDevice()override { return m_Device.GetDevice(); }
		inline convDeviceContext GetDeviceContext()override { return m_Device.GetDeviceContext(); }
		inline convSwapChain GetSwapChain()override { return m_SwapChain.GetSwapChain(); }

		inline iTextureFactory* GetiTextureFactory()override { return
#ifdef DIRECTX11_PRJ
			New(DirectX11TextureFactory)
#else
			New(DirectX12TextureFactory)
#endif // DIRECTX11_PRJ
			; 
		}

		inline iShaderFactory* GetiShaderFactory() override { return
#ifdef DIRECTX11_PRJ
			New(DirectX11ShaderFactory)
#else
			New(DirectX12ShaderFactory)
#endif // DIRECTX11_PRJ
			;
		}

		void SetRenderTarget(uint16 num, iRenderTarget** ppViews, iDepstStencil* pView)override;
	private:
		DirectX11Device m_Device;
		DirectX11SwapChain m_SwapChain;
		DirectX11CommandQueue m_CommandQueue;
	};

	//class DirectX12Graphics
	//	:public iGraphicsAPI
	//{
	//public:
	//	void Initialize(HWND hWnd, int16 width, int16 height) override;
	//	void RenderFrame() override;
	//	void Cleanup() override;

	//	inline iDevice* GetiDevice() override { return &m_Device; }
	//private:
	//	DirectX12Device m_Device;
	//	DirectX12SwapChain m_SwapChain;
	//	DirectX12CommandQueue m_CommandQueue;
	//};


	class GraphicsManager final
		: public System::Singleton<GraphicsManager>
	{
		friend class System::Singleton<GraphicsManager>;
	public:
		GraphicsManager& CreateGraphicsAPI();
		inline iGraphicsFactory* operator->() { return m_GraphicsAPI.get(); }
		inline iGraphicsFactory* get() { return m_GraphicsAPI.get(); }
	private:
		GraphicsManager() {};
		~GraphicsManager() {};

		std::unique_ptr<iGraphicsFactory> m_GraphicsAPI; 
	};
}


#endif // !_____Direct3D_HXX_____
