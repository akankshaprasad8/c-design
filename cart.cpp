// Online C++ compiler to run C++ program online
#include <iostream>
#include <bits/stdc++.h>
using namespace std;
class Items{
    public:
    int id;
    string name;
    int price;
    string brand;
    string category;
    Items(string name,int id,int price,string brand,string category)
    {
        this->id=id;
        this->name=name;
        this->price=price;
        this->brand=brand;
        this->category=category;
    }
};
class Inventory{
  public:
  unordered_map<Items*,int> itemsQuantity;  
};
class InventoryManagment{
    public:
    Inventory* inventory;
    InventoryManagment(Inventory* inventory)
    {
        this->inventory=inventory;
    }
    void getItems()
    {
        for(auto i:inventory->itemsQuantity)
        {
            cout<<i.first->name<<" "<<i.second<<endl;
        }
    }
    void addItems(Items* item,int quantity)
    {
        if(inventory->itemsQuantity.find(item)==inventory->itemsQuantity.end())
        {
            inventory->itemsQuantity[item]=quantity;
        }
        else
        {
            inventory->itemsQuantity[item]+=quantity;
        }
        cout<<item->name<<" added successfully"<<endl;
    }
};
class CustomerCart{
    public:
    unordered_map<Items*,int> orderedItems;
    CustomerCart()
    {
        orderedItems=unordered_map<Items*,int>();
    }
    void emptyCart()
    {
        orderedItems.clear();
    }
    void getItems()
    {
        for(auto i:orderedItems)
        {
            cout<<i.first->name<<" "<<i.second<<endl;
        }
    }
    void addItems(Items* item,int quantity)
    {
        if(orderedItems.find(item)==orderedItems.end())
        {
            orderedItems[item]=quantity;
        }
        else
        {
            orderedItems[item]+=quantity;
        }
    }
    void deleteItems(Items* item,int quantity)
    {
        if(orderedItems.find(item)==orderedItems.end())
        {
            cout<<"Item not found in cart"<<endl;
        }
        else
        {
            if(orderedItems[item]<quantity)
            {
                cout<<"Quantity not available"<<endl;
            }
            else
            {
                orderedItems[item]-=quantity;
            }
        }
    }
    void updateQuatity(Items* item,int quantity)
    {
        if(orderedItems.find(item)==orderedItems.end())
        {
            cout<<"Item not found in cart"<<endl;
        }
        else
        {
            orderedItems[item]=quantity;
        }
    }
};
class Customer{
    public:
    string name;
    string address;
    string email;
    string phone;
    CustomerCart* cart;
    int money;
    Customer(string name,string address,string email,string phone,int money)
    {
        this->name=name;
        this->address=address;
        this->email=email;
        this->phone=phone;
        this->cart=new CustomerCart();
        this->money=money;
    }
    void addMoney(int money)
    {
        this->money+=money;
    }
    void placeOrder()
    {
        int total=0;
        for(auto i:cart->orderedItems)
        {
            total+=i.first->price*i.second;
        }
        if(total>money)
        {
            cout<<"Insufficient balance"<<endl;
        }
        else
        {
            money-=total;
            cart->orderedItems.clear();
            cout<<"Order placed successfully"<<endl;
        }
    }
};
class FlipkartOrderingSystem{
    unordered_map<string,Customer*> customers;
    InventoryManagment* inventoryManagment;
    public:
    FlipkartOrderingSystem(InventoryManagment* inventoryManagment)
    {
        this->inventoryManagment=inventoryManagment;
    }
    void addCustomer(Customer* customer)
    {
        customers[customer->name]=customer;
    }
    void deleteCustomer(string name)
    {
        customers.erase(name);
    }
    void getCustomer(string name)
    {
        cout<<customers[name]->name<<" "<<customers[name]->address<<" "<<customers[name]->email<<" "<<customers[name]->phone<<" "<<customers[name]->money<<endl;
    }
    void Checkout(string name)
    {
        customers[name]->placeOrder();
    }
    void GetCart(string name)
    {
        customers[name]->cart->getItems();
    }
};
class Search{
    public: 
    vector<Items*>filterItems;
    InventoryManagment* inventoryManagment;
    Search(InventoryManagment* inventoryManagment)
    {
        this->inventoryManagment=inventoryManagment;
    }
    void getItems()
    {
        for(auto i:filterItems)
        {
            cout<<i->name<<endl;
        }
    }
};
class SearchBuilder{
    public:
    Search* search;
    SearchBuilder(Search* search)
    {
        this->search=search;
    }
    SearchBuilder* ByCategory(string category)
    {
        for(auto i:search->inventoryManagment->inventory->itemsQuantity)
        {
            if(i.first->category==category)
            {
                this->search->filterItems.push_back(i.first);
            }
        }
        return this;
    }
    SearchBuilder* ByBrand(string brand)
    {
        for(auto i:search->inventoryManagment->inventory->itemsQuantity)
        {
            if(i.first->brand==brand)
            {
                this->search->filterItems.push_back(i.first);
            }
        }
        return this;
    }
    SearchBuilder* byPrice(int price)
    {
        for(auto i:search->inventoryManagment->inventory->itemsQuantity)
        {
            if(i.first->price==price)
            {
                this->search->filterItems.push_back(i.first);
            }
        }
        return this;
    }
};
int main() {
    // Write C++ code here
    Items* item1 = new Items("Shirt",1,1000,"Puma","Clothing");
    Items* item2 = new Items("Shoes",2,2000,"Nike","Footwear");
    Inventory* inventory = new Inventory();
    InventoryManagment inventoryManagment(inventory);
    inventoryManagment.addItems(item1,10);
    inventoryManagment.addItems(item2,20);
    inventoryManagment.getItems();
    Customer customer("Rahul","Delhi","rahul@gmail.com","9910",3000);
    FlipkartOrderingSystem flipkartOrderingSystem(&inventoryManagment);
    flipkartOrderingSystem.addCustomer(&customer);
    customer.cart->addItems(item1,2);
    customer.cart->addItems(item2,3);
    customer.cart->getItems();
    customer.cart->deleteItems(item1,1);
    customer.cart->updateQuatity(item1,1);
    customer.placeOrder();
    Search search(&inventoryManagment);
    SearchBuilder searchBuilder(&search);
    SearchBuilder* result = searchBuilder.ByCategory("Clothing")->ByBrand("Puma");
    result->search->getItems();

    delete item1;
    delete item2;

    return 0;
}