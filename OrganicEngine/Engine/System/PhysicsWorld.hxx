/**
 * @file PhysicsWorld.hxx
 * @brief 共通物理演算クラス
 * @author yuki57-46
 * @date 2025/03/29 
 */


// =-=-= インクルードガード部 =-=-=
#ifndef ____PHYSICS_WORLD_HXX____
#define ____PHYSICS_WORLD_HXX____

// =-=-= インクルード部 =-=-=
#include <btBulletDynamicsCommon.h>
#include <btBulletCollisionCommon.h>

#include "Singleton.hxx"


namespace Engine::System {
	class PhysicsWorld : public Engine::System::Singleton<PhysicsWorld>
	{
		friend class Singleton<PhysicsWorld>;
	}
}




#endif // !____PHYSICS_WORLD_HXX____
