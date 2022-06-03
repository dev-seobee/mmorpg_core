// GameServer.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//
#include "pch.h"
#include <iostream>
#include <memory>
#include "CorePch.h"
#include "CoreGlobal.h"
#include "CoreMacro.h"
#include "ThreadManager.h"
#include "AccountManager.h"
#include "PlayerManager.h"


int main()
{
    make_shared<int>():
    GThreadManager->Launch([=]
    {
        while (true)
        {
            cout << "PlayerThenAccount" << endl;
            GPlayerManager.PlayerThenAccount();
            this_thread::sleep_for(100ms);
        }
    });

    GThreadManager->Launch([=]
    {
        while (true)
        {
            cout << "AccountThenPlayer" << endl;
            GAccountManager.AccountThenPlayer();
            this_thread::sleep_for(100ms);
        }
    });

    GThreadManager->Join();
}
