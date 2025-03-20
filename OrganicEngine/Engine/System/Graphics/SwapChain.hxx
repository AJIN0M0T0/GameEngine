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

union convSwapChain {
	IDXGISwapChain1* p11SC;
	IDXGISwapChain4* p12SC;
};

namespace Engine::Graphic {
		class iSwapChain
		{
		public:
			virtual ~iSwapChain() = default;

			virtual void Create() = 0;
			virtual void Present() = 0;

			virtual convSwapChain GetSwapChain() = 0;
		};

		
		class DirectX11SwapChain 
			: public iSwapChain
		{
		public:
			void Create() override;
			void Present() override;

			inline convSwapChain GetSwapChain() override { return { m_swapChain }; }
		private:
			IDXGISwapChain1* m_swapChain;
		};


		class DirectX12SwapChain 
			: public iSwapChain
		{
		public:
			void Create() override;
			void Present() override;

			inline convSwapChain GetSwapChain() override { convSwapChain ret; ret.p12SC = m_SwapChain; return ret; }
		private:
			IDXGISwapChain4* m_SwapChain;
		};
	}

#endif // !_____SwapChain_HXX_____
