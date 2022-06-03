#pragma once
#include <thread>
#include <functional>

// 관리할 스레드의 기능들을 담당.
class ThreadManager
{
public:
    ThreadManager();
    ~ThreadManager();

    void Launch(function<void(void)> callback);
    void Join();

    static void InitTLS();
    static void DestroyTLS();

private:
    Mutex           _lock;
    vector<thread>  _threads;

};

