/*
    Date: 2016/11/08
    Author: shpdqyfan
    profile: a simple thread
*/

#include <iostream>
#include <memory>
#include <unistd.h>

#include "Thread.h"

class TestThread : public MyThread
{
public:
    TestThread()
    {
        std::cout<<"TestThread construct"<<std::endl;
    }

    ~TestThread()
    {
        std::cout<<"TestThread deconstruct"<<std::endl;
    }

protected:
    virtual void run()
    {
        setRunningState(RUNNING);
        std::cout<<"hello test thread id="<<std::this_thread::get_id()<<std::endl;
    }
};

int main()
{
    std::cout<<"hello main thread id="<<std::this_thread::get_id()<<std::endl;

    std::unique_ptr<TestThread> testPtr = std::unique_ptr<TestThread>(new TestThread());
    testPtr->start();

    do
    {
        std::cout<<"test thread start ..."<<std::endl;
    }while(!testPtr->getRunningState());

    std::cout<<"test thread start ok"<<std::endl;
    
    testPtr->join();
    
    return 0;
}

