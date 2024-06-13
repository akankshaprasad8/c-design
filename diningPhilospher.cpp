#include <iostream>
#include <mutex>
#include <thread>
#include <condition_variable>
#include <queue>
using namespace std;
mutex m;
condition_variable cv;
vector<int> fork(5, 1);
//vector<int> alleat(5,0);
void diningPhilosophers(int philosopher)
{
    while (true)
    {
        unique_lock<mutex> lock(m);
        cv.wait(lock, [philosopher] { return fork[philosopher] && fork[(philosopher + 1) % 5];});//&&alleat[philosopher]==0; });
        fork[philosopher] = 0;
        fork[(philosopher + 1) % 5] = 0;
        cout << "Philosopher " << philosopher << " is eating." << endl;
        fork[philosopher] = 1;
        fork[(philosopher + 1) % 5] = 1;
        //alleat[philosopher]=1;
        cout << "Philosopher " << philosopher << " is thinking." << endl;
        cv.notify_all();
    }
}
void diningPhilosophersOddEven(int philosopher)
{
    unique_lock<mutex> lock(m);
    cv.wait(lock, [philosopher] { return fork[philosopher] && fork[(philosopher + 1) % 5]; });
    if(philosopher&1)
    {
        fork[philosopher] = 0;
        cout<<"Philosopher "<<philosopher<<" is picking up right fork."<<endl;
        fork[(philosopher + 1) % 5] = 0;
        cout<<"Philosopher "<<philosopher<<" is picking up left fork."<<endl;
    }
    else
    {
        fork[(philosopher + 1) % 5] = 0;
        cout<<"Philosopher "<<philosopher<<" is picking up left fork."<<endl;
        fork[philosopher] = 0;
        cout<<"Philosopher "<<philosopher<<" is picking up right fork."<<endl;
    }
    cout << "Philosopher " << philosopher << " is eating." << endl;
    fork[philosopher] = 1;
    cout<<"Philosopher "<<philosopher<<" is putting down right fork."<<endl;
    fork[(philosopher + 1) % 5] = 1;
    cout<<"Philosopher "<<philosopher<<" is putting down left fork."<<endl;
    cout << "Philosopher " << philosopher << " is thinking." << endl;
    cv.notify_all();
}
int main()
{
    vector<thread> threads;
    for (int i = 0; i < 5; i++)
    {
        threads.push_back(thread(diningPhilosophersOddEven, i));
    }
    for (auto &t : threads)
    {
        t.join();
    }
    return 0;
}