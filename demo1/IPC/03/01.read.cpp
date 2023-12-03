#include <stdio.h>
#include <sys/ipc.h>
#include <sys/msg.h>
// structure for message queue
typedef struct mesg_buffer
{
    long mesg_type;
    char mesg_text[100];
} message;

int main()
{
    key_t key;
    message msg;
    int msgid;
    // ftok to generate unique key
    key = ftok("progfile", 65);
    // msgget creates a message queue     // and returns identifier
    msgid = msgget(key, 0666 | IPC_CREAT);
    // msgrcv to receive message
    msgrcv(msgid, &msg, sizeof(msg), 1, 0);
    // display the message
    printf("Data Received is : %s \n", msg.mesg_text);
    // to destroy the message queue
    msgctl(msgid, IPC_RMID, NULL);
    return 0;
}
