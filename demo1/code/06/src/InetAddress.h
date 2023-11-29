#include <sys/socket.h>
#include <arpa/inet.h>
#include <string.h>

class InetAddress
{
    // private:
public:
    struct sockaddr_in addr;
    socklen_t addr_len;
    InetAddress();
    ~InetAddress();
    InetAddress(const char *ip, uint16_t port);
};
