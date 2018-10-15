#include <cstdio>
#include <vector>
#include <climits>
#include <algorithm>
#include <iostream>
using namespace std;

int n;

void solve()
{
    vector<int> minOps(n+1, INT_MAX);

    minOps[1] = 0;

    for(int i=2;i<=n;i++)
    {
        int minPrev = minOps[i-1];
        if(i%3==0)minPrev = min(minPrev, minOps[i/3]);
        if(i%2==0)minPrev = min(minPrev, minOps[i/2]);
        minOps[i] = minPrev + 1;
    }

    printf("%d\n", minOps.back());
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin>>n;
    solve();
}
/**
5
4 10 0 12 2
**/
