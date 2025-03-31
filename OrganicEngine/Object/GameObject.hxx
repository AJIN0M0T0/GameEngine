//	ファイル名	：GameObject.hxx
//	  概  要	：
//	作	成	者	：daigo
//	 作成日時	：2025/03/14 3:32:17
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/

// =-=-= インクルードガード部 =-=-=
#ifndef _____GameObject_HXX_____
#define _____GameObject_HXX_____

// =-=-= インクルード部 =-=-=
#include "Object.hxx"
#include "../Component/Component.hxx"

class GameObject 
	: public iObject
{
public_Func
	GameObject();
	~GameObject();

	GameObject& operator=(const GameObject&) = delete;
	GameObject& operator=(GameObject&&) = delete;

	/// @brief コンポーネントの追加
	/// @tparam TypeComp 追加するコンポーネントの型
	/// @return 追加したコンポーネントのポインタ
	template<typename TypeComp, typename = std::enable_if_t<std::is_base_of_v<iComponent, TypeComp>>>
	inline TypeComp* AddComponent()
	{
		std::unique_ptr<TypeComp> pComp(New(TypeComp));
		pComp->m_pObject = this;
		m_Components.push_back(std::move(pComp));
		return static_cast<TypeComp*>(m_Components.back().get());
	}

	/// @brief コンポーネントの取得
	/// @tparam TypeComp 取得するコンポーネントの型
	/// @return 取得したコンポーネントのポインタ
	template<typename TypeComp, typename = std::enable_if_t<std::is_base_of_v<iComponent, TypeComp>>>
	inline TypeComp* GetComponent()
	{
		for (const auto& elem : m_Components)
		{
			if (dynamic_cast<TypeComp*>(elem.get()))
				return static_cast<TypeComp*>(elem.get());
		}
		DebugBreakPoint_
			return nullptr;
	}

	/// @brief 名前の設定
	/// @param name 設定する名前
	void SetName(const Name& name);
	/// @brief 名前の取得
	/// @return 名前
	const Name& GetName();
	/// @brief タグの取得
	/// @return タグ
	Tag GetTag();
	/// @brief タグの設定
	/// @param tag 設定するタグ
	void SetTag(Tag tag);

	virtual bool Init()override;
	virtual void Update()override;
	/// @brief 描画処理
	/// @param Parentworld 自身のワールド座標
	virtual void Draw(const Engine::Math::Matrix& world);

private_Var
	Name m_Name;						// オブジェクト名
	unsigned m_Tag;						// タグ
	std::deque<std::unique_ptr<iComponent>> m_Components;	// 追加されたコンポーネント
};

#endif // !_____GameObject_HXX_____
