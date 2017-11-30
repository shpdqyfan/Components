/*
    Date: 2017/11/11
    Author: shpdqyfan
    profile: Thread pool
*/

#ifndef THREAD_POOL_H
#define THREAD_POOL_H

#include <deque>
#include <pthread.h>
#include <boost/noncopyable.hpp>

#include "Task.h"

class ThreadPool : private boost::noncopyable
{
public:
    ThreadPool(size_t threadNum = 8);
    ~ThreadPool();

    void postTask(void (*func)(void* arg), void* arg);
    Task* getTask();
    size_t getTaskSize();
    size_t getThreadNum();
    void stop();

private:
    void createThreadGroup();
    static void* execute(void* arg);

    bool myRunning;
    size_t myThreadNum;
    std::deque<Task*> myTaskQueue;
    pthread_mutex_t myMutex;
    pthread_cond_t myCond;
    pthread_t* myThreadGroup;
};

#endif

