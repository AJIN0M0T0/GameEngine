//	ファイル名	：ThreadPool.hxx
//	  概  要	：
//	作	成	者	：daigo
//	 作成日時	：2025/03/14 1:45:50
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/

// =-=-= インクルードガード部 =-=-=
#ifndef _____ThreadPool_HXX_____
#define _____ThreadPool_HXX_____

// =-=-= インクルード部 =-=-=
#include "Singleton.hxx"
#include <vector>
#include <shared_mutex>
#include <functional>
#include <queue>

namespace {
	struct FuncInfo {
		std::function<void()> func;
		bool IsEvery;
	};
}

namespace Engine::System {
	class ThreadPool : public Engine::System::Singleton<ThreadPool>
	{
		friend class Engine::System::Singleton<ThreadPool>;
	public_Func
		void Update();

		void AddPool(std::function<void()> func,bool IsEvery = false);
		FuncInfo GetPoolFead();

	private_Func
		ThreadPool();
		~ThreadPool();
		static void poolloop(bool& EveryFlag);

	private_Var
		static bool ThreadContinue;

		uint16 m_ThreadCount;

		std::shared_mutex m_Mutex;
		std::vector<std::unique_ptr<std::thread>> m_Thread;
		bool* m_EveryFlags;
		std::queue<FuncInfo> m_Pool;
	};
};

#endif // !_____ThreadPool_HXX_____
