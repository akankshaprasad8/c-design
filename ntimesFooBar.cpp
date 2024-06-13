#include <iostream>
#include <thread>
#include <mutex>
#include <random>
#include <condition_variable>
using namespace std;
//mutex m;
mutex m1,m2;
/*int flag = 0;
condition_variable cv;
*/
void printFoo(int n)
{
    while(n>0)
    {
    /*unique_lock<mutex> lock(m);
    cv.wait(lock, [] { return flag == 0; });  
    */
    m1.lock();  
    n--;    
    //flag=1;
    cout << "foo";
    m2.unlock();
    //cv.notify_all();
    }
}
void printBar(int n)
{
    while(n>0)
    {
    /*unique_lock<mutex> lock(m);
    cv.wait(lock, [] { return flag == 1; });*/
    m2.lock();
    n--;
    //flag=0;
    cout << "bar"<<endl;
    m1.unlock();
    //cv.notify_all();
    }
}
int main()
{
    thread t1(printFoo, 10);
    thread t2(printBar, 10);
    t1.join();
    t2.join();
    return 0;
}