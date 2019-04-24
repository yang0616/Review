#include <sys/sem.h>
#include <pthread.h>
#include <iostream>
#include <time.h>
#include <stdlib.h>
using namespace std;

static int sem_id = 0;

union semun
{
	int val;
};

static int sem_init()
{
	union semun sem_union;
	sem_union.val = 3;

	if (semctl(sem_id, 0, SETVAL, sem_union) == -1)
	{
		cout << "semctl faild!" << endl;
		return 0;
	}
}

static void sem_destroy()
{
	union semun sem_union;

	if (semctl(sem_id, 0, SETVAL, sem_union) == -1)
	{
		cout << "semaphore destroy faild!" << endl;
	}
	cout << "semaphore destroy successful!" << endl;
}

static int sem_p()
{
	struct sembuf buf;
	buf.sem_num = 0;
	buf.sem_op = -1;
	buf.sem_flg = SEM_UNDO;
	if (semop(sem_id, &buf, 1) == -1)
	{
		cout << "semaphore_p faild!" << endl;
		return 0;
	}
	return 1;
}

static int sem_v()
{
	struct sembuf buf;
	buf.sem_num = 0;
	buf.sem_op = +1;
	buf.sem_flg = SEM_UNDO;
	if (semop(sem_id, &buf, 1) == -1)
	{
		cout << "semaphore_p faild!" << endl;
		return 0;
	}
	return 1;
}

void *doBank(void* arg)
{
	int tmp = *(int*)arg;

	cout << "pthread" << tmp << "wait" << endl << endl;
	sem_p();

	cout << "pthread" << tmp << "start" << endl << endl;
	for (int i = 0; i < 1; i++)
	{
		cout << "pthread" << tmp << "doing......" << endl << endl;;
		sleep(rand() % 3 + 1);
	}
	cout << "pthread" << tmp << " end" << endl << endl;

	sem_v();
}

int main()
{
	sem_id = semget((key_t)1234, 1, 0666 | IPC_CREAT);
	if (sem_id == -1)
	{
		cout << "semget faild!" << endl;
	}
	else
	{
		cout << "semget successful" << endl;
	}


	sem_init();

	pthread_t t[6];
	void *pthread_result = NULL;

	srand((unsigned long)time(NULL));
	int i;
	int count[6] = { 1, 2, 3, 4, 5, 6 };
	for (i = 0; i < 6; i++)
	{
		int res = pthread_create(&t[i], NULL, doBank, (void*)&count[i]);
		if (res != 0)
		{
			cout << "pthread create faild." << endl;
			return 0;
		}
	}

	for (i = 0; i < 6; i++)
	{
		pthread_join(t[i], &pthread_result);
	}

	sem_destroy();

	return 0;
}


