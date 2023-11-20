#include "client.h"
#include <stdio.h>
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
            perror("fork()");
            exit(1);
        case 0:
            /* daemon setup */
            cur_fd = open("/dev/null", O_WRONLY);
            if (cur_fd > 0)
            {
                dup2(cur_fd, 0);
                dup2(cur_fd, 1);
                dup2(cur_fd, 2);
            }
            break;
        default:
            exit(0);
        }
    }
    while (1)
    {
        /* code */
    }

    return 0;
}
