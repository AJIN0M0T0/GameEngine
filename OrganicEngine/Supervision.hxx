//	ファイル名	：Singleton.hxx
//	  概  要	：
//	作	成	者	：daigo
//	 作成日時	：2025/02/25 22:29:33
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/

// =-=-= インクルードガード部 =-=-=
#ifndef _____Supervision_hxx_____
#define _____Supervision_hxx_____

// =-=-= インクルード部 =-=-=
#include <stack>
#include <mutex>

/// @brief シングルトンの最終処理を行うクラス
class Supervision final
{
	template<typename Type> friend class Singleton;
public:
	/// @brief 初期化処理を行う
	/// @return 成功したらtrue
	static bool Initialize();
	/// @brief 更新処理を行う
	static void Updater();
	/// @brief 終了処理を行う
	static void Finalize();

private:
	/// @brief 終了処理を追加する
	/// @param func 終了処理
	static void addFinalizer(void(*func)());
private:
	static std::stack<void(*)()> m_finalizers;//終了処理
	static std::mutex gMutex;// 排他制御用
};

#endif // !_____Supervision_hxx_____
