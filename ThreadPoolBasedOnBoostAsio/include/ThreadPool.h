/*
    Date: 2017/11/11
    Author: shpdqyfan
    profile: Thread pool based on boost asio lib
*/

#ifndef THREADPOOL_H
#define THREADPOOL_H

#include <memory>
#include <functional>
#include <boost/thread.hpp>
#include <boost/asio.hpp>

typedef std::unique_ptr<boost::asio::io_service::work> AsioServiceWorker;
typedef std::function<void(void)> ThreadCallBack;

class ThreadPool
{
public:
    explicit ThreadPool(size_t threadNum);
    ~ThreadPool();
    void post(ThreadCallBack cb);

private:
    //Just to prevent run() call of myIoService from returning 
    //when there is no more work to do.
    AsioServiceWorker myIoServiceWorker;
    boost::asio::io_service myIoService;
    boost::thread_group myThreadGroup;
};

#endif

