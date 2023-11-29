#include <stdio.h>
#include <arpa/inet.h>
#include <fcntl.h>
#include <errno.h>
#include <strings.h>
#include <unistd.h>
#include "src/EventLoop.h"
#include "src/Server.h"

int main()
{
    EventLoop *e = new EventLoop();
    Server *server = new Server(e);
    e->loop();
    return 0;
}
