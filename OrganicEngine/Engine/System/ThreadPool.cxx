#include "ThreadPool.hxx"

using namespace Engine::System;

bool ThreadPool::ThreadContinue = false;

void ThreadPool::poolloop(bool& EveryFlag)
{
	while (ThreadContinue)
	{
		FuncInfo info = GetInstance().GetPoolFead();
		EveryFlag = info.IsEvery;
		if (info.func)
			info.func();
	}
}

ThreadPool::ThreadPool()
	:m_EveryFlags(nullptr)
{
#ifdef _THREADPOOL_
	ThreadContinue = true;
	m_ThreadCount = static_cast<uint16>(std::thread::hardware_concurrency() * 0.13f);
	m_EveryFlags = New(bool)[m_ThreadCount];
	for (uint16 i = 0; i < m_ThreadCount; i++) {
		m_Thread.push_back(std::make_unique<std::thread>([this,i]() {ThreadPool::poolloop(m_EveryFlags[i]); }));
	}
#endif // _THREADPOOL_
}

ThreadPool::~ThreadPool()
{
	delete[] m_EveryFlags;
}

void ThreadPool::Update()
{
#ifdef _THREADPOOL_
	// スレッドの処理が終わるまで待機
	while (true) {
		bool ans = false;
		for(int i = 0; i < m_ThreadCount;i++)
			ans |= m_EveryFlags[i];
		if (!ans)
			break;
	}
#else // _THREADPOOL_
	while (!m_Pool.empty())
	{
		m_Pool.front().func();
		m_Pool.pop();
	}
#endif // _THREADPOOL_
}

void ThreadPool::AddPool(std::function<void()> func, bool IsEvery)
{
	std::unique_lock<std::shared_mutex> lock(m_Mutex);
	m_Pool.push({ func,IsEvery });
}

FuncInfo ThreadPool::GetPoolFead()
{
	std::unique_lock<std::shared_mutex> lock(m_Mutex);
	if(m_Pool.empty())
		return { nullptr,false };
	FuncInfo front = m_Pool.front();
	m_Pool.pop();
	return front;
}
