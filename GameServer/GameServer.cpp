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

class Monster
{
public:
    int64 _id = 0;
};

int main()
{
    //Knight* pKnight = ObjectPool<Knight>::Pop();
    //ObjectPool<Knight>::Push(pKnight);
    //shared_ptr<Knight> sptr = { ObjectPool<Knight>::Pop() , ObjectPool<Knight>::Push };
    Knight* knights[100];
    for (int32 i = 0; i < 100; i++)
    {
        knights[i] = ObjectPool<Knight>::Pop();
    }

    for (int32 i = 0; i < 100; i++)
    {
        ObjectPool<Knight>::Push(knights[i]);
        knights[i] = nullptr;
    }

    shared_ptr<Knight> sptr = ObjectPool<Knight>::MakeShared();
    shared_ptr<Knight> sptr2 = MakeShared<Knight>();

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
