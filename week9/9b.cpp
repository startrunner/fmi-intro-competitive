#include <cstdio>
#include <iostream>
#include <vector>
using namespace std;

int n, k;

void read(){ cin>>n>>k; }

vector<uint8_t> callStack;
void go()
{
    if(callStack.size() == k)
    {
        for(uint8_t x : callStack)printf("%c", char('A'+x));
        putchar('\n');
        return;
    }

    for(
        uint8_t i = (callStack.empty()) ? 0 : callStack.back()+1;
        i<n;
        i++
    )
    {
        callStack.push_back(i);
        go();
        callStack.pop_back();
    }
}

void solve()
{
    callStack.reserve(k);
    go();
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    read();
    solve();
}
