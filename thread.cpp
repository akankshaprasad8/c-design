#include <iostream>
#include <thread>
#include <mutex>
using namespace std;
mutex m;
condition_variable cv;
int count=0;

void taskA()
{
    while(count<10)
    {  m.lock();
       cout<<count<<" ";
       count++; //critical section
        m.unlock();
     }
}
int main()
{
    thread t1(taskA);
    thread t2(taskA);
    t1.join();
    t2.join();
    return 0;
}
