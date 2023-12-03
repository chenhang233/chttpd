#include <stdio.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <string.h>

// 消息队列数据结构
typedef struct mesg_buffer
{
    long mesg_type;
    char mesg_text[100];
} message;

int main()
{
    key_t key;
    int msgid;
    message msg;
    // ftok to generate unique key
    key = ftok("progfile", 65);
    // msgget creates a message queue
    // and returns identifier
    msgid = msgget(key, 0666 | IPC_CREAT);
    msg.mesg_type = 1;
    printf("Write Data : ");
    const char *buf = "hello world";
    memcpy(msg.mesg_text, buf, sizeof(buf));
    // msgsnd to send message
    msgsnd(msgid, &msg, sizeof(msg), 0);
    // display the message
    printf("Data send is : %s \n", msg.mesg_text);
    return 0;
}
