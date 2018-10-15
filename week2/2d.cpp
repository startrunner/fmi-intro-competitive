#include <cstdio>
#include <vector>
#include <climits>
#include <algorithm>
#include <iostream>
using namespace std;

int n;
vector<vector<int>> table;

void read()
{
    cin>>n;
    table.resize(n, vector<int>(n));

    string line;
    for(int i=0;i<n;i++)
    {
        cin>>line;
        for(int j=0;j<n;j++)table[i][j] = line[j] - '0';
    }
}

int value_or(const vector<vector<int>> &table, int i, int j, int orValue)
{
    if(i<0 || j<0 || i>=table.size() || j>=table[i].size())return orValue;
    return table[i][j];
}

void solve()
{
    vector<vector<int>> minValueAt(n, vector<int>(n, INT_MAX));

    minValueAt[0] = table[0];

    for(int i=1;i<n;i++)
    {
        for(int j=0;j<n;j++)
        {
            int minPrev = value_or(minValueAt, i-1, j, INT_MAX);
            minPrev = min(minPrev, value_or(minValueAt, i-1, j-1, INT_MAX));
            minPrev = min(minPrev, value_or(minValueAt, i-1, j+1, INT_MAX));

            minValueAt[i][j] = minPrev + table[i][j];
        }
    }

    int answer = INT_MAX;
    for(int x : minValueAt.back())answer = min(answer, x);

    printf("%d\n", answer);
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
12045
10110
10111
11011
10111

5
90999
90199
90909
99909
99909


5
19999
99899
99919
99991
99991
**/
