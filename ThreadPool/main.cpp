/*
    Date: 2017/11/11
    Author: shpdqyfan
    profile: Thread pool
*/

#include <iostream>
#include <pthread.h>

#include "ThreadPool.h"

pthread_mutex_t myGolMutex;
int array[10] = {1,2,3,4,5,6,7,8,9,10};

void myThreadCallback(void* arg)
{
    int* val = static_cast<int*>(arg);
    pthread_t tid = pthread_self();

    pthread_mutex_lock(&myGolMutex);
    std::cout<<"myThreadCallback: val="<<*val<<", in thread id="<<tid<<std::endl;
    pthread_mutex_unlock(&myGolMutex);
}

int main()
{
    std::cout<<"Welcome ThreadPool"<<std::endl;

    pthread_mutex_init(&myGolMutex, NULL);
    ThreadPool myThreadPool(8);

    sleep(2);

    for(int i = 0;i <= 9;i++)
    {
        void* arg = static_cast<void*>(&array[i]);
        myThreadPool.postTask(myThreadCallback, arg);
    }

    sleep(2);

    myThreadPool.stop();
    
    return 0;
}
