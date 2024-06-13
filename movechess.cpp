#include <iostream>
#include <vector>
using namespace std;
class Piece
{
public:
    vector<pair<int,int>>moves;
    virtual void move() = 0;
};
class King : public Piece
{
    public:

    //vector<pair<int,int>>moves={{1,0},{0,1},{1,1},{-1,0},{0,-1},{-1,-1},{1,-1},{-1,1}};    
    King()
    {
        cout << "King is created" << endl;
        moves.push_back({1,0});
        moves.push_back({0,1});
        moves.push_back({1,1});
        moves.push_back({-1,0});    
        moves.push_back({0,-1});
        moves.push_back({-1,-1});
        moves.push_back({1,-1});
        moves.push_back({-1,1});
        

    }
    void move()
    {
        cout << "One square in any direction" << endl;
        for(auto i : moves)
        {
            cout << i.first << " " << i.second << endl;
        }
    }

};
int main()
{
    Piece *p = new King();
    p->move();
    return 0;
}