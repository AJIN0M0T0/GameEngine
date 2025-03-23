#include "Collision.hxx"
#include "../Object/Object.hxx"
#include "../Engine/Math/Vectors.hxx"
#include <btBulletDynamicsCommon.h>
#include <list>
#include <functional>
#include <DirectXMath.h>

iCollision::iCollision()
	: m_func(nullptr)
	, m_collisionObject(nullptr)
{
}

iCollision::~iCollision()
{
}

bool iCollision::Init()
{
	// 衝突オブジェクトの生成
	m_collisionObject = new btCollisionObject();
	m_collisionObject->setCollisionShape(GetCollisionShape());
	
	// 衝突オブジェクトの位置と姿勢の設定
	btTransform transform;
	transform.setIdentity(); // 単位行列
	m_collisionObject->setWorldTransform(transform);

	// 衝突オブジェクトにユーザーポインタを設定(衝突時に自身を識別するため)
	m_collisionObject->setUserPointer(m_pObject);

	// Bulletの衝突検出ワールドに登録
	//g_pPhysics->GetDynamicsWorld()->addCollisionObject(m_collisionObject);
	m_collisionWorld->addCollisionObject(m_collisionObject);

	return true;
}

void iCollision::Update()
{
	// 衝突オブジェクトの位置と姿勢を更新
	btTransform transform;
	transform.setIdentity();

	// ワールド座標系の位置
	Engine::Math::fVec3 worldPos = m_pObject->GetTransform().GetWorldPosition();
	transform.setOrigin({ worldPos.x, worldPos.y, worldPos.z });

	// ワールド座標系の回転
	Engine::Math::fVec3 worldRot = m_pObject->GetTransform().GetWorldRotation();
	DirectX::XMVECTOR quat = DirectX::XMQuaternionRotationRollPitchYaw(worldRot.x, worldRot.y, worldRot.z);
	DirectX::XMFLOAT4 quat4;
	DirectX::XMStoreFloat4(&quat4, quat);
	transform.setRotation(btQuaternion(quat4.x, quat4.y, quat4.z, quat4.w));

	// Bulletの衝突検出ワールドに更新を通知
	m_collisionObject->setWorldTransform(transform);
}

iObject* iCollision::IsHit(ID id)
{
	for (auto& pair : m_collisionPairs)
	{
		btCollisionObject* objA = pair.first;
		btCollisionObject* objB = pair.second;

		iObject* pObjectA = static_cast<iObject*>(objA->getUserPointer());
		iObject* pObjectB = static_cast<iObject*>(objB->getUserPointer());

		if (pObjectA == m_pObject && pObjectB->GetID() == id)
		{
			return pObjectB->GetParent();
		}

		if (pObjectB == m_pObject && pObjectA->GetID() == id)
		{
			return pObjectA->GetParent();
		}
	}

    return nullptr;
}

std::list<iObject*> iCollision::HitObject(Tag tag)
{
	std::list<iObject*> hitObjects;
	auto& collisionPairs = m_collisionPairs;
	
	for (auto& pair : collisionPairs)
	{
		btCollisionObject* objctA = pair.first;
		btCollisionObject* objctB = pair.second;

		iObject* pObjectA = static_cast<iObject*>(objctA->getUserPointer());
		iObject* pObjectB = static_cast<iObject*>(objctB->getUserPointer());

		//if (pObjectA == m_pObject && pObjectB->GetTag() == tag)
		//{
		//	hitObjects.push_back(pObjectB->GetParent());
		//}

		//if (pObjectB == m_pObject && pObjectA->GetTag() == tag)
		//{
		//	hitObjects.push_back(pObjectA->GetParent());
		// }
	}

	return hitObjects;
}

std::list<iObject*> iCollision::IsHit(Name name)
{
	std::list<iObject*> hitObjects;
	auto& collisionPairs = m_collisionPairs;

	for (auto& pair : collisionPairs)
	{
		btCollisionObject* objctA = pair.first;
		btCollisionObject* objctB = pair.second;
		
		iObject* pObjectA = static_cast<iObject*>(objctA->getUserPointer());
		iObject* pObjectB = static_cast<iObject*>(objctB->getUserPointer());
		
		//if (pObjectA == m_pObject && pObjectB->GetName() == name)
		//{
		//	hitObjects.push_back(pObjectB->GetParent());
		//}
		//if (pObjectB == m_pObject && pObjectA->GetName() == name)
		//{
		//	hitObjects.push_back(pObjectA->GetParent());
		//}
	}



	return std::list<iObject*>();
}

void iCollision::SetHitEvent(ID id, std::function<void()> func)
{
	m_hitEventID[id] = func;
}

void iCollision::SetHitEvent(Tag tag, std::function<void()> func)
{
	m_hitEventTag[tag] = func;
}

void iCollision::SetHitEvent(Name name, std::function<void()> func)
{
	m_hitEventName[name] = func;
}

CubeCollision::CubeCollision()
{
}

CubeCollision::~CubeCollision()
{
}

bool CubeCollision::Init()
{
    return false;
}

void CubeCollision::Update()
{
}

btCollisionShape* CubeCollision::GetCollisionShape() const
{
	return m_boxShape;
}



CapsuleCollision::CapsuleCollision()
{
}

CapsuleCollision::~CapsuleCollision()
{
}

bool CapsuleCollision::Init()
{
    return false;
}

void CapsuleCollision::Update()
{
}

btCollisionShape* CapsuleCollision::GetCollisionShape() const
{
	return m_capsuleShape;
}


MeshCollision::MeshCollision()
{
}

MeshCollision::~MeshCollision()
{
}

bool MeshCollision::Init()
{
    return false;
}

void MeshCollision::Update()
{
}

btCollisionShape* MeshCollision::GetCollisionShape() const
{
	return m_meshShape;
}


