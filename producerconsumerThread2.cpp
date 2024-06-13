#include <iostream>
#include <mutex>
#include <thread>
#include <condition_variable>
#include <queue>
using namespace std;
queue<int>q;
mutex m;
condition_variable cv;
int maxSize=10;
void producer(int val){
    while(val>0){
        unique_lock<mutex>lock(m);
        cv.wait(lock,[]{return q.size()<maxSize;});
        q.push(val);
        cout<<"Produced: "<<val<<endl;
        val--;
        cv.notify_all();
    }
}
void consumer(){
    while(true){
    unique_lock<mutex>lock(m);
    cv.wait(lock,[]{return q.size()>0;});
    cout<<q.front()<<endl;
    q.pop();
    cv.notify_all();
}
}
int main(){
    thread t1(producer,20);
    thread t2(consumer);
    t1.join();
    t2.join();
    return 0;
}