#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/sem.h>

union semun
{
    int val;
    struct semid_ds *buf;
    unsigned short *array;
    // struct seminfo *buff;
};

static int set_semvalue(void);
static void del_semvalue(void);
static int semaphore_p(void);
static int semaphore_v(void);
static int sem_id;

int main(int argc, char *argv[])
{
    int i;
    int pause_time;
    char op_char = 'O';
    srand((unsigned int)getpid());
    sem_id = semget((key_t)1234, 1, 0666 | IPC_CREAT);
    /* 如果程序第一个被调用，也就是调用时含有一个参数，使得argc>1,此时就调用set_semvalue初始化信号量，并将op_char设置为x*/
    if (argc > 1)
    {
        if (!set_semvalue())
        {
            fprintf(stderr, "Failed to initialize semaphore\n");
            exit(EXIT_FAILURE);
        }
        op_char = 'X';
        sleep(2);
    }
    /*进入和离开临界区10次，每次循环开始的时候首先调用semaphore_p函数，它在程序将进入临界区域时设置信号量以等待进入*/
    for (i = 0; i < 10; i++)
    {
        if (!semaphore_p())
            exit(EXIT_FAILURE);
        printf("%c", op_char);
        fflush(stdout);
        pause_time = rand() % 3;
        sleep(pause_time);
        printf("%c", op_char);
        fflush(stdout);
        /*进入临界区域后，调用semaphore_v将信号量设置为可用，然后等待一段随机的时间，再进入下一次循环*/
        if (!semaphore_v())
            exit(EXIT_FAILURE);
        pause_time = rand() % 2;
        sleep(pause_time);
    }
    printf("\n%d - finished\n", getpid());
    if (argc > 1)
    {
        sleep(10);
        del_semvalue();
    }
    exit(EXIT_SUCCESS);
}
/*该函数用来将semctl调用的command参数设置为SETVAL来初始化信号量*/
static int set_semvalue(void)
{
    union semun sem_union;
    sem_union.val = 1;
    if (semctl(sem_id, 0, SETVAL, sem_union) == -1)
        return 0;
    return (1);
}
/*通过调用semctl调用的command设置为IPC_RMID来删除信号量ID*/
static void del_semvalue(void)
{
    union semun sem_union;
    if (semctl(sem_id, 0, IPC_RMID, sem_union) == -1)
        fprintf(stderr, "Failed to delete semaphore");
}
/*对信号量执行减1操作*/
static int semaphore_p(void)
{
    struct sembuf sem_b;
    sem_b.sem_num = 0;
    sem_b.sem_op = -1;
    sem_b.sem_flg = SEM_UNDO;
    if (semop(sem_id, &sem_b, 1) == -1)
    {
        fprintf(stderr, "semaphore_p failed\n");
        return (0);
    }
    return (1);
}
/*对信号量执行加1操作*/
static int semaphore_v(void)
{
    struct sembuf sem_b;
    sem_b.sem_num = 0;
    sem_b.sem_op = 1;
    sem_b.sem_flg = SEM_UNDO;
    if (semop(sem_id, &sem_b, 1) == -1)
    {
        fprintf(stderr, "semaphore_v failed\n");
        return (0);
    }
    return (1);
}
