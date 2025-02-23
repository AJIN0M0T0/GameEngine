#include "Defines.hxx"
#include <crtdbg.h>

#ifdef __ENGINE__
#include "System/Window.hxx"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	Window window;

	window.SettingWindow(hInstance,nCmdShow);
	window.ShowWindow();

	MSG msg = window.GetMSG();

	while (true) {
		if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE)) {
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}

		if (msg.message == WM_QUIT)
			break;
	}

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
