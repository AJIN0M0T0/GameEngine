#include "CameraManager.h"
#include "../../Component/CameraBase.h"
#include "../Math/Transform.hxx"

using namespace Engine::System;

CameraManager::CameraManager()
	: m_pMainCamera(nullptr)
{

}

CameraManager::~CameraManager()
{

}

void CameraManager::SetMainCamera(CameraBase* cam)
{
	m_pMainCamera = cam;
}

CameraBase* CameraManager::GetMainCamera()
{
	//if (m_pMainCamera == nullptr)
	//{
	//	BaseObject cam = ObjectManager::Make(Singleton<SceneManager>::GetInstance().GetScene());
	//	cam.AddComponent<Transform>();
	//	m_pMainCamera = cam.AddComponent<CameraDebug>();
	//}
	return m_pMainCamera;
}
