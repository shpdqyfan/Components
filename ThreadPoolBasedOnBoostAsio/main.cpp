/*
    Date: 2017/11/11
    Author: shpdqyfan
    profile: Thread pool based on boost asio lib
*/

#include <iostream>
#include <thread>

#include "ThreadPool.h"

void myThreadCallback()
{
    std::cout<<"myThreadCallback, thread id="<<std::this_thread::get_id()<<std::endl;
    sleep(1);
}

int main()
{
    ThreadPool myThreadPool(8);
    for(size_t i = 0;i < 10;++i)
    {
        myThreadPool.post(myThreadCallback);
    }
    
    return 0;
}

