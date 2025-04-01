/**
 * @file Collision.hxx
 * @brief 
 * @author yuki57-46
 * @date 2025-03-23
 */

// =-=-= インクルードガード部 =-=-=
#ifndef ____COLLISION_HXX____
#define ____COLLISION_HXX____

// =-=-= インクルード部 =-=-=
#include "Component.hxx"
#include "../Object/Object.hxx"
#include <list>
#include <map>
#include <vector>
#include <functional>
#include <string>
#include <memory>
#include <btBulletDynamicsCommon.h>

class iCollision
	: public iComponent
{
public:
	iCollision();
	~iCollision();

	bool Init() override;
	void Update() override;


	/// 各オブジェクトの持つUIDで参照
	iObject* IsHit(ID id);

	/// 各オブジェクトに持たせることのできるタグや名前で参照 
	std::list<iObject*> HitObject(Tag tag);
	std::list<iObject*> IsHit(Name name);

	/// 指定したID,Tag,Nameのいずれかに当たった時に呼ぶ関数(ラムダ式)
	void SetHitEvent(ID id, std::function<void()> func);
	void SetHitEvent(Tag tag, std::function<void()> func);
	void SetHitEvent(Name name, std::function<void()> func);

	virtual btCollisionShape* GetCollisionShape() const = 0;

	iObject* m_pObject = nullptr;
protected:
	btCollisionObject* m_collisionObject = nullptr;

	std::map<ID, std::function<void()>> m_hitEventID;
	std::map<Tag, std::function<void()>> m_hitEventTag;
	std::map<Name, std::function<void()>> m_hitEventName;
	//static std::vector<std::pair<btCollisionObject*, btCollisionObject*>> m_collisionPairs;

	//std::vector<btCollisionObject*> m_collisionObjects;

private:
	std::function<void()> m_func;

	std::unique_ptr<btBroadphaseInterface> m_broadphase;
	std::unique_ptr<btDefaultCollisionConfiguration> m_collisionConfiguration;
	std::unique_ptr<btCollisionDispatcher> m_dispatcher;

	//static int collisionObjectCount; // 衝突オブジェクトの数


};

class CubeCollision
	: public iCollision
{
public:
	CubeCollision();
	~CubeCollision();
	bool Init() override;
	void Update() override;

	btCollisionShape* GetCollisionShape() const override;

	/**
	 * @brief ボックスの半径を設定
	 * @param[in] x  x軸方向の半径
	 * @param[in] y  y軸方向の半径
	 * @param[in] z  z軸方向の半径
	 */
	inline void SetHalfExtents(const float x, const float y, const float z)
	{
		m_halfExtents = btVector3(x, y, z);
		m_boxShape = new btBoxShape(m_halfExtents);
	}

private:
	btBoxShape* m_boxShape = nullptr;
	btVector3 m_halfExtents; // ボックスの半径
};

class CapsuleCollision
	: public iCollision
{
public:
	CapsuleCollision();
	~CapsuleCollision();
	bool Init() override;
	void Update() override;

	btCollisionShape* GetCollisionShape() const override;

	/**
	 * @brief カプセルの半径と高さを設定
	 * @param[in] radius  半径
	 * @param[in] height  高さ
	 */
	void SetRadiusAndHeight(const float radius, const float height)
	{
		m_radius = radius;
		m_height = height;
		m_capsuleShape = new btCapsuleShape(m_radius, m_height);
	}

private:
	btCapsuleShape* m_capsuleShape = nullptr;
	float m_radius, m_height;

};

class MeshCollision
	: public iCollision
{
public:
	MeshCollision();
	~MeshCollision();
	bool Init() override;
	void Update() override;

	btCollisionShape* GetCollisionShape() const override;

	bool LoadModel(const std::string& path);

private:
	btBvhTriangleMeshShape* m_meshShape = nullptr;
	btTriangleMesh* m_triangleMesh = nullptr;
	std::string m_modelName;
};



#endif // !____COLLISION_HXX____
