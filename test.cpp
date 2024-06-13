// Online C++ compiler to run C++ program online
#include <iostream>
#include <unordered_map>
#include <vector>
using namespace std;
int parent(int i,unordered_map<int,int>&par)
{
    if(par[i]==i)
    {
        return i;
    }
    return par[i]=parent(par[i],par);
}
void union1(int i,int j,unordered_map<int,int>&par,unordered_map<int,int>&rank)
{
    int p1=parent(i,par);
    int p2=parent(j,par);
    if(rank[p1]>rank[p2])
    {
        par[p2]=p1;
    }
    else if(rank[p1]<rank[p2])
    {
        par[p1]=p2;
    }
    else
    {
        par[p1]=p2;
        rank[p2]++;
    }
}
int getminoperation(vector<int>data)
{
    unordered_map<int,int>par(data.size());
    unordered_map<int,int>rank(data.size());
    int ans=0;
    for(int i=0;i<data.size();i++)
    {
        par[data[i]]=data[i];
        rank[data[i]]=1;
    }
    for(int i=0;i<data.size()/2;i++)
    {
        if(par[data[i]]!=par[data[data.size()-1-i]])
        {
            ans++;
            union1(data[i],data[data.size()-1-i],par,rank);
        }
    }
    return ans;
}
int main() {
    cout<<getminoperation({2,4,5,7,4,5,5});
    return 0;
}