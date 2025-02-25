#include "Timer.hxx"
#include <Windows.h>
#include <deque>

#pragma comment(lib, "winmm.lib")

// =-=-= グローバル変数・定数定義部 =-=-=
namespace {
	DWORD countStartTime;
	DWORD preExecTime;
	std::deque<float> fpsQueue;

	constexpr int FPS_QUEUE_SIZE = 100;
}

void timer::TimerInit()
{
	timeBeginPeriod(1);
	countStartTime = timeGetTime();
	preExecTime = countStartTime;
}
float timer::DeltaSeconds()
{
	return fpsQueue.back();
}
float timer::GetFPS()
{
	int nCount = 0;
	float fps = 0.0f;
	for (; nCount < fpsQueue.size(); nCount++)
		fps += fpsQueue[nCount];
	return 1.0f / (fps / nCount);
}
void timer::TimerUpdate()
{
	DWORD nowTime = timeGetTime();
	fpsQueue.push_back(static_cast<float>(nowTime - preExecTime) * 0.001f);
	if (fpsQueue.size() > FPS_QUEUE_SIZE)
		fpsQueue.pop_front();

	preExecTime = nowTime;
}

