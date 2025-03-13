//	ファイル名	：SceneBase.hxx
//	  概  要	：
//	作	成	者	：daigo
//	 作成日時	：2025/03/14 3:28:57
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/

// =-=-= インクルードガード部 =-=-=
#ifndef _____SceneBase_HXX_____
#define _____SceneBase_HXX_____

// =-=-= インクルード部 =-=-=
#include "Object.hxx"
#include "../Component/Component.hxx"

namespace Engine::System {
	class SceneManager;
};

class iScene 
	:public iObject
{
	friend class Engine::System::SceneManager;
public_Func
	iScene();
	virtual ~iScene();

	template<typename TypeComp, typename = std::enable_if_t<std::is_base_of_v<iComponent, TypeComp>>>
	inline TypeComp* AddSceneComponent()
	{
		std::unique_ptr<TypeComp> pComp(New(TypeComp));
		pComp->m_pBaseObject = this;
		m_SceneComponent = std::move(pComp);
		return m_SceneComponent.get();
	}

private_Func
	void Loading(iScene** ppInstantChange);

private_Var
	bool m_LoadComplete;
	std::unique_ptr<iComponent> m_SceneComponent;
};

#endif // !_____SceneBase_HXX_____
