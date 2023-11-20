#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

// 线程函数，线程执行的入口
void *my_thread_func(void *arg)
{
    int *id_ptr = (int *)arg;
    int thread_id = *id_ptr;
    printf("Thread %d: Hello, World! 111\n", thread_id);
    pthread_exit(NULL);
}

int main()
{
    pthread_t threads[5];
    int thread_ids[5];
    int i;

    // 创建 5 个线程
    for (i = 0; i < 5; i++)
    {
        thread_ids[i] = i;
        if (pthread_create(&threads[i], NULL, my_thread_func, (void *)&thread_ids[i]) != 0)
        {
            fprintf(stderr, "Error creating thread\n");
            exit(1);
        }
    }

    // 等待所有线程结束
    for (i = 0; i < 5; i++)
    {
        if (pthread_join(threads[i], NULL) != 0)
        {
            fprintf(stderr, "Error joining thread\n");
            exit(1);
        }
    }

    return 0;
}