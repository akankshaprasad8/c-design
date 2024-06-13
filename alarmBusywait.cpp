#include <iostream>
#include <thread>
#include <mutex>
#include <queue>
#include <condition_variable>
using namespace std;
mutex m;
void alarm()
{
    cout << "Alarm is ringing" << endl;
}
void schedule_alarm(int seconds)
{
    //auto current_time = chrono::system_clock::now();
    m.lock();
    cout << "Alarm scheduled after " << seconds << " seconds" << endl;
    m.unlock();
    this_thread::sleep_for(chrono::seconds(seconds));
    m.lock();
    alarm();
    m.unlock();
}
int main()
{
    thread t1(schedule_alarm, 5);
    thread t2(schedule_alarm, 10);
    thread t3(schedule_alarm, 2);
    t1.join();
    t2.join();
    t3.join();
    return 0;
}