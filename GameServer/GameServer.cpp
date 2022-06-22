// GameServer.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//
#include "pch.h"
#include "CorePch.h"
#include "CoreGlobal.h"
#include "CoreMacro.h"
#include "ThreadManager.h"

#include "SocketUtils.h"
#include "Listener.h"

int main()
{
    Listener listener;
    listener.StartAccept(NetAddress(L"127.0.0.1", 7777));

    for (int32 i = 0; i < 1; i++)
    {
        GThreadManager->Launch([=]()
        {
            while (true)
            {
                GIocpCore.Dispatch();
            }

        });
    }
    GThreadManager->Join();
    cout << "Client Connected log" << endl;
    while (true)
    {

    }

    GThreadManager->Join();
}