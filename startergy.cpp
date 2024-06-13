#include <iostream>
using namespace std;

class DrivingStratergy {
public: 
    virtual void drive() = 0; // Pure virtual function
};
class SportsDriving : public DrivingStratergy {
public:
    void drive()  {
        cout << "sports drive";
    }
};
class OffroadDriving: public DrivingStratergy{
    public:
    void drive() {
        cout<<"off road drive";
    }
};
class Vehicle {
public:
    DrivingStratergy *obj;
    Vehicle(DrivingStratergy obj) 
    {
        this->obj = obj;
    }
    void drive() {
        obj->drive();
    }
};

class SportVehicle : public Vehicle {
public:
    SportVehicle(){
        obj = new SportsDriving();
    }
};
class OffRoadVehicle: public Vehicle
{
    public:
    OffRoadVehicle(){
        obj = new OffroadDriving();
    }
};
/*
segrating statergy to implement vehicle and of different types with class implement,
in a way we are creating a base class which HAS A statergy and rest other objects are implemented by it
*/
int main() {
    SportVehicle vehicle;
    vehicle.drive();
    cout<<endl;
    OffRoadVehicle vehicle2;
    vehicle2.drive();
    return 0;
}
