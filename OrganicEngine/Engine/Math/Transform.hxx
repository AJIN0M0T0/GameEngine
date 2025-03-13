//	ファイル名	：Transform.hxx
//	  概  要	：
//	作	成	者	：daigo
//	 作成日時	：2025/03/14 3:33:49
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/

// =-=-= インクルードガード部 =-=-=
#ifndef _____Transform_HXX_____
#define _____Transform_HXX_____

#include "Vectors.hxx"

namespace Engine::Math{

class Transform
{
public:
	Transform();
	~Transform();

	void Update();

	Engine::Math::fVec3 GetLocalPosition();
	Engine::Math::fVec3 GetLocalRotation();
	Engine::Math::fVec3 GetLocalScale();
	Engine::Math::fVec3 GetWorldPosition();
	Engine::Math::fVec3 GetWorldRotation();
	Engine::Math::fVec3 GetWorldScale();

	void  SetLocalPosition(fVec3 Get);
	void  SetLocalRotation(fVec3 Get);
	void  SetLocalScale(fVec3 Get);
	void  SetWorldPosition(fVec3 Get);
	void  SetWorldRotation(fVec3 Get);
	void  SetWorldScale(fVec3 Get);

	void SetParent(Transform* tf);
	void RemoveParent();

	void LookPoint(Transform* point);

	Matrix GetWorldMatrix(void);

private:
	void ChangeParent();

private:
	fVec3 m_Rotation;// ローカル座標の回転
	fVec3 m_Scale;// ローカル座標の拡大縮小
	fVec3 m_Position;// ローカル座標の位置

	bool m_IsLook;
	Transform* m_LookPoint;


	Transform* m_Parent;
};

	fVec3 PositionLocalToWorld(fVec3 localPos, Transform* pParentTransform);
	fVec3 PositionWorldToLocal(fVec3 worldPos, Transform* pParentTransform);
	fVec3 RotationLocalToWorld(fVec3 localRot, Transform* pParentTransform);
	fVec3 RotationWorldToLocal(fVec3 worldRot, Transform* pParentTransform);
	fVec3 ScaleLocalToWorld(fVec3 localScale, Transform* pParentTransform);
	fVec3 ScaleWorldToLocal(fVec3 worldScale, Transform* pParentTransform);
	fVec3 VectorToRotation(fVec3 vec);
	fVec3 RotationToVector(fVec3 rot);

	Matrix GetWorldMatrix(const Matrix& baseWorld,Transform Local);
};

#endif // !_____Transform_HXX_____
