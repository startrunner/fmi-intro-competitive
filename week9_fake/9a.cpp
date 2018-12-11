#include <cstdio>
#include <iostream>
#include <vector>
using namespace std;

int n;
vector<int> ballCounts;

void read()
{
    cin>>n;
    ballCounts.resize(n);
    for(int &x : ballCounts)cin>>x;
}

string callStack;
void go(int boxI)
{
    if(boxI == n)
    {
        printf("%s\n", callStack.c_str());
        return;
    }

    for(int i=0;i<ballCounts[boxI];i++)
    {
        char letter = 'A' + i;
        callStack.push_back(letter);
        go(boxI + 1);
        callStack.pop_back();
    }
}

void solve()
{
    callStack.reserve(n);
    go(0);
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    read();
    solve();
}
