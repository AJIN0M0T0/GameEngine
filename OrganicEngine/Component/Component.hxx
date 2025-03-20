//	ファイル名	：Component.hxx
//	  概  要	：
//	作	成	者	：daigo
//	 作成日時	：2025/03/14 3:54:24
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/

// =-=-= インクルードガード部 =-=-=
#ifndef _____Component_HXX_____
#define _____Component_HXX_____

class iObject;
class GameObject;
class iScene;

class iComponent
{
	friend class GameObject;
	friend class iScene;
public_Func
	iComponent() :m_pObject(nullptr) {};
	virtual ~iComponent() = default;

	virtual bool Init() = 0;
	virtual void Update() = 0;

	/// @brief GameObjectを取得する
	/// @brief 注意※SceneComponentの場合エラー
	/// @return 所属ゲームオブジェクト
	iObject* GetGameObject();

protected_Var
	iObject* m_pObject;
};

#endif // !_____Component_HXX_____
