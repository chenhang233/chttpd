#include <stdio.h>
#include <arpa/inet.h>
#include <fcntl.h>
#include <errno.h>
#include <strings.h>
#include <unistd.h>
#include "Socket.h"
#include "Epoll.h"

#define READ_BUFFER 1024
void handleReadEvent(int sockfd);
int main()
{
    Socket *s = new Socket();
    InetAddress *address = new InetAddress("127.0.0.1", 8888);
    s->bind(address);
    s->listen();
    s->setnonblocking();
    Epoll *e = new Epoll();
    e->addFd(s->getFd(), EPOLLIN | EPOLLET);
    while (true)
    {
        std::vector<struct epoll_event> events = e->poll();
        int nfds = events.size();
        for (int i = 0; i < nfds; ++i)
        {
            if (events[i].data.fd == s->getFd())
            {
                InetAddress *clnt_addr = new InetAddress();
                Socket *clnt_sock = new Socket(s->accept(clnt_addr));
                clnt_sock->setnonblocking();
                printf("new client fd %d! IP: %s Port: %d\n", clnt_sock->getFd(), inet_ntoa(clnt_addr->addr.sin_addr), ntohs(clnt_addr->addr.sin_port));
            }
            else if (events[i].events & EPOLLIN)
            {
                handleReadEvent(events[i].data.fd);
            }
            else
            {
                printf("something else happened\n");
            }
        }
    }
    delete address;
    delete s;

    return 0;
}

void handleReadEvent(int sockfd)
{
    char buf[READ_BUFFER];
    while (true)
    { // 由于使用非阻塞IO，读取客户端buffer，一次读取buf大小数据，直到全部读取完毕
        bzero(&buf, sizeof(buf));
        ssize_t bytes_read = read(sockfd, buf, sizeof(buf));
        if (bytes_read > 0)
        {
            printf("message from client fd %d: %s\n", sockfd, buf);
            write(sockfd, buf, sizeof(buf));
        }
        else if (bytes_read == -1 && errno == EINTR)
        { // 客户端正常中断、继续读取
            printf("continue reading");
            continue;
        }
        else if (bytes_read == -1 && ((errno == EAGAIN) || (errno == EWOULDBLOCK)))
        { // 非阻塞IO，这个条件表示数据全部读取完毕
            printf("finish reading once, errno: %d\n", errno);
            break;
        }
        else if (bytes_read == 0)
        { // EOF，客户端断开连接
            printf("EOF, client fd %d disconnected\n", sockfd);
            close(sockfd); // 关闭socket会自动将文件描述符从epoll树上移除
            break;
        }
    }
}
