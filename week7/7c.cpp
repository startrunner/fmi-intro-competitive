#include <iostream>
#include <vector>
#include <cstdio>
using namespace std;

int n, m;
vector<vector<int>> gr;
vector<vector<bool>> matrix;

void read()
{
    cin>>n>>m;
    gr.resize(n+1, {});
    matrix.resize(n+1, vector<bool>(n+1, false));
    for(int i=0;i<m;i++)
    {
        int x, y;
        cin>>x>>y;
        gr[x].push_back(y);
        gr[y].push_back(x);
        matrix[x][y]=true;
        matrix[y][x]=true;
    }
}

int answer = 0;

int candidateCount = 0;
vector<bool> currentCandidate;

vector<bool> used;
int usedCount = 0;

int first;

void go(int current)
{
    if(usedCount+1 == candidateCount)
    {
        if(matrix[current][first])answer++;
        return;
    }

    used[current] = true;
    usedCount++;

    for(int x : gr[current])
    {
        if(!currentCandidate[x])continue;
        if(used[x])continue;
        go(x);
    }

    used[current] = false;
    usedCount--;
}

void solve()
{
    currentCandidate.resize(n+1);
    used.resize(n+1, false);

    unsigned mask = 1;
    for(int i=0;mask < (1<<n);i++, mask++)
    {
        first = -1;
        candidateCount = 0;
        for(unsigned j=0;j<n;j++)
        {
            unsigned jMask = (1u<<j);
            bool  value = mask&jMask;
            currentCandidate[j+1]=value;
        }
        for(int j=1;j<=n;j++)
        {
            if(currentCandidate[j])
            {
                if(first == -1)first = j;
                candidateCount++;
            }
        }

        if(candidateCount>2)go(first);
    }
    printf("%d\n", answer/2);
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    read();
    solve();
}
/**
3 2
1 2
2 3

4 5
1 2
2 3
3 4
4 1
1 3
**/
