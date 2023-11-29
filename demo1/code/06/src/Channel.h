#pragma once
#include <sys/epoll.h>
#include <functional>
class EventLoop;

class Channel
{
private:
    EventLoop *loop;
    int fd;           // socket fd
    uint32_t events;  // 挂载的事件
    uint32_t revents; // 当前正发生的事件
    bool inEpoll;     // 是否挂载到 epoll实例 上
    std::function<void()> callback;

public:
    Channel(EventLoop *_loop, int _fd);
    ~Channel();

    void handleEvent();
    void enableReading();

    int getFd();
    uint32_t getEvents();
    uint32_t getRevents();
    bool getInEpoll();
    void setInEpoll();

    void setRevents(uint32_t);
    void setCallback(std::function<void()>);
};