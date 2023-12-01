#include <functional>

class Socket;
class InetAddress;
class Channel;
class EventLoop;

class Acceptor
{
private:
    EventLoop *loop;
    Socket *sock;
    InetAddress *addr;
    Channel *acceptChannel;

public:
    Acceptor(EventLoop *_loop);
    ~Acceptor();
    void acceptConnection();
    std::function<void(Socket *)> newConnectionCallback;
    void setNewConnectionCallback(std::function<void(Socket *)>);
};
