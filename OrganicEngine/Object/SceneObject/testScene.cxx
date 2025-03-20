#include "testScene.hxx"
#include "../GameObject.hxx"
#include "../../Component/ModelRenderer.hxx"
#include "../../Engine/System/Graphics/GraphicsAPI.hxx"
#include "../../Engine/System/Graphics/Shader.hxx"
#include "../../Component/CameraDebug.h"
#include "../../Engine/System/CameraManager.h"

testScene::testScene()
{

}

testScene::~testScene()
{

}

bool testScene::Init()
{
	// カメラの生成
	GameObject& pCam = thisCreateObject<GameObject>();
	pCam.AddComponent<CameraDebug>()->SetMainCamera();

	GameObject& pObject = thisCreateObject<GameObject>();
	ModelRenderer* pModelRenderer = pObject.AddComponent<ModelRenderer>();
	pModelRenderer->Execute("Assets/Model/spot/spot.fbx");
	m_pModel = pModelRenderer->GetModel();

	Engine::Graphic::ShaderManager& sm = Engine::Graphic::ShaderManager::GetInstance();

	m_pModel->SetVertexShader("VertexShader");
	m_pModel->SetPixelShader("PixelShader");

	sm.LoadVertexShader("VertexShader")->Load("VertexShader");
	sm.LoadPixelShader("PixelShader")->Load("PixelShader");

	return true;
}

void testScene::Update()
{
}

void testScene::Draw(const Engine::Math::Matrix& world)
{
	Engine::Graphic::iRenderTarget* pRT = Engine::Graphic::TextureManager::GetInstance().RecordRenderTarget("default").get();
	Engine::Graphic::GraphicsManager::GetInstance()->SetRenderTarget(1, &pRT, 
		Engine::Graphic::TextureManager::GetInstance().RecordDepstStencil("default").get());

	CameraBase* pCamera = Engine::System::CameraManager::GetInstance().GetMainCamera();
	Engine::Math::fVec4x4 wvp[3];
	wvp[1] = pCamera->GetViewMatrix();
	wvp[2] = pCamera->GetProjMatrix();

	wvp[0] = m_pModel->GetWorldMatrix();

	Engine::Graphic::ShaderManager::GetInstance().LoadVertexShader("VertexShader")->WriteBuffer(0, wvp);

	m_pModel->Draw();
}
