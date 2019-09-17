#include "threadpool.h"
#include <stdlib.h>
void work(void)
{
	int cnt = rand() % 10;
	for (int i = 0; i<rand(); i++)
	{
		cout << pthread_self() << ":" << i << endl;
		sleep(1);
	}
}

int main()
{
	pthread_t pid[3] = {};
	int cnt = 0;
	Threadpool* thread = new Threadpool(3, 8);
	while (true)
	{
		cout << "请输入要添加的任务数:" << endl;
		cin >> cnt;
		for (int i = 0; i<10; i++)
		{
			thread->addTask(work);
		}
	}
	pause();
}
