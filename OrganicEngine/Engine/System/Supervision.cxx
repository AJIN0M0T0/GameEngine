#include "Supervision.hxx"

// =-=-= インクルード部 =-=-=
#include <d3d11.h>
#include "Window.hxx"
#include "Graphics/GraphicsAPI.hxx"
#include "ThreadPool.hxx"
#include "SceneManager.hxx"
#include "Graphics/Shader.hxx"
#include "CameraManager.h"
#include "InputDeviceManager.h"

#include "../../Object/SceneObject/testScene.hxx"

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
	Graphic::GraphicsManager& graph = Graphic::GraphicsManager::CreateInstance();
	graph.CreateGraphicsAPI();
	graph->Initialize(Window::GetInstance().GetHWND(), 1280, 720);
	Graphic::TextureManager::CreateInstance().SetFactory(graph.GetInstance()->GetiTextureFactory());
	Graphic::ShaderManager::CreateInstance().SetFactory(graph.GetInstance()->GetiShaderFactory());
	InputDeviceManager::CreateInstance().Init();
	CameraManager::CreateInstance();

	ThreadPool::CreateInstance();
	SceneManager::CreateInstance();
	SceneManager::GetInstance().ChangeScene<testScene>();

	return Success;
}

/// @brief シングルトンの更新処理
void Engine::System::Supervision::Updater()
{// ここに更新処理を追加
	ThreadPool::GetInstance().Update(); // スレッドプールの更新処理　※必ず先頭に記述

	InputDeviceManager::GetInstance().Update();

	SceneManager::GetInstance().Update();
	
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
	Graphic::GraphicsManager& api =	Graphic::GraphicsManager::GetInstance();
	Graphic::TextureManager& tex = Graphic::TextureManager::GetInstance();
	iScene* scene = Engine::System::SceneManager::GetInstance().GetNowScene();

	auto rtv = tex.RecordRenderTarget("default");
	auto dsv = tex.RecordDepstStencil("default");
	Math::fVec4 clearColor = { 0.5f,0.2f,0.3f,1.0f };

	api->GetDeviceContext().p11DC
		->ClearRenderTargetView(rtv->GetView().p11RTV, clearColor.v);
	api->GetDeviceContext().p11DC
		->ClearDepthStencilView(dsv->GetView().p11DSV, D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);

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
