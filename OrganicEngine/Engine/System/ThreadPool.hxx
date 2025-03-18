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
		/// @brief 更新処理　毎ループ処理がある場合完了確認を行う
		void Update();

		/// @brief スレッドプールに関数を追加
		/// @param func スレッドに投げたい関数。ラムダ式も可。
		/// @param IsNoEvery 毎ループ処理をするならtrue, デフォルトでfalse
		void AddPool(std::function<void()> func,bool IsEvery = false);
		FuncInfo GetPoolFead();

	private_Func
		ThreadPool();
		~ThreadPool();

		/// @brief 各スレッドのループ処理
		static void poolloop(bool& EveryFlag);

	private_Var
		// スレッドの継続フラグ
		static bool ThreadContinue;
		
		uint16 m_ThreadCount;		// スレッド数
		std::shared_mutex m_Mutex;	// ミューテックス
		std::vector<std::unique_ptr<std::thread>> m_Thread;	// スレッド
		bool* m_EveryFlags;		// 毎ループ処理フラグ
		
		std::queue<FuncInfo> m_Pool;
	};
};

#endif // !_____ThreadPool_HXX_____
