#include <iostream>
#include <thread>
#include <mutex>
#include <random>
#include <condition_variable>
using namespace std;
//mutex m;
mutex m1,m2,m3;
//int flag = 0;
//condition_variable cv;
void printFirst() {
    /*unique_lock<mutex> lock(m);
    cv.wait(lock, [] { return flag == 0; });
    flag=1;*/
    m1.lock();
    cout << "First" << endl;
    m2.unlock();
    //cv.notify_all();
}
void printSecond() {
    /*unique_lock<mutex> lock(m);
    cv.wait(lock, [] { return flag == 1; });
    flag=2;*/
    m2.lock();
    cout << "Second" << endl;
    m3.unlock();
    //cv.notify_all();
}
void printThird() {
    /*unique_lock<mutex> lock(m);
    cv.wait(lock, [] { return flag == 2; });
    flag=3;*/
    m3.lock();
    cout << "Third" << endl;
    m1.unlock();
    //cv.notify_all();
}
int main() {
    m1.unlock();
    m2.lock();
    m3.lock();
    thread t1(printFirst);
    thread t2(printSecond);
    thread t3(printThird);
    t1.join();
    t2.join();
    t3.join();
    return 0;
}