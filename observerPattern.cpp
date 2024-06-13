// Online C++ compiler to run C++ program online
#include <iostream>
#include <bits/stdc++.h>
using namespace std;
class Obervers
{
    public:
    virtual void update()=0;
};
class Obervers1 :public Obervers
{
    public:
    void update() override
    {
        cout<<"notify by oberserv1"<<endl;
    }
};
class Obervers2 :public Obervers
{
    public:
    void update() override
    {
        cout<<"notify by oberserv2"<<endl;
    }
};
class Observable{
    public:
    vector<Obervers*>observerlist;
    int temp;
    void add(Obervers* obj)
    {
        observerlist.push_back(obj);
    }
    void remove(Obervers* obj)
    {
        auto idx= find(observerlist.begin(),observerlist.end(),obj);

            observerlist.erase(idx);

    }
    void notify()
    {
        for(int i=0;i<observerlist.size();i++)
        {
            observerlist[i]->update();
        }
    }
    void setdata(int temp)
    {
        this->temp=temp;
        notify();
    }
};
int main() {
    // Write C++ code here
    Obervers* obj=new Obervers1();
    Observable* data= new Observable();
    data->add(obj);
    data->setdata(4);
    cout<<"adding oberver2"<<endl;
    Obervers* obj2=new Obervers2();
    data->add(obj2);
    data->setdata(4);
    cout<<"removing oberver1"<<endl;
    data->remove(obj);
    data->setdata(4);

    return 0;
}