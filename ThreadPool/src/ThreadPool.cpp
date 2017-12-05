/*
    Date: 2017/11/11
    Author: shpdqyfan
    profile: Thread pool
*/

#include <iostream>

#include "ThreadPool.h"

ThreadPool::ThreadPool(size_t threadNum)
    : myRunning(true)
    , myThreadNum(threadNum)
{
    std::cout<<"ThreadPool, construct"<<std::endl;
	
    createThreadGroup();
}

ThreadPool::~ThreadPool()
{
    for(auto task : myTaskQueue)
    {
        delete task;
    }
    myTaskQueue.clear();

    std::cout<<"ThreadPool, deconstruct done"<<std::endl;
}

void ThreadPool::createThreadGroup()
{
    std::cout<<"ThreadPool, createThreadGroup"<<std::endl;
	
    pthread_mutex_init(&myMutex, NULL);
    pthread_cond_init(&myCond, NULL);
	
    myThreadGroup = (pthread_t*)malloc(sizeof(pthread_t) * myThreadNum);
    for(int i = 0;i < myThreadNum;i++)
    {
        int rlt = -1;
        while(0 != rlt)
        {
            rlt = pthread_create(&myThreadGroup[i], NULL, execute, this);
        }
    }

    std::cout<<"ThreadPool, createThreadGroup done"<<std::endl;
}

void ThreadPool::postTask(void (*func)(void* arg), void* arg)
{
    Task* task = new Task(func, arg);

    pthread_mutex_lock(&myMutex);
    myTaskQueue.push_back(task);
    pthread_cond_signal(&myCond);
    pthread_mutex_unlock(&myMutex);
}

Task* ThreadPool::getTask()
{
    Task* task = NULL;
    while(NULL == task)
    {
        pthread_mutex_lock(&myMutex);
        while(myTaskQueue.empty() && myRunning)
        {
       	    pthread_cond_wait(&myCond, &myMutex);
        }

        if(!myRunning)
        {
            pthread_mutex_unlock(&myMutex);				  
            break;
        }

        if(myTaskQueue.empty())
        {		
            pthread_mutex_unlock(&myMutex);
            continue;
	    }
        else
        {
            task = myTaskQueue.front();
            myTaskQueue.pop_front();
            pthread_mutex_unlock(&myMutex);
        }
    }
	
    return task;
}

size_t ThreadPool::getTaskNum()
{
    pthread_mutex_lock(&myMutex);
    size_t size = myTaskQueue.size();
    pthread_mutex_unlock(&myMutex);

    return size;
}

const size_t ThreadPool::getThreadNum() const 
{
    return myThreadNum;
}

void ThreadPool::stop()
{
    std::cout<<"ThreadPool, stop"<<std::endl;
	
    //pthread_mutex_lock(&myMutex);
    myRunning = false;        
    pthread_cond_broadcast(&myCond);
    //pthread_mutex_unlock(&myMutex);   

    for(int i = 0;i < myThreadNum;i++)
    {
        pthread_join(myThreadGroup[i], NULL);
    }

    free(myThreadGroup);
    myThreadGroup = NULL;

    pthread_cond_destroy(&myCond);
    pthread_mutex_destroy(&myMutex);

    std::cout<<"ThreadPool, stop done"<<std::endl;
}

void* ThreadPool::execute(void* arg)
{	
    ThreadPool* pool = static_cast<ThreadPool*>(arg);
    while(pool->myRunning)
    {
        Task* task = pool->getTask();
        if(NULL == task)
        {
            break;
        }

        task->myFunc(task->myArg);
        delete task;
    }
	
    return 0;
}
