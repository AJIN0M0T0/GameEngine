#include "SceneBase.hxx"
#include "../Engine/System/SceneManager.hxx"

iScene::iScene()
	: m_LoadComplete(false)
	, m_SceneComponent()
{
}

iScene::~iScene()
{
}

// ロード処理（並列前提）
void iScene::Loading(iScene** ppInstantChange)
{
	// 初期化処理
	FalseCheck(this->Init());

	// ロード完了フラグを立てる
	m_LoadComplete = true;

	// このクラスが即チェンジならチェンジさせる
	if (this == *ppInstantChange)
		Engine::System::SceneManager::GetInstance().ChangeScene(this);
}
