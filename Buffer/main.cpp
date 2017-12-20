/*
    Date: 2017/12/18
    Author: shpdqyfan
    profile: Buffer supports to asynchronously and sequentially 
    process T-typed elements in a dedicated thread in FIFO order.
*/

#include <iostream>
#include <thread>
#include <vector>

#include "src/Buffer.h"

class Data
{
public:
    Data(int value){myValue = value;}
    int myValue;
};

void read(const Data& d)
{
    std::cout<<"read, data="<<d.myValue<<" in thread="<<std::this_thread::get_id()<<std::endl;
}

Buffer<Data> myBuffer(read);

void write(const Data& d)
{
    std::cout<<"write, data="<<d.myValue<<" in thread="<<std::this_thread::get_id()<<std::endl;
    myBuffer.pushToBuffer(d);
}

int main()
{
    std::cout<<"Welcome Buffer"<<std::endl;

    std::vector<std::thread> threadV;
    
    myBuffer.startBuffering();

    for(unsigned i = 1;i <= 10;i++)
    {
        Data d(i);
        threadV.push_back(std::thread(write, d));
    }

    for(unsigned i = 0;i < threadV.size();i++)
    {
        threadV[i].join();
    }

    myBuffer.stopBuffering();
    
    return 0;
}

