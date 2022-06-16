#pragma once

#include "Types.h"
#include "CoreTLS.h"
#include "CoreGlobal.h"
#include "CoreMacro.h"
#include "Container.h"
#include "Allocator.h"
#include <iostream>
#include <windows.h>
using namespace std;

#include <WinSock2.h>
#include <MSWSock.h>
#include <WS2tcpip.h>
#pragma comment(lib, "ws2_32.lib")

#include "Lock.h"
#include "ObjectPool.h"
#include "TypeCast.h"
#include "Memory.h"

