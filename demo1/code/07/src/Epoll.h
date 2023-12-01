#include <sys/epoll.h>
#include "util.h"
#include <strings.h>
#include <vector>
#include "Channel.h"

class Channel;
class Epoll
{
private:
    int epfd;
    struct epoll_event *events;

public:
    Epoll();
    ~Epoll();
    void addFd(int fd, uint32_t op);
    std::vector<Channel *> poll(int timeout = -1);
    void updateChannel(Channel *);
};
