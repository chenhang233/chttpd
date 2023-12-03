#include <sys/types.h>
#include <sys/stat.h>
#include <errno.h>
#include <stdio.h>
#include <fcntl.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

#define FIFO_PATH "myfifofile"

int main()
{
    int fd;
    char cont_r[255];
    // 创建命名管道
    if (mkfifo(FIFO_PATH, 0666) < 0 && errno != EEXIST)
    {
        perror("create fifo failed");
        return -1;
    }
    else
    {
        printf("create fifo success\n");
        // 打开文件进行读操作
        fd = open(FIFO_PATH, O_CREAT | O_RDONLY, 0666);
        if (fd > 0)
        {
            while (1)
            {
                read(fd, cont_r, 255);
                printf("read:%s\n", cont_r);
            }
            close(fd);
        }
        else
            perror("open failed");
    }
    return 0;
}
