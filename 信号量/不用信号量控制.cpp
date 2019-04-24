#include <sys/sem.h>
#include <pthread.h>
#include <iostream>
#include <time.h>
#include <stdlib.h>
using namespace std;

void *doBank(void* arg)
{
    int tmp = *(int*)arg;
    cout << "pthread" << tmp <<"start" << endl << endl;
    for(int i = 0; i < 3; i++)
    {
        cout << "pthread"<< tmp <<"doing......" << endl << endl;;
        sleep(rand()%3);
    }
    cout << "pthread" << tmp << " end" << endl << endl;
}

int main()
{
    pthread_t t[6];
    void *pthread_result = NULL;
    
    srand((unsigned long)time(NULL));
    int i;
    int count[6] = {1, 2, 3, 4, 5, 6};
    for(i = 0; i < 6; i++)
    {
        int res = pthread_create(&t[i], NULL, doBank, (void*)&count[i]);
        if(res != 0)
        {
            cout << "pthread create faild." << endl;
            return 0;
        }
    }

    for(i = 0; i < 6; i++)
    {
        pthread_join(t[i], &pthread_result);
    }

    return 0;
}

