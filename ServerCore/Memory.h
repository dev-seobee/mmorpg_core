#pragma once
#include "Allocator.h"

class MemoryPool;

/*
    Memory
*/
class Memory
{
    enum
    {
        // ~1024 까지는 32단위로, ~2048까지는 128, ~4096까지는 256단위로 생성.
        POOL_COUNT = (1024 / 32) + (1024 / 128) + (2048 / 256),
        MAX_ALLOC_SIZE = 4096
    };

public:
    Memory();
    ~Memory();

    void* Allocate(int32 size);
    void Release(void* ptr);

private:
    vector<MemoryPool*> _pools;

    //메모리 풀을 빠르게 찾기위한 테이블.
    MemoryPool* _poolTable[MAX_ALLOC_SIZE + 1];
};

template<typename Type, typename... Args>
Type* xnew(Args&&... args)
{
    Type* memory = static_cast<Type*>(Xalloc(sizeof(Type)));

    // placement new
    new(memory)Type(forward<Args>(args)...);

    return memory;
}

template<typename Type>
void xdelete(Type* obj)
{
    obj->~Type();
    Xrelease(obj);
}
