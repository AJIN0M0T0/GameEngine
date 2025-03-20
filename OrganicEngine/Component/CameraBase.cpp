#include "CameraBase.h"
#include "../Engine/System/CameraManager.h"
#include "../Object/GameObject.hxx"

CameraBase::CameraBase():
	m_look(0.0f,0.0f,0.0f),
	m_up(0.0f,1.0f,0.0f),
	m_fovy(1.472f),
	m_aspect(16.0f/9.0f),
	m_near(0.3f),
	m_far(1000.0f)
{
	
}

CameraBase::~CameraBase()
{
}

bool CameraBase::Init()
{
	m_Transform = &GetGameObject()->GetTransform();

	Engine::Math::fVec3 look = Engine::Math::RotationToVector(m_Transform->GetWorldRotation()) + m_Transform->GetWorldPosition();

	m_look = {look.x,look.y,look.z};
	return true;
}

DirectX::XMFLOAT4X4 CameraBase::GetViewMatrix()
{
	DirectX::XMFLOAT4X4 mat;
	DirectX::XMMATRIX view;
	Engine::Math::fVec3 pos = m_Transform->GetWorldPosition();
	//
	//ビュー行列の計算
	view =
		DirectX::XMMatrixLookAtLH(
			DirectX::XMVectorSet(pos.x, pos.y, pos.z, 0.0f),//カメラの位置
			DirectX::XMVectorSet(m_look.x, m_look.y, m_look.z, 0.0f),//カメラの注目してる位置
			DirectX::XMVectorSet(m_up.x, m_up.y, m_up.z, 0.0f) //カメラの上方向
		);
	view = DirectX::XMMatrixTranspose(view);
	DirectX::XMStoreFloat4x4(&mat, view);

	return mat;
}

DirectX::XMFLOAT4X4 CameraBase::GetProjMatrix()
{
	DirectX::XMFLOAT4X4 mat;
	DirectX::XMMATRIX proj;
	//
	//プロジェクション行列の計算
	proj = 
		DirectX::XMMatrixPerspectiveFovLH(m_fovy, m_aspect, m_near, m_far);
	proj = DirectX::XMMatrixTranspose(proj);									   //見える範囲
	DirectX::XMStoreFloat4x4(&mat, proj);

	return mat;
}

void CameraBase::SetMainCamera()
{
	Engine::System::CameraManager::GetInstance().SetMainCamera(this);
}
