/*
    Date: 2017/11/11
    Author: shpdqyfan
    profile: Thread pool
*/

#include <iostream>
#include <mutex>

#include "ThreadPool.h"

std::mutex myMutex;
int array[10] = {1,2,3,4,5,6,7,8,9,10};

void myThreadCallback(void* arg)
{
    int* val = static_cast<int*>(arg);

    std::unique_lock<std::mutex> guard(myMutex);
    std::cout<<"myThreadCallback: "<<*val<<std::endl;
}

int main()
{
    std::cout<<"Welcome ThreadPool"<<std::endl;
    
    ThreadPool myThreadPool(8);

    for(int i = 0;i <= 9;i++)
    {
        void* arg = static_cast<void*>(&array[i]);
        myThreadPool.postTask(myThreadCallback, arg);
    }
    
    return 0;
}

