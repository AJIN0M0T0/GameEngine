#include "Defines.hxx"
#include <crtdbg.h>

#ifdef __ENGINE__
#include "Supervision.hxx"
#include "System/Window.hxx"
#include "System/Timer.hxx"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	Window& window = Window::CreateInstance();
	window.SettingWindow(hInstance,nCmdShow);
	window.ShowWindow();

	// 初期化処理　※失敗したら停止
	if (!Supervision::Initialize())
	{
		Supervision::Finalize();
		return 0;
	}

	MSG msg = window.GetMSG();

	timer::TimerInit();

	while (true) {
		if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE)) {
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else
		{
			DebugString_(std::to_string(timer::GetFPS()) + "\n")
			Supervision::Updater();
			timer::TimerUpdate();
		}

		if (msg.message == WM_QUIT)
			break;
	}

	// 終了時
	timeEndPeriod(1);
	Supervision::Finalize();

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
