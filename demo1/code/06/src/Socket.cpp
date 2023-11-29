#include "Socket.h"

Socket::Socket() : fd(-1)
{
    fd = socket(AF_INET, SOCK_STREAM, 0);
    errif(fd == -1, "socket create error");
}

Socket::Socket(int _fd) : fd(_fd)
{
    errif(fd == -1, "socket create error");
}

Socket::~Socket()
{
    if (fd != -1)
    {
        close(fd);
        fd = -1;
    }
}

void Socket::bind(InetAddress *ia)
{
    errif(::bind(fd, (sockaddr *)&ia->addr, ia->addr_len) == -1, "socket bind error");
}

void Socket::listen()
{
    errif(::listen(fd, SOMAXCONN) == -1, "socket listen error");
}

// 设置socket文件描述符为非阻塞模式
void Socket::setnonblocking()
{
    fcntl(fd, F_SETFL, fcntl(fd, F_GETFL) | O_NONBLOCK);
}

int Socket::accept(InetAddress *ia)
{
    int c_sockfd = ::accept(fd, (sockaddr *)&ia->addr, &ia->addr_len);
    errif(c_sockfd == -1, "socket accept error");
    return c_sockfd;
}

int Socket::getFd()
{
    return fd;
}