// Online C++ compiler to run C++ program online
#include <iostream>
using namespace std;
//virtual of interface
class Vehicle{
    public: 
    virtual int getseats()=0;
};
class Car: public Vehicle{
  public:
    int fuel=80;
    int wheels=4;
    int seats=4;
  int getseats(){
      return seats;
  }
};
class Nullobj: public Vehicle{
 public:
      int fuel=0;
    int wheels=0;
    int seats=0;
   int getseats(){
      return seats;
  }
};
class VehicleFactory{
  public:
  Vehicle* vehicle;
  VehicleFactory(string type)
  {
      if(type=="Car")
      {
          this->vehicle=new Car();
      }
      else
      this->vehicle=new Nullobj();
  }
  Vehicle* getobj()
  {
      return vehicle;
  }
};

int main() {
    VehicleFactory* vf=new VehicleFactory("Car");
    Vehicle* v=vf->getobj();
    cout<<v->getseats();
    return 0;
}