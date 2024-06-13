// Online C++ compiler to run C++ program online
#include <iostream>
using namespace std;
class Shape{
    public:
    virtual void draw()=0;
};
class Circle: public Shape{
    public :
    void draw()
    {
        cout<<"Circle draw"<<endl;
    }
};
class Square: public Shape{
    public :
    void draw()
    {
        cout<<"Square draw"<<endl;
    }
};
class ShapeFactory{
public:
   Shape* getShape(string input)
   {
       if(input=="CIRCLE")
       {
           return new Circle();
       }
       else
       {
           return new Square();
       }
   }
};

int main() {
    // Write C++ code here
    ShapeFactory* sh=new ShapeFactory();
    Shape* s=sh->getShape("Square");
    s->draw();
    return 0;
}