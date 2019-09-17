#ifndef THREADPOOL_H
#define THREADPOOL_H

#include <iostream>
#include <queue>
#include <pthread.h>
#include <unistd.h>

using namespace std;

//������������
typedef void(*Task)(void);

class Threadpool
{
	//�����������
	queue<Task> taskQueue;
	//�����������
	size_t maxCount;
	//��ǰ��������
	size_t cuiCount;
	//��������
	pthread_cond_t null;
	//������
	pthread_mutex_t lock;

public:
	//���캯��,ȷ���̳߳ص��߳���
	Threadpool(size_t cntThread, size_t maxCount);
	//��������
	~Threadpool(void);
	//�������
	bool addTask(Task task);
	//�߳����
	static void* start(void*);
};

#endif//THREADPOOL_H
