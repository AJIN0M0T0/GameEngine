#include "Supervision.hxx"

// =-=-= インクルード部 =-=-=
#include "Window.hxx"
#include "Graphics/GraphicsAPI.hxx"
#include "ThreadPool.hxx"
#include "SceneManager.hxx"

// =-=-= インスタンス変数の実体化 =-=-=
std::stack<void(*)()> Engine::System::Supervision::m_finalizers;//終了処理
std::mutex Engine::System::Supervision::gMutex;// 排他制御用


/// @brief シングルトンの初期化処理
/// @return 成功ならtrue
bool Engine::System::Supervision::Initialize()
{
	bool Success = true;

	//Success &= FalseCheck(~~~class::CreateInstance().Init());	←例
	Window::CreateInstance();
	Graphic::GraphicsFactory& graph = Graphic::GraphicsFactory::CreateInstance();
	graph.CreateGraphicsAPI();

	ThreadPool::CreateInstance();


	return Success;
}

/// @brief シングルトンの更新処理
void Engine::System::Supervision::Updater()
{// ここに更新処理を追加
	ThreadPool::GetInstance().Update(); 
	
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

void Engine::System::Supervision::Drawings()
{
	Graphic::GraphicsFactory& api =	Graphic::GraphicsFactory::GetInstance();

	iScene* scene = Engine::System::SceneManager::GetInstance().GetNowScene();

///////////////////////////////////////////
	koko;

	Engine::Math::Matrix origin = { {0.0f,0.0f,0.0f,0.0f},{0.0f,0.0f,0.0f,0.0f},{0.0f,0.0f,0.0f,0.0f},{0.0f,0.0f,0.0f,0.0f} };
	scene->Draw(origin);

	api->RenderFrame();
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
