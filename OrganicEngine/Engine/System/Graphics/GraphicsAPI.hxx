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

namespace Engine {
	namespace Graphic {
		class iGraphicsAPI
		{
		public:
			virtual ~iGraphicsAPI() = default;

			virtual void Initialize(HWND hWnd, int16 width, int16 height) = 0;
			virtual void RenderFrame() = 0;
			virtual void Cleanup() = 0;

			virtual iDevice* GetiDevice() = 0;
		};

		class GraphicsDirectX11
			:public iGraphicsAPI
		{
		public:
			void Initialize(HWND hWnd, int16 width, int16 height) override;
			void RenderFrame() override;
			void Cleanup() override;

			inline iDevice* GetiDevice() override { return &m_Device; }
		private:
			DirectX11Device m_Device;
			DirectX11SwapChain m_SwapChain;
			DirectX11CommandQueue m_CommandQueue;
		};

		class DirectX12Graphics
			:public iGraphicsAPI
		{
		public:
			void Initialize(HWND hWnd, int16 width, int16 height) override;
			void RenderFrame() override;
			void Cleanup() override;

			inline iDevice* GetiDevice() override { return &m_Device; }
		private:
			DirectX12Device m_Device;
			DirectX12SwapChain m_SwapChain;
			DirectX12CommandQueue m_CommandQueue;
		};


		class GraphicsFactory final
			: public System::Singleton<GraphicsFactory>
		{
			friend class System::Singleton<GraphicsFactory>;
		public:
			GraphicsFactory& CreateGraphicsAPI();
			inline iGraphicsAPI* operator->() { return m_GraphicsAPI.get(); }
			inline iGraphicsAPI* get() { return m_GraphicsAPI.get(); }
		private:
			GraphicsFactory() {};
			~GraphicsFactory() {};

			std::unique_ptr<iGraphicsAPI> m_GraphicsAPI; 
		};
	}
}

#endif // !_____Direct3D_HXX_____
