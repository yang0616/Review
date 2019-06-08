#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <sys/msg.h>


struct msg_st
{
    long int msg_type;
    char text[512];
};

int main()
{
    int flag = 1;
    int msgid = -1;
    struct msg_st data;
    long int msgtype = 0;

    msgid = msgget((key_t)1234, 0600 | IPC_CREAT);
    if(msgid == -1)
    {
        perror("msgget error!\n");
        return 0;
    }

    while(flag)
    {
        if(msgrcv(msgid, (void*)&data, 512, msgtype, 0) == -1)
        {
            perror("msgrcv error!\n");
            return 0;
        }
        printf("data:%s\n", data.text);
        if(strncmp(data.text, "end", 3) == 0)
        {
            flag = 0;
        }
    }

    if(msgctl(msgid, IPC_RMID, 0) == -1)
    {
        perror("msgctl error!\n");
    }
    return 0;
}
