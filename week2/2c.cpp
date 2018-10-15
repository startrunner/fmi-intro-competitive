#include <cstdio>
#include <map>
#include <vector>
#include <queue>
#include <climits>
#include <algorithm>
#include <iostream>
using namespace std;

int n, m;
vector<vector<int>> gr, revGr;

void read()
{
    cin>>n>>m;

    gr.resize(n+1);
    revGr.resize(n+1);

    for(int i=0;i<m;i++)
    {
        int x, y;
        cin>>x>>y;
        gr[x].push_back(y);
        revGr[y].push_back(x);
    }
}

void solve()
{
    vector<int> unresolvedDependencies(n+1, 0);
    vector<int> lenTo(n+1, INT_MAX);
    queue<int> wave;

    for(int i=1;i<=n;i++)
    {
        if(gr[i].empty())wave.push(i);
        unresolvedDependencies[i] = gr[i].size();
    }

    int maxValue = INT_MIN;

    while(!wave.empty())
    {
        int x = wave.front();
        //printf("solving for x = %d\n", x);
        wave.pop();

        int value = INT_MIN;
        if(!gr[x].empty())
        {
            for(int dependency : gr[x])
            {
                //printf("%d ", dependency);
                value = max(value, lenTo[dependency]);
            }
            value++;
        }
        else value = 0;
        //printf("value = %d\n", value);
        lenTo[x] = value;

        maxValue = max(maxValue, value);

        for(int dependent : revGr[x])
        {
            if(--unresolvedDependencies[dependent] == 0)
            {
                wave.push(dependent);
            }
        }
    }

    //for(int x : lenTo)printf("%d ", x);
    //putchar('\n');
    printf("%d\n", maxValue);
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    read();
    solve();
}
/**
5 5
1 2
2 3
3 4
3 5
1 5
**/
