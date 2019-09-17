#include "threadpool.h"

//构造函数,确定线程池的线程数
Threadpool::Threadpool(size_t cntThread, size_t maxCount)
{
	//初始化条件变量与互斥量
	pthread_mutex_init(&lock, NULL);
	pthread_cond_init(&null, NULL);

	//创建线程
	pthread_t pid[cntThread];
	for (int i = 0; i<maxCount; i++)
	{
		pthread_create(pid + i, NULL, start, this);
	}
}

//析构函数
Threadpool::~Threadpool(void)
{
	//销毁条件变量与互斥量
	pthread_mutex_destroy(&lock);
	pthread_cond_destroy(&null);
}

//添加任务
bool Threadpool::addTask(Task task)
{
	//加锁
	pthread_mutex_lock(&lock);

	//检查任务数量
	if (taskQueue.size() >= maxCount)
	{
		cout << "任务已经满了" << endl;
		pthread_mutex_unlock(&lock);
		return false;
	}

	//加入任务到队列
	taskQueue.push(task);

	//唤醒空状态进入睡眠的线程
	pthread_cond_broadcast(&null);

	//解锁
	pthread_mutex_unlock(&lock);
}

//线程入口
void* Threadpool::start(void* arg)
{
	Threadpool* thread = (Threadpool*)arg;
	while (true)
	{
		//加锁访问任务队列
		pthread_mutex_lock(&thread->lock);

		while (thread->taskQueue.empty())
		{
			cout << pthread_self() << ":没活了，洗洗睡吧!" << endl;
			pthread_cond_wait(&thread->null, &thread->lock);
		}

		//从队列中获取任务
		Task task = thread->taskQueue.front();
		thread->taskQueue.pop();

		//先解锁，因为不知道任务需要执行多久
		pthread_mutex_unlock(&thread->lock);

		//执行任务
		task();
	}
}