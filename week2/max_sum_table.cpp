#include <cstdio>
#include <vector>
#include <iostream>
using namespace std;

int n, m;
vector<vector<int>> input;

void read()
{
    cin>>n>>m;
    input.resize(n, vector<int>(m));
    for(auto &x : input)for(int &y : x)cin>>y;
}

void solve()
{
    vector<vector<int>> answer(n, vector<int>(m));

    answer[0][0] = input[0][0];
    for(int i=1;i<n;i++)
    {
        answer[0][i] = answer[0][i-1] + input[0][i];
        answer[i][0] = answer[i-1][0] + input[i][0];
    }

    for(int i=1;i<n;i++)
    {
        for(int j=1;j<n;j++)
        {
            answer[i][j] = max(answer[i][j-1], answer[i-1][j]) + input[i][j];
        }
    }

    printf("%d\n", (int)answer.back().back());
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    read();
    solve();
}
/**
3 3
1 2 3
4 5 6
7 8 9
**/
