#include <sys/types.h>
#include <signal.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

static int alarm_fired = 0;

/*该函数用来模拟闹钟*/

void ding(int sig)
{
    alarm_fired = 1;
}
/*main函数中告诉子进程在等待5秒后发送SIGALRM信号给它的父进程*/

int main()
{
    pid_t pid;
    printf("alarm start\n");
    pid = fork(); /*创建子进程*/
    switch (pid)
    {
    case -1:
        perror("fork failed");
        exit(1);
    case 0:
        sleep(5);                 /*子进程休眠5秒*/
        kill(getppid(), SIGALRM); /*子进程在5秒后将SIGALRM信号传递给父进程*/
        exit(0);
    }

    /*父进程通过一个signal调用捕获SIGALRM信号的工作，等待该信号的到来*/
    printf("waitting for alarm to go on\n");

    signal(SIGALRM, ding);
    pause();
    if (alarm_fired)
        printf("ding!\n");
    printf("done\n");
    exit(0);
}
