// Online C++ compiler to run C++ program online
#include <iostream>
#include <bits/stdc++.h>
using namespace std;
class EmployeeIn{
    public:
    virtual void create(string client)=0;
    virtual void get(string client)=0;
    virtual void deleteE(string client)=0;
};
class Employee:public EmployeeIn{
    public:
    void create(string client)
    {
        cout<<"added client";
    }
    void get(string client)
    {
        cout<<"getting client";
    }
    void deleteE(string client)
    {
        cout<<"deleting success";
    }
};
class EmployeeProxy:public EmployeeIn{
    public:
    Employee* en;
    EmployeeProxy()
    {
        this->en=new Employee();
    }
    void create(string client)
    {
        if(client=="ADMIN"){
        en->create(client);
        }
        else 
        {
            cout<<"not admin";
        }
    }
    void get(string client)
    {
        en->get(client);
    }
    void deleteE(string client)
    {
        if(client=="ADMIN"){
        en->deleteE(client);
        }
        else 
        {
            cout<<"not admin";
        }
    }
};
int main() {
    // Write C++ code here
    EmployeeIn* emp=new EmployeeProxy();
    emp->create("ADMIN");
    cout<<endl;
    emp->get("ADMIN");
    cout<<endl;
    emp->deleteE("USER");
    return 0;
}