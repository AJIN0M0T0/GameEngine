//	ファイル名	：CommandQueue.hxx
//	  概  要	：
//	作	成	者	：daigo
//	 作成日時	：2025/02/28 23:48:23
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/

// =-=-= インクルードガード部 =-=-=
#ifndef _____CommandQueue_HXX_____
#define _____CommandQueue_HXX_____

// =-=-= インクルード部 =-=-=

namespace Engine::Graphic {
		class iCommandQueue
		{
		public:
			virtual ~iCommandQueue() = default;

			virtual void Execute() = 0;
		};

		class DirectX11CommandQueue
			: public iCommandQueue
		{
		public:
			void Execute() override;
		};

		class ID3D12CommandQueue;

		class DirectX12CommandQueue
			: public iCommandQueue
		{
		public:
			void Execute() override;
		private:
			std::unique_ptr<ID3D12CommandQueue> m_CommandQueue;
		};
}

#endif // !_____CommandQueue_HXX_____
