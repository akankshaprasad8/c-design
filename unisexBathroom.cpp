#include <iostream>
#include <thread>
#include <mutex>
#include <queue>
#include <condition_variable>
using namespace std;
mutex m;
condition_variable cv;
int flag=0;
int female=0;
int male=0;
void goToBathroom(string person,int seconds)
{
    unique_lock<mutex> lock(m);
    if(person=="female")
    {
        cv.wait(lock,[]{return flag==0||flag==2;});
        female++;
        flag=0;
        this_thread::sleep_for(chrono::seconds(seconds));
        cout<<"female in bathroom"<<endl;
        cout<<"female left bathroom"<<endl;
        female--;
        if(female==0)flag=2;
        cv.notify_all();
    }
    if(person=="male")
    {
        cv.wait(lock,[]{return flag==1||flag==2;});
        male++;
        flag=1;
        this_thread::sleep_for(chrono:: seconds(seconds));
        cout<<"male in bathroom"<<endl;
        cout<<"male left bathroom"<<endl;
        male--;
        if(male==0)flag=2;
        cv.notify_all();
    }
}
int main()
{
    thread t1(goToBathroom,"female",10);
    thread t2(goToBathroom,"male",2);
    thread t3(goToBathroom,"female",3);
    thread t8(goToBathroom,"female",2);
    thread t4(goToBathroom,"male",2);
    thread t5(goToBathroom,"female",1);
    thread t6(goToBathroom,"male",5);
    t1.join();
    t2.join();
    t3.join();
    t8.join();
    t4.join();
    t5.join();
    t6.join();
    return 0;
}