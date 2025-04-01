#include "Collision.hxx"
#include "../Object/Object.hxx"
#include "../Engine/Math/Vectors.hxx"
#include "../Object/GameObject.hxx"
#include <btBulletDynamicsCommon.h>
#include <list>
#include <functional>
#include <memory>
#include <DirectXMath.h>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>


static std::vector<std::pair<btCollisionObject*, btCollisionObject*>> m_collisionPairs;
static int collisionObjectCount;
std::vector<btCollisionObject*> m_collisionObjects;
btCollisionWorld* m_collisionWorld = nullptr;


iCollision::iCollision()
	: m_func(nullptr)
	, m_collisionObject(nullptr)
	//, m_collisionWorld(nullptr)
	, m_broadphase(nullptr)
	, m_collisionConfiguration(nullptr)
	, m_dispatcher(nullptr)
	, m_pObject(nullptr)
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

	// CollisionWorldを作成

	m_broadphase = std::make_unique<btDbvtBroadphase>();
	m_collisionConfiguration = std::make_unique<btDefaultCollisionConfiguration>();
	m_dispatcher = std::make_unique<btCollisionDispatcher>(m_collisionConfiguration.get());
	m_collisionWorld = new btCollisionWorld(m_dispatcher.get(), m_broadphase.get(), m_collisionConfiguration.get());


	// Bulletの衝突検出ワールドに登録
	//g_pPhysics->GetDynamicsWorld()->addCollisionObject(m_collisionObject);
	m_collisionWorld->addCollisionObject(m_collisionObject);

	// 衝突オブジェクトを登録
	m_collisionObjects.push_back(m_collisionObject);


	
	// 衝突オブジェクトの数をカウント
	collisionObjectCount++;


	// 衝突ペアを登録
	for (auto& existingObject : m_collisionObjects)
	{
		if (existingObject == m_collisionObject)
			continue;
		m_collisionPairs.push_back(std::make_pair(existingObject, m_collisionObject));
	}

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

	// 衝突検出
	m_collisionWorld->performDiscreteCollisionDetection();


	// 衝突ペアをチェックし、対応する関数を呼ぶ
	int numManifolds = m_collisionWorld->getDispatcher()->getNumManifolds();
	for (int i = 0; i < numManifolds; ++i)
	{
		btPersistentManifold* contactManifold = m_collisionWorld->getDispatcher()->getManifoldByIndexInternal(i);
		const btCollisionObject* objA = contactManifold->getBody0();
		const btCollisionObject* objB = contactManifold->getBody1();

		iObject* pObjectA = static_cast<iObject*>(objA->getUserPointer());
		iObject* pObjectB = static_cast<iObject*>(objB->getUserPointer());

		GameObject* pGameObjectA = reinterpret_cast<GameObject*>(objA->getUserPointer());
		GameObject* pGameObjectB = reinterpret_cast<GameObject*>(objB->getUserPointer());

		if (pObjectA == m_pObject)
		{
			auto it = m_hitEventID.find(pObjectB->GetID());
			if (it != m_hitEventID.end())
			{
				it->second();
			}
			auto it2 = m_hitEventTag.find(pGameObjectB->GetTag());
			if (it2 != m_hitEventTag.end())
			{
				it2->second();
			}
			auto it3 = m_hitEventName.find(pGameObjectB->GetName());
			if (it3 != m_hitEventName.end())
			{
				it3->second();
			}
		}

		if (pObjectB == m_pObject)
		{
			auto it = m_hitEventID.find(pObjectA->GetID());
			if (it != m_hitEventID.end())
			{
				it->second();
			}
			auto it2 = m_hitEventTag.find(pGameObjectA->GetTag());
			if (it2 != m_hitEventTag.end())
			{
				it2->second();
			}
			auto it3 = m_hitEventName.find(pGameObjectA->GetName());
			if (it3 != m_hitEventName.end())
			{
				it3->second();
			}
		}
	}
	
	//for (auto& pair : m_collisionPairs)
	//{
	//	btCollisionObject* objA = pair.first;
	//	btCollisionObject* objB = pair.second;

	//	iObject* pObjectA = static_cast<iObject*>(objA->getUserPointer());
	//	iObject* pObjectB = static_cast<iObject*>(objB->getUserPointer());

 //       GameObject* pGameObjectA = reinterpret_cast<GameObject*>(objA->getUserPointer());
	//	GameObject* pGameObjectB = reinterpret_cast<GameObject*>(objB->getUserPointer());
	//	
	//	if (pObjectA == m_pObject)
	//	{
	//		auto it = m_hitEventID.find(pObjectB->GetID());
	//		

	//		if (it != m_hitEventID.end())
	//		{
	//			it->second();
	//		}

	//		auto it2 = m_hitEventTag.find(pGameObjectB->GetTag());
	//		if (it2 != m_hitEventTag.end())
	//		{
	//			it2->second();
	//		}

	//		auto it3 = m_hitEventName.find(pGameObjectB->GetName());
	//		if (it3 != m_hitEventName.end())
	//		{
	//			it3->second();
	//		}
	//	}

	//	if (pObjectB == m_pObject)
	//	{
	//		auto it = m_hitEventID.find(pObjectA->GetID());
	//		if (it != m_hitEventID.end())
	//		{
	//			it->second();
	//		}
	//		auto it2 = m_hitEventTag.find(pGameObjectA->GetTag());
	//		if (it2 != m_hitEventTag.end())
	//		{
	//			it2->second();
	//		}
	//		auto it3 = m_hitEventName.find(pGameObjectA->GetName());
	//		if (it3 != m_hitEventName.end())
	//		{
	//			it3->second();
	//		}
	//	}
	//}
	 

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
		
		GameObject* pGameObjectA = reinterpret_cast<GameObject*>(objctA->getUserPointer());
		GameObject* pGameObjectB = reinterpret_cast<GameObject*>(objctB->getUserPointer());

		if (pObjectA == m_pObject && pGameObjectB->GetName() == name)
		{
			hitObjects.push_back(pObjectB->GetParent());
		}

		if (pObjectB == m_pObject && pGameObjectA->GetName() == name)
		{
			hitObjects.push_back(pObjectA->GetParent());
		}
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
	: m_boxShape(nullptr)
	, m_halfExtents(0.0f, 0.0f, 0.0f)
{
}

CubeCollision::~CubeCollision()
{
	if (m_boxShape)
	{
		delete m_boxShape;
		m_boxShape = nullptr;
	}
}

bool CubeCollision::Init()
{
	m_boxShape = new btBoxShape(m_halfExtents);
	return iCollision::Init();
}

void CubeCollision::Update()
{
	iCollision::Update();
}

btCollisionShape* CubeCollision::GetCollisionShape() const
{
	return m_boxShape;
}



CapsuleCollision::CapsuleCollision()
	: m_capsuleShape(nullptr)
	, m_radius(0.0f)
	, m_height(0.0f)
{
}


CapsuleCollision::~CapsuleCollision()
{
	if (m_capsuleShape)
	{
		delete m_capsuleShape;
		m_capsuleShape = nullptr;
	}
}

bool CapsuleCollision::Init()
{
	m_capsuleShape = new btCapsuleShape(m_radius, m_height);


	return iCollision::Init();
}

void CapsuleCollision::Update()
{
	iCollision::Update();
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
	iCollision::Update();
}

btCollisionShape* MeshCollision::GetCollisionShape() const
{
	return m_meshShape;
}

bool MeshCollision::LoadModel(const std::string& path)
{
	Assimp::Importer importer;

	const aiScene* scene = importer.ReadFile(
		path,
		aiProcess_Triangulate |
		aiProcess_JoinIdenticalVertices |
		aiProcess_GenSmoothNormals |
		aiProcess_FlipUVs
	);

	if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
	{
		return false;
	}

	m_triangleMesh = new btTriangleMesh();

	// メッシュの読み込み
	for (unsigned int meshIndex = 0; meshIndex < scene->mNumMeshes; ++meshIndex)
	{
		aiMesh* mesh = scene->mMeshes[meshIndex];

		// モデルの三角形データをBulletの三角形メッシュに追加
		for (unsigned int faceIndex = 0; faceIndex < mesh->mNumFaces; ++faceIndex)
		{
			aiFace& face = mesh->mFaces[faceIndex];

			// Assimpの三角形化処理により、全ての面が3頂点になっている
			if (face.mNumIndices == 3) 
			{
				btVector3 vertex[3];

				for (unsigned int i = 0; i < 3; ++i)
				{
					aiVector3D pos = mesh->mVertices[face.mIndices[i]];
					vertex[i] = btVector3(pos.x, pos.y, pos.z);
				}

				m_triangleMesh->addTriangle(vertex[0], vertex[1], vertex[2]);
			}
		}
	}

	bool useQuantizedAabbCompression = true;
	m_meshShape = new btBvhTriangleMeshShape(m_triangleMesh, useQuantizedAabbCompression);

	return true;
}


