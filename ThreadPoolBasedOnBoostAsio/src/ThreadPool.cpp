/*
    Date: 2017/11/11
    Author: shpdqyfan
    profile: Thread pool based on boost asio lib
*/
#include <iostream>

#include "ThreadPool.h"

ThreadPool::ThreadPool(size_t threadNum) 
    : myIoService()
    , myIoServiceWorker(new AsioServiceWorker::element_type(myIoService))
{
    std::cout<<"ThreadPool, construct"<<std::endl;
        
    for(size_t i = 0;i < threadNum;++i)
    {
        //The run() of myIoService will be invoked by multiple threads, 
        //so that the "task list" of myIoService can be shared.
        myThreadGroup.add_thread(new boost::thread(boost::bind(&boost::asio::io_service::run, &myIoService)));
    }
}

ThreadPool::~ThreadPool()
{
    //Allow run() to exit
    myIoServiceWorker.reset();
    
    myThreadGroup.join_all();
    
    //Stop the io_service object's event processing loop.
    myIoService.stop(); 
    
    std::cout<<"ThreadPool, deconstruct done"<<std::endl;
}

void ThreadPool::post(ThreadCallBack cb)
{
    //The posted cb will only be called in a thread in which run() of io_service is currently being invoked.
    myIoService.post(cb);
}

