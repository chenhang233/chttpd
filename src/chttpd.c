#include "client.h"
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>

int main(int argc, char const *argv[])
{
    int cur_fd;
    c_config_parse();

    if (conf.fork_on)
    {
        switch (fork())
        {
        case -1:
            perror("main fork()");
            exit(1);
        case 0:
            /* daemon setup */
            printf("hello world 0\n");
            cur_fd = open("/dev/null", O_WRONLY);
            printf("hello world 1\n");
            if (cur_fd > 0)
            {
                dup2(cur_fd, 0);
                dup2(cur_fd, 1);
                dup2(cur_fd, 2);
            }
            printf("hello world 2\n");
            break;
        default:
            printf("exit\n");
            exit(0);
        }
    }

    return 0;
}
