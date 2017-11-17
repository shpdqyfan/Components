/*
    Date: 2017/11/11
    Author: shpdqyfan
    profile: Thread pool based on boost asio lib
*/

#include "ThreadPool.h"

ThreadPool::ThreadPool(size_t threadNum) 
    : myIoService()
    , myIoServiceWorker(new AsioServiceWorker::element_type(myIoService))
{
    for(size_t i = 0;i < threadNum;++i)
    {
        myThreadGroup.add_thread(new boost::thread(boost::bind(&boost::asio::io_service::run, &myIoService)));
    }
}

ThreadPool::~ThreadPool()
{
    myIoService.reset();
    myThreadGroup.join_all();
    myIoService.stop();
}

void ThreadPool::post(ThreadCallBack cb)
{
    myIoService.post(cb);
}

