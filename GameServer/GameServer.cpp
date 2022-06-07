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
#include "LFStack.h"

DECLSPEC_ALIGN(16)
class Data
{
public:
    SListEntry _entry;

    int64 _rand = rand() % 1000;
};

SListHeader* GHeader;

int main()
{
    GHeader = new SListHeader();
    ASSERT_CRASH((uint64)GHeader % 16 == 0);
    InitializeHead(GHeader);

    for (int32 i = 0; i < 3; i++)
    {
        GThreadManager->Launch([]()
        {
            while (true)
            {
                Data* data = new Data();
                ASSERT_CRASH((uint64)data % 16 == 0);

                PushEntrySList(GHeader, (SListEntry*)data);
                this_thread::sleep_for(10ms);
            }
        });
    }

    for (int32 i = 0; i < 3; i++)
    {
        GThreadManager->Launch([]()
        {
            while (true)
            {
                Data* popData = nullptr;
                popData = (Data*)PopEntrySList(GHeader);

                if (popData)
                {
                    cout << popData->_rand << endl;
                    delete popData;
                }
                else
                {
                    cout << "NOne" << endl;
                }
            }
        });
    }
}
