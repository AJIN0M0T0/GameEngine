#include "Supervision.hxx"

// =-=-= インクルード部 =-=-=
#include "Window.hxx"


// =-=-= インスタンス変数の実体化 =-=-=
std::stack<void(*)()> Engine::System::Supervision::m_finalizers;//終了処理
std::mutex Engine::System::Supervision::gMutex;// 排他制御用


/// @brief シングルトンの初期化処理
/// @return 成功ならtrue
bool Engine::System::Supervision::Initialize()
{
	bool Success = true;

	//Success &= FalseCheck(~~~class::CreateInstance().Init());	←例
	Success &= FalseCheck(Window::CreateInstance().Init());

	return Success;
}

/// @brief シングルトンの更新処理
void Engine::System::Supervision::Updater()
{// ここに更新処理を追加
	
	
	return;
}

/*\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\

							！！！！！　以下編集不要　！！！！！

\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\*/

/// @brief 終了処理を保存
/// @param func 終了処理
void Engine::System::Supervision::_addFinalizer(void(*func)())
{
	std::lock_guard<std::mutex> lock(gMutex);// 排他制御
	m_finalizers.push(func);// 終了処理を追加
}

/// @brief 終了処理を行う
void Engine::System::Supervision::Finalize()
{
	std::lock_guard<std::mutex> lock(gMutex);// 排他制御

	while (!m_finalizers.empty()) {// 終了処理を逆順に実行
		m_finalizers.top()();
		m_finalizers.pop();
	}
}
