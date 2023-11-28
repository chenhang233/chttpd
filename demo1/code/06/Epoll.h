#include <sys/epoll.h>
#include "util.h"
#include <strings.h>
#include <vector>

class Epoll
{
private:
    int epfd;
    struct epoll_event *events;

public:
    Epoll();
    ~Epoll();
    void addFd(int fd, uint32_t op);
    std::vector<struct epoll_event> poll(int timeout = -1);
};
