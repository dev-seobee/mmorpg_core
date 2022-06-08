// GameServer.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//
#include "pch.h"
#include "CorePch.h"
#include "CoreGlobal.h"
#include "CoreMacro.h"
#include "ThreadManager.h"
#include "AccountManager.h"
#include "PlayerManager.h"

#include "Memory.h"
class Knight
{
public:
    int32 _hp = rand() % 100;
};

int main()
{
    for (int32 i = 0; i < 3; i++)
    {
        GThreadManager->Launch([]()
        {
            while (true)
            {
                Knight* knight = xnew<Knight>();
                cout << knight->_hp << endl;

                this_thread::sleep_for(10ms);
                xdelete(knight);
            }
        });
    }
}
