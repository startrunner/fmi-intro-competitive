#include <iostream>
#include <vector>
#include <set>
#include <tuple>
#include <cstdio>
using namespace std;

int n, q;
vector<int> items;
vector<pair<int, int>> queries;

void read()
{
    cin>>n;
    items.resize(n);
    for(int &x : items)cin>>x;

    cin>>q;
    queries.resize(q);
    for(auto &x : queries)cin>>x.first>>x.second;
}

void solve()
{
    set<int> itemSet;
    vector<pair<int, int>> uniqueByIndex;
    for(int i=0; i<n; i++)
    {
        int x = items[i];

        if(itemSet.find(x) == itemSet.end())continue;

        itemSet.insert(x);

    }

}

int main()
{

}
