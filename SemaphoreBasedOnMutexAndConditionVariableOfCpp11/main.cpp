/*
    Author: shpdqyfan
    profile: A simple semaphore which based on mutex and 
               condition variable of cplusplus 11. Because of no
               semaphore provided by cplusplus 11 standard lib.
*/

#include <unistd.h>
#include <thread>
#include <iostream>

#include "SemaphoreBasedOnMutexAndConditionVariableOfCpp11.h"

//test case 1 begin
/*
Semaphore mySem(0);

void threadWaitingSem()
{
    mySem.wait();
}

int main()
{
    std::thread ta(threadWaitingSem);
    sleep(5);
    mySem.notify();
    ta.join();
    
    return 0;
}
*/
//test case 1 end

//test case 2 begin
/*
Semaphore mySem(0);

void threadWaitingSem()
{
    mySem.waitFor(3000);
}

int main()
{
    std::thread ta(threadWaitingSem);
    sleep(2);
    mySem.notify();
    ta.join();
    
    return 0;
}
*/
//test case 2 end

//test case 3 begin
/*
Semaphore mySem(1);

void threadWaitingSem()
{
    mySem.wait();
}

int main()
{
    std::thread ta(threadWaitingSem);
    sleep(5);
    mySem.notify();
    ta.join();
    
    return 0;
}
*/
//test case 3 end

//test case 4 begin
Semaphore mySem(0);
int number = 0;

void calcNumber()
{
    mySem.wait();
    number++;
    std::cout<<"number="<<number<<std::endl;
}

int main()
{
    std::thread ta(calcNumber);
    std::thread tb(calcNumber);
    std::thread tc(calcNumber);

    for(int i = 0;i < 3;i++)
    {
        sleep(1);
        mySem.notify();
    }

    ta.join();
    tb.join();
    tc.join();
    return 0;
}
//test case 4 end

