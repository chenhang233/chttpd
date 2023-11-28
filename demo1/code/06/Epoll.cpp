#include "Epoll.h"

#define MAX_EVENTS 1024

Epoll::Epoll() : epfd(-1)
{
    errif((epfd = epoll_create1(0)) == -1, "epoll create error");
    events = new struct epoll_event[MAX_EVENTS];
    bzero(events, sizeof(*events) * MAX_EVENTS);
}

Epoll::~Epoll()
{
    delete[] events;
}

void Epoll::addFd(int fd, uint32_t op)
{
    struct epoll_event e;
    bzero(&e, sizeof(e));
    e.data.fd = fd;
    e.events = op;
    errif(epoll_ctl(epfd, EPOLL_CTL_ADD, fd, &e) == -1, "epoll add event error");
}

std::vector<struct epoll_event> Epoll::poll(int timeout)
{
    std::vector<struct epoll_event> values;
    int nfds = epoll_wait(epfd, events, MAX_EVENTS, timeout);
    for (int i = 0; i < nfds; i++)
    {
        values.push_back(events[i]);
    }
    return values;
}