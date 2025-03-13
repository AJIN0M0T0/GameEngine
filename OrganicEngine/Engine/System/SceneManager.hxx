//	ファイル名	：SceneManager.hxx
//	  概  要	：
//	作	成	者	：daigo
//	 作成日時	：2025/03/14 3:14:19
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/

// =-=-= インクルードガード部 =-=-=
#ifndef _____SceneManager_HXX_____
#define _____SceneManager_HXX_____

// =-=-= インクルード部 =-=-=
#include <vector>
#include <type_traits>
#include "Singleton.hxx"
#include "ThreadPool.hxx"
#include "../../Object/SceneBase.hxx"

namespace Engine::System {
	class SceneManager final
		: public Singleton<SceneManager>
	{
		friend class Singleton<SceneManager>;
		friend class iObject;
	public_Func
		void Update();
	
		template<typename SceneObject, typename = std::enable_if_t<std::is_base_of_v<iScene, SceneObject>>>
		inline void StartLoading()
		{
			// 既にロード済みシーンならば生成しない
			for (const auto& elem : m_LoadScenes) {
				if (dynamic_cast<SceneObject*>(elem.get())) {
					return;
				}
			}
			m_LoadScenes.push_back(std::make_unique<SceneObject>());

			ThreadPool::GetInstance().AddPool([this]() {m_NextScene->Loading(&m_pInstantChange); });
		}

		template<typename SceneObject, typename = std::enable_if_t<std::is_base_of_v<iScene, SceneObject>>>
		inline void ChangeScene()
		{
			// 既にロード済みか調べる
			for (int i = 0; i < m_LoadScenes.size(); i++) {
				if (typeid(SceneObject) == typeid(m_LoadScenes[i].get())) {
					if (m_LoadScenes[i]->m_LoadComplete);
					{
						m_NextScene.swap(m_LoadScenes[i]);
						m_LoadScenes.erase(m_LoadScenes.begin() + i);
						return;
					}
				}
			}
			// ロードしていない場合はロードする
			m_NextScene = std::make_unique<SceneObject>();
			m_NextScene->Init();
			m_NextScene->m_LoadComplete = true;

			//m_LoadScenes.push_back(std::make_unique<SceneObject>());
			//m_pInstantChange = m_LoadScenes.back().get();
			//ThreadPool::GetInstance().AddPool([this]() {m_pInstantChange->Loading(&m_pInstantChange); });
		}

		inline void ChangeScene(iScene* pScene)
		{
			for (int i = 0; i < m_LoadScenes.size(); i++) {
				if (pScene == m_LoadScenes[i].get()) {
					m_NextScene.swap(m_LoadScenes[i]);
					m_LoadScenes.erase(m_LoadScenes.begin() + i);
					return;
				}
			}
		}

		inline iScene* GetNowScene() const { return m_NowScene.get(); }

	private_Func
		SceneManager();
		~SceneManager();
		
	private_Var
		iScene* m_pInstantChange;

		std::unique_ptr<iScene> m_NowScene;
		std::unique_ptr<iScene> m_NextScene;
		std::vector<std::unique_ptr<iScene>> m_LoadScenes;
		std::queue<iObject*> m_InitQueue;
	};
};

#endif // !_____SceneManager_HXX_____
