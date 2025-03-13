#include "SceneManager.hxx"

using namespace Engine::System;

SceneManager::SceneManager()
	: m_NowScene()
	, m_NextScene()
	, m_LoadScenes()
	, m_InitQueue()
{

}

SceneManager::~SceneManager()
{
	m_LoadScenes.clear();
}

void SceneManager::Update()
{
	if (m_NextScene) {
		m_NowScene.release();
		m_NowScene = std::move(m_NextScene);
	}
	if (m_NowScene) {
		while (!m_InitQueue.empty())
		{
			m_InitQueue.front()->Init();
			m_InitQueue.pop();
		}
		m_NowScene->UpdateChildren();
	}
}
