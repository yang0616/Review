#include "threadpool.h"

//���캯��,ȷ���̳߳ص��߳���
Threadpool::Threadpool(size_t cntThread, size_t maxCount)
{
	//��ʼ�����������뻥����
	pthread_mutex_init(&lock, NULL);
	pthread_cond_init(&null, NULL);

	//�����߳�
	pthread_t pid[cntThread];
	for (int i = 0; i<maxCount; i++)
	{
		pthread_create(pid + i, NULL, start, this);
	}
}

//��������
Threadpool::~Threadpool(void)
{
	//�������������뻥����
	pthread_mutex_destroy(&lock);
	pthread_cond_destroy(&null);
}

//�������
bool Threadpool::addTask(Task task)
{
	//����
	pthread_mutex_lock(&lock);

	//�����������
	if (taskQueue.size() >= maxCount)
	{
		cout << "�����Ѿ�����" << endl;
		pthread_mutex_unlock(&lock);
		return false;
	}

	//�������񵽶���
	taskQueue.push(task);

	//���ѿ�״̬����˯�ߵ��߳�
	pthread_cond_broadcast(&null);

	//����
	pthread_mutex_unlock(&lock);
}

//�߳����
void* Threadpool::start(void* arg)
{
	Threadpool* thread = (Threadpool*)arg;
	while (true)
	{
		//���������������
		pthread_mutex_lock(&thread->lock);

		while (thread->taskQueue.empty())
		{
			cout << pthread_self() << ":û���ˣ�ϴϴ˯��!" << endl;
			pthread_cond_wait(&thread->null, &thread->lock);
		}

		//�Ӷ����л�ȡ����
		Task task = thread->taskQueue.front();
		thread->taskQueue.pop();

		//�Ƚ�������Ϊ��֪��������Ҫִ�ж��
		pthread_mutex_unlock(&thread->lock);

		//ִ������
		task();
	}
}