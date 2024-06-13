#include <iostream>
#include <mutex>
using namespace std;


class Singleton {
private:
    int data;
    static Singleton* singletonObj;
    static mutex mtx; // Mutex for thread safety
    Singleton(int data) {
        this->data = data;
    }
public:
    static Singleton* GetInstance(int data) {
        if (singletonObj == nullptr) {
            lock_guard<mutex> lock(mtx); // Lock the mutex
            if (singletonObj == nullptr) {
                singletonObj = new Singleton(data);
            }
        }
        return singletonObj;
    }
    int getData() {
        return data;
    }
    void changeData(int datanew)
    {
        this->data=datanew;
    }
};

Singleton* Singleton::singletonObj = nullptr;
mutex Singleton::mtx; // Initialization of static member

int main() {
    std::cout << "Try programiz.pro" << std::endl;
    
    // Get instance of Singleton
    Singleton* obj = Singleton::GetInstance(4);
    
    // Access data member of Singleton object
    std::cout << "Data: " << obj->getData() << std::endl;
    cout<<obj<<endl;
    Singleton* obj2 = Singleton::GetInstance(5);
    cout<<obj2<<endl;
    std::cout << "Data: " << obj2->getData() << std::endl;
    obj2->changeData(3);
    std::cout << "Data: " << obj->getData() << std::endl;

    return 0;
}
