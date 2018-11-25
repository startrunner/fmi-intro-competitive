#include <cstdio>
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int n, m, k;
vector<vector<bool>> isBlocked;
void read()
{
    cin>>n>>m;
    k = n*n - m;
    isBlocked.resize(n+1, vector<bool>(n+1, false));
    for(int i=0;i<m;i++)
    {
        int x, y;
        cin>>x>>y;
        isBlocked[x][y] = true;
    }
}

vector<pair<int, int>>coordsOf;
vector<vector<int>> idOf;

bool valid(pair<int, int> coords)
{
    return
        coords.first > 0 && coords.second > 0 &&
        coords.first <=n && coords.second <=n;
}

void calculate_jumps(vector<pair<int, int>> &v, int x, int y)
{
    v.clear();
    for(int o1 = 1; o1<4; o1++)
    {
        int o2 = 4-o1;
        for(int i : {-1, +1})
        {
            for(int j : {-1, +1})
            {
                pair<int, int> candidate{x + i*o1, y + j*o2};
                if(valid(candidate))v.push_back(candidate);
            }
        }
    }
}

vector<vector<int>> gr;

void solve()
{
    coordsOf.resize(k+1);
    idOf.resize(n+1, vector<int>(n+1, -1));

    for(int i=1, id=0;i<=n;i++)
    {
        for(int j=1;j<=n;j++)
        {
            if(isBlocked[i][j])continue;

            id++;
            coordsOf[id] = {i, j};
            idOf[i][j] = id;
            printf("id: %d\n", id);
        }
    }

    gr.resize(k+1);

    vector<pair<int, int>> jumps;
    for(int i=1; i<=n; i++)
    {
        for(int j=i%2; j<=n; j+=2)
        {
            int id = idOf[i][j];
            int id1 = idOf[i][(j+1)%n];
            if(id == -1 || id1 == -1)continue;
            calculate_jumps(jumps, i, j);
            for(auto x : jumps)
            {
                int xId = idOf[x.first][x.second];
                if(xId == -1)continue;
                printf("%d %d has id: %d\n", x.first, x.second, xId);
                gr[id].push_back(xId);
            }
            gr[0].push_back(id);
            gr[id1].push_back(k);
        }
    }

    for(int i=0;i<=k;i++)
    {
        printf("%d: ", i);
        for(int x : gr[i])printf("%d ", x);
        puts("");
    }
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
1 1
3 3
**/
