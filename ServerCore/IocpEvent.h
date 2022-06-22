#pragma once

class Session;

enum class EventType : uint8
{
    Connect,
    Accept,
    //PreRecv,      zero byte recv를 위한 타입.
    Recv,
    Send
};


class IocpEvent : public OVERLAPPED
{
public:

    IocpEvent(EventType type);

    void Init();
    EventType   GetType() { return _type; }

private:

    EventType       _type;

};

class ConnectEvent : public IocpEvent
{
public:
    ConnectEvent() : IocpEvent(EventType::Connect) { }
};

class AcceptEvent : public IocpEvent
{
public:
    AcceptEvent() : IocpEvent(EventType::Accept) { }
    void SetSession(Session* session) { _session = session; }
    Session* GetSession() { return _session; }

public:
    Session* _session = nullptr;
};

class RecvEvent : public IocpEvent
{
public:
    RecvEvent() : IocpEvent(EventType::Recv) { }
};

class SendEvent : public IocpEvent
{
public:
    SendEvent() : IocpEvent(EventType::Send) { }
};