//	ファイル名	：SwapChain.hxx
//	  概  要	：
//	作	成	者	：daigo
//	 作成日時	：2025/02/28 23:47:25
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/

// =-=-= インクルードガード部 =-=-=
#ifndef _____SwapChain_HXX_____
#define _____SwapChain_HXX_____

// =-=-= インクルード部 =-=-=

namespace Engine {
	namespace Graphic {
		class iSwapChain
		{
		public:
			virtual ~iSwapChain() = default;

			virtual void Present() = 0;
		};

		// 前方定義
		class IDXGISwapChain;

		class DirectX11SwapChain 
			: public iSwapChain
		{
		public:
			void Present() override;
		private:
			std::unique_ptr<IDXGISwapChain> m_swapChain;
		};

		// 前方定義
		class IDXGISwapChain4;

		class DirectX12SwapChain 
			: public iSwapChain
		{
		public:
			void Present() override;
		private:
			std::unique_ptr<IDXGISwapChain4> m_SwapChain;
		};
	}
}

#endif // !_____SwapChain_HXX_____
