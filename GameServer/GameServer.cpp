// GameServer.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//
#include "pch.h"
#include "CorePch.h"
#include "CoreGlobal.h"
#include "CoreMacro.h"
#include "ThreadManager.h"

#include "SocketUtils.h"

int main()
{
    SOCKET socket = SocketUtils::CreateSocket();
    SocketUtils::BindAnyAddress(socket, 7777);
    SocketUtils::Listen(socket);

    SOCKET clientSocket = ::accept(socket, nullptr, nullptr);

    cout << "Client Connected log" << endl;
    while (true)
    {

    }

    GThreadManager->Join();
}