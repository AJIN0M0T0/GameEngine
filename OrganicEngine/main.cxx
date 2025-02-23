#include "defines.hxx"
#include <Windows.h>

#ifdef __ENGINE__

int WINAPI WinMain(HINSTANCE,HINSTANCE,LPSTR,int) {
	return 0;
}

#else

#include <iostream>

#ifdef BULLET_INPORT_CHECK
#include <btBulletDynamicsCommon.h>
#include <btBulletCollisionCommon.h>
#endif // BULLET_INPORT_CHECK

int main() {

#ifdef BULLET_INPORT_CHECK

	btBroadphaseInterface* broadphase = new btDbvtBroadphase();

	btDefaultCollisionConfiguration* collisionConfiguration = new btDefaultCollisionConfiguration();
	btCollisionDispatcher* dispatcher = new btCollisionDispatcher(collisionConfiguration);

	btSequentialImpulseConstraintSolver* solver = new btSequentialImpulseConstraintSolver();

	btDiscreteDynamicsWorld* world = new btDiscreteDynamicsWorld(dispatcher, broadphase, solver, collisionConfiguration);

	delete broadphase;
	delete collisionConfiguration;
	delete dispatcher;
	delete solver;
	delete world;

#endif // BULLET_INPORT_CHECK

	rewind(stdin);
	getchar();
	return 0;
}

#endif // __ENGINE__
