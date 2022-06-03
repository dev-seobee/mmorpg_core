#pragma once

#include <stack>
#include <mutex>
template<typename T>
class LockFreeStack
{
    struct Node
    {
        Node(const T& value) : data(value)
        {

        }
        T data;
        Node* next;
    };
public:

    void Push(const T& value)
    {
        Node* node = new Node(value);
        node->next
    }


private:
    atomic<int64_t>
};
