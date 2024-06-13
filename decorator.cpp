// Online C++ compiler to run C++ program online
#include <iostream>
#include <bits/stdc++.h>
using namespace std;
class Pizza{
    public:
    int price;
    virtual void OrderDisplay()=0;
    virtual int TotalPrice()=0;
};
class CountryDeligh:public Pizza{
    public :
    int price=300;
    void OrderDisplay()
    {
        cout<<"Ordering base as CountryDeligh"<<endl;
    }
    int TotalPrice()
    {
        return this->price;
    }
};
class ExtraCheese:public Pizza{
    public :
    Pizza* pizza;
    int cheesePrice=40;
    ExtraCheese(Pizza* pizza)
    {
        this->pizza=pizza;
    }
    void OrderDisplay()
    {
        cout<<"adding extra cheese";
    }
    int TotalPrice()
    {
        this->pizza->price=pizza->TotalPrice()+cheesePrice;
        return pizza->price;
    }
};

int main() {
    // Write C++ code here
    Pizza* pizza=new CountryDeligh();
    pizza->OrderDisplay();
    cout<<pizza->TotalPrice()<<endl;
    Pizza* extracheese= new ExtraCheese(pizza);
    cout<<extracheese->TotalPrice()<<endl;
    Pizza *extracheese2= new ExtraCheese(extracheese);
    cout<<extracheese2->TotalPrice();
    return 0;
}