//	ファイル名	：SwapChain.hxx
//	  概  要	：
//	作	成	者	：daigo
//	 作成日時	：2025/02/28 23:47:25
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/

// =-=-= インクルードガード部 =-=-=
#ifndef _____SwapChain_HXX_____
#define _____SwapChain_HXX_____

// =-=-= インクルード部 =-=-=

// 前方定義
struct IDXGISwapChain1;
struct IDXGISwapChain4;

namespace Engine {
	namespace Graphic {
		class iSwapChain
		{
		public:
			virtual ~iSwapChain() = default;

			virtual void Create() = 0;
			virtual void Present() = 0;
		};

		
		class DirectX11SwapChain 
			: public iSwapChain
		{
		public:
			void Create() override;
			void Present() override;
		private:
			IDXGISwapChain1* m_swapChain;
		};


		class DirectX12SwapChain 
			: public iSwapChain
		{
		public:
			void Create() override;
			void Present() override;
		private:
			std::unique_ptr<IDXGISwapChain4> m_SwapChain;
		};
	}
}

#endif // !_____SwapChain_HXX_____
