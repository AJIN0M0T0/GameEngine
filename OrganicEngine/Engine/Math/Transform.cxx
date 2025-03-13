#include "Transform.hxx"
#include "DirectXMath.h"
#include "Transform.hxx"

using namespace Engine::Math;

const static float c_fPi_180 = 3.1415926535f / 180.0f;

Transform::Transform()
	: m_Rotation()
	, m_Scale()
	, m_Parent(nullptr)
	, m_IsLook(false)
	, m_LookPoint(nullptr)
{
	m_Scale = m_Scale + 1.0f;
}
Transform::~Transform()
{
	m_Parent = nullptr;
}

void Transform::Update()
{
	if (m_IsLook)// Billboard
	{
		fVec3 LookVec = GetWorldPosition() - m_LookPoint->GetWorldPosition();
		fVec3 Nom = Vec::Nomalize(LookVec);
		fVec3 LookRot = { atan2f(Nom.y,sqrtf(Nom.x * Nom.x + Nom.z * Nom.z)) * -57.2957795f,atan2f(Nom.x,Nom.z) * 57.2957795f,0.0f };
		SetLocalRotation(LookRot);
	}
}

void  Transform::SetLocalPosition(fVec3 Get)
{
	m_Position = Get;
}
fVec3 Transform::GetLocalPosition()
{
	return m_Position;
}
void  Transform::SetLocalRotation(fVec3 Get)
{
	m_Rotation = Get;
}
fVec3 Transform::GetLocalRotation()
{
	return m_Rotation;
}
void  Transform::SetLocalScale(fVec3 Get)
{
	m_Scale = Get;
}
fVec3 Transform::GetLocalScale()
{
	return m_Scale;
}

void  Transform::SetWorldPosition(fVec3 Get)
{
	if (m_Parent)
		m_Position = PositionWorldToLocal(Get, m_Parent);
	else
		m_Position = Get;
}
fVec3 Transform::GetWorldPosition()
{
	if (m_Parent)
		return PositionLocalToWorld(m_Position, m_Parent);
	else
		return m_Position;
}
void  Transform::SetWorldRotation(fVec3 Get)
{
	if (m_Parent)
		m_Rotation = RotationWorldToLocal(Get, m_Parent);
	else
		m_Rotation = Get;
}
fVec3 Transform::GetWorldRotation()
{
	if (m_Parent)
		return RotationLocalToWorld(m_Rotation, m_Parent);
	else
		return m_Rotation;
}
void  Transform::SetWorldScale(fVec3 Get)
{
	if (m_Parent)
		m_Scale = ScaleWorldToLocal(Get, m_Parent);
	else
		m_Scale = Get;
}

fVec3 Transform::GetWorldScale()
{
	if (m_Parent)
		return ScaleLocalToWorld(m_Scale, m_Parent);
	else
		return m_Scale;
}

void Transform::SetParent(Transform* tf)
{
	m_Parent = tf;
	ChangeParent();
}

void Transform::RemoveParent()
{
	m_Parent = nullptr;
	ChangeParent();
}

void Transform::LookPoint(Transform* Point)
{
	m_IsLook = true;
	m_LookPoint = Point;
}

Matrix Transform::GetWorldMatrix(void)
{
	//----------現在の状態を取得----------
	fVec3 worldPosition = GetWorldPosition();
	fVec3 worldRotate = GetWorldRotation();
	fVec3 worldScale = GetWorldScale();

	//----------各種変換行列を求める----------
	DirectX::XMMATRIX transMat = DirectX::XMMatrixTranslation(worldPosition.x, worldPosition.y, worldPosition.z);
	DirectX::XMMATRIX rotXMat = DirectX::XMMatrixRotationX(worldRotate.x * Engine::Meta::Division<Engine::PI, 180.0f>());
	DirectX::XMMATRIX rotYMat = DirectX::XMMatrixRotationY(worldRotate.y * Engine::Meta::Division<Engine::PI, 180.0f>());
	DirectX::XMMATRIX rotZMat = DirectX::XMMatrixRotationZ(worldRotate.z * Engine::Meta::Division<Engine::PI, 180.0f>());
	DirectX::XMMATRIX scaleMat = DirectX::XMMatrixScaling(worldScale.x, worldScale.y, worldScale.z);

	DirectX::XMMATRIX mat = scaleMat * rotXMat * rotYMat * rotZMat * transMat;// 変換座標を格納
	mat = DirectX::XMMatrixTranspose(mat);// 転置行列を求める

	return mat;
}

void Transform::ChangeParent()
{
	if (m_Parent)
	{
		m_Position = PositionWorldToLocal(m_Position, m_Parent);
		m_Rotation = RotationWorldToLocal(m_Rotation, m_Parent);
		m_Scale = ScaleWorldToLocal(m_Scale, m_Parent);
	}
	else if (m_Parent == nullptr)
	{
		m_Position = PositionLocalToWorld(m_Position, m_Parent);
		m_Rotation = RotationLocalToWorld(m_Rotation, m_Parent);
		m_Scale = ScaleLocalToWorld(m_Scale, m_Parent);
	}
}

fVec3 Engine::Math::PositionLocalToWorld(fVec3 localPos, Transform* pParentTransform)
{
	fVec3 worldPos = localPos;
	fVec3 parentScale = pParentTransform->GetLocalScale();
	worldPos.x *= parentScale.x;
	worldPos.y *= parentScale.y;
	worldPos.z *= parentScale.z;

	// 親に合わせて回転
	fVec3 parentRot = pParentTransform->GetLocalRotation();
	// ベクトルを回転
	DirectX::XMMATRIX rotXMat = DirectX::XMMatrixRotationX(parentRot.x * Engine::Meta::Division<Engine::PI, 180.0f>());
	DirectX::XMMATRIX rotYMat = DirectX::XMMatrixRotationY(parentRot.y * Engine::Meta::Division<Engine::PI, 180.0f>());
	DirectX::XMMATRIX rotZMat = DirectX::XMMatrixRotationZ(parentRot.z * Engine::Meta::Division<Engine::PI, 180.0f>());
	DirectX::XMMATRIX rotMat = rotXMat * rotYMat * rotZMat;
	DirectX::XMVECTOR rotPos = DirectX::XMVector3TransformCoord(
		DirectX::XMVectorSet(worldPos.x, worldPos.y, worldPos.z, 1.0f), rotMat
	);
	DirectX::XMFLOAT3 rotPosFloatVec;
	DirectX::XMStoreFloat3(&rotPosFloatVec, rotPos);

	worldPos = { rotPosFloatVec.x, rotPosFloatVec.y, rotPosFloatVec.z };

	// 親からの相対座標からワールド座標に直す
	fVec3 parentPos = pParentTransform->GetLocalPosition();
	worldPos = worldPos + parentPos;

	// ワールド座標を計算
	return worldPos;

}
fVec3 Engine::Math::PositionWorldToLocal(fVec3 worldPos, Transform* pParentTransform)
{
	// 座標を設定
	// 相対ベクトルを計算
	fVec3 relPos = worldPos - pParentTransform->GetLocalPosition();

	// 親の回転量と逆転
	fVec3 parentRot = pParentTransform->GetLocalRotation();
	parentRot = parentRot * -1.0f;
	DirectX::XMMATRIX rotXMat = DirectX::XMMatrixRotationX(parentRot.x * Engine::Meta::Division<Engine::PI, 180.0f>());
	DirectX::XMMATRIX rotYMat = DirectX::XMMatrixRotationY(parentRot.y * Engine::Meta::Division<Engine::PI, 180.0f>());
	DirectX::XMMATRIX rotZMat = DirectX::XMMatrixRotationZ(parentRot.z * Engine::Meta::Division<Engine::PI, 180.0f>());
	DirectX::XMMATRIX rotMat = rotXMat * rotYMat * rotZMat;
	DirectX::XMVECTOR rotPos = DirectX::XMVector3TransformCoord(
		DirectX::XMVectorSet(worldPos.x, worldPos.y, worldPos.z, 1.0f), rotMat
	);
	DirectX::XMFLOAT3 rotPosFloatVec;
	DirectX::XMStoreFloat3(&rotPosFloatVec, rotPos);

	worldPos = { rotPosFloatVec.x, rotPosFloatVec.y, rotPosFloatVec.z };

	// 親の拡大率で縮小
	fVec3 parentScale = pParentTransform->GetLocalScale();
	relPos.x = parentScale.x > 0.0f ? relPos.x / parentScale.x : 0.0f;
	relPos.y = parentScale.y > 0.0f ? relPos.y / parentScale.y : 0.0f;
	relPos.z = parentScale.z > 0.0f ? relPos.z / parentScale.z : 0.0f;

	return relPos;

}
fVec3 Engine::Math::RotationLocalToWorld(fVec3 localRot, Transform* pParentTransform)
{
	fVec3 parentRot = pParentTransform->GetLocalRotation();
	return localRot + parentRot;
}
fVec3 Engine::Math::RotationWorldToLocal(fVec3 worldRot, Transform* pParentTransform)
{
	fVec3 parentRot = pParentTransform->GetLocalRotation();
	return worldRot - parentRot;
}
fVec3 Engine::Math::ScaleLocalToWorld(fVec3 localScale, Transform* pParentTransform)
{
	fVec3 parentScale = pParentTransform->GetLocalScale();
	return localScale * parentScale;
}
fVec3 Engine::Math::ScaleWorldToLocal(fVec3 worldScale, Transform* pParentTransform)
{
	fVec3 parentScale = pParentTransform->GetLocalScale();
	return worldScale / parentScale;
}

// ベクトルから回転を求める
fVec3 Engine::Math::VectorToRotation(fVec3 vec)
{
	vec = Vec::Nomalize(vec);
	fVec3 rot;
	rot.x = atan2f(vec.y, sqrtf(vec.x * vec.x + vec.z * vec.z)) * -57.2957795f;
	rot.y = atan2f(vec.x, vec.z) * 57.2957795f;
	rot.z = 0.0f;
	return rot;
}

// 回転から正規化されたベクトルを求める
fVec3 Engine::Math::RotationToVector(fVec3 rot)
{
	fVec3 vec;
	vec.x = cosf(rot.x * c_fPi_180) * sinf(rot.y * c_fPi_180);
	vec.y = sinf(rot.x * c_fPi_180);
	vec.z = cosf(rot.x * c_fPi_180) * cosf(rot.y * c_fPi_180);
	vec = Vec::Nomalize(vec);
	return vec;
}

Matrix Engine::Math::GetWorldMatrix(const Matrix& baseWorld, Transform Local)
{
	return Local.GetWorldMatrix() * baseWorld;
}
