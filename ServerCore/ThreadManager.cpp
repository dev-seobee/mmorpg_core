#include "pch.h"
#include "ThreadManager.h"
#include "CoreTLS.h"
#include "CoreGlobal.h"

ThreadManager::ThreadManager()
{
    InitTLS();
}

ThreadManager::~ThreadManager()
{
    Join();
}

void ThreadManager::InitTLS()
{
    // 생성자 호출시 매번 1씩 증가하는 아이디(Thread) 생성.
    static Atomic<uint32> SThreadId = 1;
    LThreadId = SThreadId.fetch_add(1);
}

void ThreadManager::DestroyTLS()
{

}

void ThreadManager::Join()
{
    for (thread& t : _threads)
    {
        if (t.joinable())
            t.join();
    }
    _threads.clear();
}

// 인풋은 ()void, 반환은 앞의 void.의 함수를 받는다.
void ThreadManager::Launch(function<void(void)> callback)
{
    LockGuard guard(_lock);

    _threads.push_back(thread([=]()
    {
        InitTLS();
        callback();
        DestroyTLS();
    }));
}