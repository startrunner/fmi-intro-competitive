#include <cstdio>
#include <vector>
#include <climits>
#include <algorithm>
#include <iostream>
using namespace std;

int n;
vector<int> coordinates;

void read()
{
    cin>>n;
    coordinates.resize(n);
    for(int &x : coordinates)cin>>x;
}

void solve()
{
    sort(coordinates.begin(), coordinates.end());

    if(n<3)
    {
        printf("%d\n", coordinates.back() - coordinates.front());
        return;
    }

    vector<int> minConnectedToPrevious(n, INT_MAX);
    vector<int> minNotConnectedToPrevious(n, INT_MAX);

    minNotConnectedToPrevious[0] = 0;

    for(int i=1;i<n;i++)
    {
        minConnectedToPrevious[i] = min(
            minConnectedToPrevious[i-1],
            minNotConnectedToPrevious[i-1]
        ) + coordinates[i] - coordinates[i-1];

        minNotConnectedToPrevious[i] = minConnectedToPrevious[i-1];

        //printf("%d: %d %d\n", i, minConnectedToPrevious[i], minNotConnectedToPrevious[i]);
    }

    printf("%d\n", minConnectedToPrevious.back());
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    read();
    solve();
}
/**
5
4 10 0 12 2
**/
