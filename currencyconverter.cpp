#include <iostream>
#include <unordered_map>
#include <vector>
#include <queue>
using namespace std;
float currencyConverter(unordered_map<string,vector<pair<string,float>>> graph,string source,string destination,int amount)
{
    queue<pair<string,float>> q;
    unordered_map<string,bool> visited;
    q.push({source,amount});
    while(!q.empty())
    {
        int size=q.size();
        while(size>0)
        {
            size--;
            auto front=q.front();
            q.pop();
            if(front.first==destination)
            {
                return front.second;
            }
            if(visited[front.first]==true)continue;
            visited[front.first]=true;            
            for(auto x:graph[front.first])
            {
                if(!visited[x.first])
                {
                    q.push({x.first,x.second*front.second});
                }
            }
        }
    }
    return -1;
}
int main()
{

    unordered_map<string,vector<pair<string,float>>> graph;
    graph["USD"].push_back({"EUR",0.84});
    graph["USD"].push_back({"INR",74.84});
    graph["USD"].push_back({"GBP",0.74});
    graph["EUR"].push_back({"USD",1.18});
    graph["INR"].push_back({"USD",1/74.84});
    graph["GBP"].push_back({"USD",1.35});
    
    cout<<currencyConverter(graph,"GBP","INR",100)<<endl;
    cout<<currencyConverter(graph,"USD","EUR",100);
    return 0;
}