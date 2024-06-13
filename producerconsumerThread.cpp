#include <iostream>
#include <thread>
#include <mutex>
#include <queue>
#include <condition_variable>
using namespace std;
queue<int> q;
mutex m;
condition_variable cv;
int max_=10;
void producer(int val)
{
  while(val>0)
  {
    unique_lock<mutex> lock(m);
    cv.wait(lock,[]{return q.size()<max_;});
    q.push(val);
    cout<<"Produced: "<<val<<endl;
    chrono::milliseconds dura(2000);
    this_thread::sleep_for(dura);
    val--;
    cv.notify_all();
  }
}
void consumer()
{
  while(true)
  {
    unique_lock<mutex> lock(m);
    cv.wait(lock,[]{return q.size()>0;});
    int val=q.front();
    q.pop();
    cout<<"Consumed: "<<val<<endl;
    cv.notify_all();
  }
}
int main()
{
    thread t1(producer,3);
    thread t4(producer,1);
    thread t2(consumer);
    thread t3(consumer);
    t1.join();
    t2.join();
    t3.join();
    t4.join();
    return 0;   
}