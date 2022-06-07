#include "pch.h"
#include "LFStack.h"

/*
void InitializeHead(SListHeader* header)
{
    header->next = nullptr;
}

void PushEntrySList(SListHeader* header, SListEntry* entry)
{
    entry->next = header->next;
    header->next = entry;
}

SListEntry* PopEntrySList(SListHeader* header)
{
    SListEntry* top = header->next;

    if (top != nullptr)
    {
        header->next = top->next;
    }

    return top;
}
*/
/*
void InitializeHead(SListHeader* header)
{
    header->next = nullptr;
}

void PushEntrySList(SListHeader* header, SListEntry* entry)
{
    entry->next = header->next;
    while (InterlockedCompareExchange64((int64*)&header->next, (int64*)entry, (int64)entry->next))
    {

    }
    header->next = entry;
}

SListEntry* PopEntrySList(SListHeader* header)
{
    SListEntry* top = header->next;

    while (top && InterlockCOmpareExchange64((int64*)&header->next, (int64*)entry->next, (int64*)entry))
    {

    }

    return top;
}
*/

void InitializeHead(SListHeader* header)
{
    header->alignment = 0;
    header->region = 0;
}

void PushEntrySList(SListHeader* header, SListEntry* entry)
{
    SListHeader expected = {};
    SListHeader desired = {};

    // 16����Ʈ ������ ��� ���� 4���� 0000��.
    desired.HeaderX64.next = (((uint64)entry) >> 4);

    while (true)
    {
        expected = *header;
        entry->next = (SListEntry*)(((uint64)expected.HeaderX64.next) << 4);
        desired.HeaderX64.depth = expected.HeaderX64.depth + 1;
        desired.HeaderX64.sequence = expected.HeaderX64.sequence + 1;

        if (InterlockedCompareExchange128((int64*)header, desired.region, desired.alignment, (int64*)&expected) == 1)
        {
            break;
        }
    }
}

// ���� �����忡�� pop�� �����Ұ��, Use-After-Free ������ ������ ������.
SListEntry* PopEntrySList(SListHeader* header)
{
    SListHeader expected = {};
    SListHeader desired = {};
    SListEntry* entry = nullptr;

    while (true)
    {
        expected = *header;
        entry = (SListEntry*)(((uint64)expected.HeaderX64.next) << 4);
        if (entry == nullptr)
            break;

        desired.HeaderX64.next = ((uint64)entry->next) >> 4;
        desired.HeaderX64.depth = expected.HeaderX64.depth - 1;
        desired.HeaderX64.sequence = expected.HeaderX64.sequence + 1;

        if (InterlockedCompareExchange128((int64*)header, desired.region, desired.alignment, (int64*)&expected) == 1)
            break;
    }

    return entry;
}