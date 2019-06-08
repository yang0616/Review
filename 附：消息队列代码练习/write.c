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
    struct msg_st data;
    char buff[512];
    int msgid = -1;

    msgid = msgget((key_t)1234, 0600 | IPC_CREAT);
    if(msgid == -1)
    {
        perror("msgget error!\n");
        return 0;
    }

    while(flag)
    {
        printf("please input data:");
        fgets(buff, 512, stdin);
        data.msg_type = 1;
        strcpy(data.text, buff);

        if(msgsnd(msgid, (void*)&data, 512, 0) == -1)
        {
            perror("msgsnd error!\n");
            return 0;
        }

        if(strncmp(buff, "end", 3) == 0)
        {
            flag = 0;
        }
        sleep(1);
    }
    return 0;
}
