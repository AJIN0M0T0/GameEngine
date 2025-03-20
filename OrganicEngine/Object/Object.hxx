//	ファイル名	：Object.hxx
//	  概  要	：
//	作	成	者	：daigo
//	 作成日時	：2025/03/14 3:32:07
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/

// =-=-= インクルードガード部 =-=-=
#ifndef _____Object_HXX_____
#define _____Object_HXX_____

// =-=-= インクルード部 =-=-=
#include <deque>
#include "../Engine/Math/Transform.hxx"

namespace Engine::System {
	class SceneManager;
};

class iObject
{
	friend class Engine::System::SceneManager;
public_Func
	iObject* GetParent()const;
	void AddChild(iObject* pChild);

	/// @brief 
	/// @tparam TypeObject 
	/// @tparam  
	/// @return 
	template <typename TypeObject, typename = std::enable_if_t<std::is_base_of_v<iObject, TypeObject>>>
	TypeObject& thisCreateObject() {
		 TypeObject* pObject = New(TypeObject);
		this->AddChild(pObject);
		AddInitQueue(pObject);
		return *pObject;
	}

	/// @brief 初期化処理
	/// @return 成功ならtrue
	virtual bool Init() = 0;
	/// @brief 更新処理
	virtual void Update() = 0;
	/// @brief 描画処理
	/// @param Parentworld 自身のワールド座標
	virtual void Draw(const Engine::Math::Matrix& world) = 0;

	void Delete();
	void RemoveChild(iObject*);

	bool IsActive()const;
	void SetActive(bool IsActive);

	inline Engine::Math::Transform& GetTransform() { return m_Transform; }

	const ID GetID();

protected_Func
	iObject();
	virtual ~iObject();
	
	void UpdateChildren();
	void DrawChildren(const Engine::Math::Matrix& world);

private_Func
	void AddInitQueue(iObject* obj);

private_Var
	bool m_IsActive;
	Engine::unique_ID m_ID;
	iObject* m_pParent;
	std::deque<iObject*> m_Children;
	Engine::Math::Transform m_Transform;
};

#endif // !_____Object_HXX_____
