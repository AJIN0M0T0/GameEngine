#include "collisionTestScene.hxx"
#include "../GameObject.hxx"
#include "../../Component/ModelRenderer.hxx"
#include "../../Engine/System/Graphics/GraphicsAPI.hxx"
#include "../../Engine/System/Graphics/Shader.hxx"
#include "../../Component/CameraDebug.h"
#include "../../Engine/System/CameraManager.h"

#include "../../Component/Collision.hxx"

collisionTestScene::collisionTestScene()
{
}

collisionTestScene::~collisionTestScene()
{
}

bool collisionTestScene::Init()
{
	// カメラの生成
	GameObject& pCam = thisCreateObject<GameObject>();
	pCam.AddComponent<CameraDebug>()->SetMainCamera();

	// モデルの生成 2つ
	GameObject& pObject1 = thisCreateObject<GameObject>();
	ModelRenderer* pModelRenderer1 = pObject1.AddComponent<ModelRenderer>();
	pModelRenderer1->Execute("Assets/Model/spot/spot.fbx");
	m_pModel1 = pModelRenderer1->GetModel();
	CubeCollision* pCubeCollision1 = pObject1.AddComponent<CubeCollision>();
	pCubeCollision1->SetHalfExtents(1.0f, 1.0f, 1.0f);
	//pCubeCollision1->Init();
	pObject1.SetName("Object1");
	m_pObject1 = &pObject1;


	GameObject& pObject2 = thisCreateObject<GameObject>();
	ModelRenderer* pModelRenderer2 = pObject2.AddComponent<ModelRenderer>();
	pModelRenderer2->Execute("Assets/Model/spot/spot.fbx");
	m_pModel2 = pModelRenderer2->GetModel();
	CubeCollision* pCubeCollision2 = pObject2.AddComponent<CubeCollision>();
	pCubeCollision2->SetHalfExtents(1.0f, 1.0f, 1.0f);
	//pCubeCollision2->Init();
	pObject2.SetName("Object2");
	m_pObject2 = &pObject2;

	Engine::Graphic::ShaderManager& sm = Engine::Graphic::ShaderManager::GetInstance();

	m_pModel1->SetVertexShader("VertexShader");
	m_pModel1->SetPixelShader("PixelShader");

	m_pModel2->SetVertexShader("VertexShader");
	m_pModel2->SetPixelShader("PixelShader");

	sm.LoadVertexShader("VertexShader")->Load("VertexShader");
	sm.LoadPixelShader("PixelShader")->Load("PixelShader");



	return true;
}

void collisionTestScene::Update()
{
	// モデルの移動
	Engine::Math::fVec3 pos1 = m_pObject1->GetTransform().GetWorldPosition();
	pos1.x += 0.01f;
	m_pObject1->GetTransform().SetWorldPosition(pos1);

	Engine::Math::fVec3 pos2 = m_pObject2->GetTransform().GetWorldPosition();
	pos2.x -= 0.01f;
	m_pObject2->GetTransform().SetWorldPosition(pos2);

	// 衝突判定
	//m_pObject1->GetComponent<CubeCollision>()->Update();
//	m_pObject2->GetComponent<CubeCollision>()->Update();

	// 衝突判定結果の取得
	// SetHitEventで設定した関数が呼ばれる
	auto* hitObject1 = m_pObject1->GetComponent<CubeCollision>();
	auto* hitObject2 = m_pObject2->GetComponent<CubeCollision>();

	//auto hit1 = hitObject1->IsHit("Object2");
	//auto hit2 = hitObject2->IsHit("Object1");

	//if (hit1.size() > 0)
	//{
	//	OutputDebugStringA("Hit Object1\n");
	//}

	//if (hit2.size() > 0)
	//{
	//	OutputDebugStringA("Hit Object2\n");
	//}
	if (!hitObject1)
	{
		OutputDebugString("hitObject1 is nullptr\n");
		return;
	}

	//hitObject1->SetHitEvent("Object2", []() {OutputDebugString("Hit Object1\n"); });
	hitObject2->SetHitEvent("Object1", []() {OutputDebugString("Hit Object2\n"); });
	


}

void collisionTestScene::Draw(const Engine::Math::Matrix& world)
{
	Engine::Graphic::iRenderTarget* pRT = Engine::Graphic::TextureManager::GetInstance().RecordRenderTarget("default").get();
	Engine::Graphic::GraphicsManager::CreateInstance()->SetRenderTarget(1, &pRT,
		Engine::Graphic::TextureManager::GetInstance().RecordDepstStencil("default").get());

	CameraBase* pCamera = Engine::System::CameraManager::GetInstance().GetInstance().GetMainCamera();
	Engine::Math::fVec4x4 wvp[3];
	wvp[1] = pCamera->GetViewMatrix();
	wvp[2] = pCamera->GetProjMatrix();

	wvp[0] = m_pModel1->GetWorldMatrix();

	Engine::Graphic::ShaderManager::GetInstance().LoadVertexShader("VertexShader")->WriteBuffer(0, wvp);

	m_pModel1->Draw();



}
