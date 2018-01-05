/*
    Date: 2017/11/11
    Author: shpdqyfan
    profile: Thread pool
*/

#ifndef TASK_H
#define TASK_H

#include <iostream>

class Task
{
public:
    Task(void (*func)(void* arg), void* arg)
        : myFunc(func)
        , myArg(arg)
    {
        std::cout<<"Task, construct"<<std::endl;
    }

    ~Task()
    {
        std::cout<<"Task, deconstruct"<<std::endl;
    }

    void (*myFunc)(void* arg);
    void* myArg;

private:
    Task();
};

#endif
