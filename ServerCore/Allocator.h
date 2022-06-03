#pragma once

/*---
    BaseAllocator
*/
class BaseAllocator
{
public:
    static void*    Alloc(int32 size);
    static void     Release(void* ptr);
};

/*
    StompAllocator
    메모리 오염 버그를 잡는데 굉장히 유용.
*/

class StompAllocator
{
    enum { PAGE_SIZE = 0x1000 };

public:
    static void*    Alloc(int32 size);
    static void     Release(void* ptr);
};
