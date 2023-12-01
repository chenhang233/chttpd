#include <sys/socket.h>
#include <unistd.h>
#include "InetAddress.h"
#include <fcntl.h>
#include "util.h"

class Socket
{
private:
    int fd;

public:
    Socket();
    Socket(int);
    ~Socket();
    void bind(InetAddress *);
    int accept(InetAddress *);
    int getFd();
    void listen();
    void setnonblocking();
};
