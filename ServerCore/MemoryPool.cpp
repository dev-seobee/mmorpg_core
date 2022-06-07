#include "pch.h"
#include "MemoryPool.h"

MemoryPool::MemoryPool(int32 allocSize) : _allocSize(allocSize)
{
}

MemoryPool::~MemoryPool()
{
    while (_queue.empty() == false)
    {
        MemoryHeader* header = _queue.front();
        _queue.pop();
        ::free(header);
    }
}

void MemoryPool::Push(MemoryHeader* ptr)
{
    WRITE_LOCK;
    ptr->allocSize = 0;

    // 메모리 반납.
    _queue.push(ptr);
    _allocCount.fetch_sub(1);
}

MemoryHeader* MemoryPool::Pop()
{
    MemoryHeader* header = nullptr;
    {
        WRITE_LOCK;

        // pool에 여분 데이터 있는지 확인.
        if (_queue.empty() == false)
        {
            // 있을 경우 하나 꺼내와 반환
            header = _queue.front();
            _queue.pop();
        }
    }

    // 없을 경우 새로 생성.
    if (header == nullptr)
    {
        header = reinterpret_cast<MemoryHeader*>(::malloc(_allocSize));
    }
    else
    {
        ASSERT_CRASH(header->allocSize == 0);
    }

    _allocCount.fetch_add(1);

    return header;
}
