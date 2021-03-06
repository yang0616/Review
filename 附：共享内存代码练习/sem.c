#include <stdio.h>
#include <error.h>
#include "sem.h"

static int semid = -1;

void sem_init()
{
    semid = semget((key_t)1234, 1, IPC_CREAT | IPC_EXCL | 0600);
    if(semid == -1)
    {
        semid = semget((key_t)1234, 1, 0600);
        if(semid == -1)
        {
            perror("semget error\n");
        }
    }
    else
    {
        union semun a;
        a.val = 0;

        if(semctl(semid, 0, SETVAL, a) == -1)
        {
            perror("semctl setval error\n");
        }
    }
}

void sem_p()
{
    struct sembuf buf;
    buf.sem_num = 0;
    buf.sem_op = -1;
    buf.sem_flg = SEM_UNDO;

    if(semop(semid, &buf, 1) == -1)
    {
        perror("semop error\n");
    }
}

void sem_v()
{
    struct sembuf buf;
    buf.sem_num = 0;
    buf.sem_op = 1;
    buf.sem_flg = SEM_UNDO;

    if(semop(semid, &buf, 1) == -1)
    {
        perror("semop error\n");
    }
}

void sem_destory()
{
    if(semctl(semid, 0, IPC_RMID) == -1)
    {
        perror("semctl error\n");
    }
}
