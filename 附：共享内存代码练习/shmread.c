#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/shm.h>
#include <assert.h>
#include "sem.h"

int main()
{
    sem_init();
    int shmid = shmget((key_t)1234, 256, IPC_CREAT|0600);
    assert(shmid != -1);

    char* p = (char *)shmat(shmid, NULL, 0);

    while(1)
    {
        sem_p();
        if(strncmp(p, "end", 3) == 0)
        {
            break;
        }

        printf("%s\n", p);
        sleep(1);
    }
    shmdt(p);
    sem_destory();
    shmctl(shmid, IPC_RMID, NULL);
    return 0;
}
