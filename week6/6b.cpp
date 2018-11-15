#include <cstdio>
#include <vector>
#include <iostream>
#include <queue>
#include <map>
#include <set>
#include <bitset>
using namespace std;


int n, m;
vector<vector<int>> gr;

void read()
{
    cin>>n>>m;
    gr.resize(n+1, {});

    for(int i=1;i<=n;i++)
    {
        gr[0].push_back(i);
    }

    for(int i=1;i<=m;i++)
    {
        int x, y;
        cin>>x>>y;
        if(x==y)continue;
        gr[x].push_back(y);
    }
}

namespace sol1
{

    vector<bool> used;
    vector<int> bit;
    vector<bool> visited;
    vector<vector<int>> bitOf;

    void go(int current)
    {
        visited[current] = true;
        used[current] = true;

        for(int next : gr[current])
        {
            if(!used[next])
            {
                go(next);
            }
            else
            {
                //printf("biting %d from %d\n", next, current);
                bit.push_back(next);
            }
            if(!bit.empty())
            {
                bitOf[current].push_back(bit.back());
                bitOf[bit.back()].push_back(current);
            }
        }

        if(!bit.empty() && bit.back()==current)bit.pop_back();
    }

    void solve()
    {
        bit.reserve(n+1);
        bitOf.resize(n+1);
        used.resize(n+1);
        visited.resize(n+1);
        for(int i=1;i<=n;i++)
        {
            if(!visited[i])go(i);
        }

        vector<bool> inComponent(n+1, false);
        queue<int> bfs;
        int answer = 0;

        for(int i=1;i<=n;i++)
        {
            if(!inComponent[i])
            {
                answer++;
                inComponent[i]=true;
                bfs.push(i);
                while(!bfs.empty())
                {
                    int x = bfs.front();
                    bfs.pop();
                    for(int y : bitOf[x])
                    {
                        if(!inComponent[y])
                        {
                            inComponent[y]=true;
                            bfs.push(y);
                        }
                    }
                }
            }
        }

        printf("%d\n", answer);
    }
}

namespace sol2
{
    vector<bool> everUsed, nodeUsed;
    vector<int> callStack;
    vector<vector<bool>> componentTable;
    vector<vector<int>> componentGr;
    //t compomentCount = 0;

    void go_stack(int from)
    {
        static vector<pair<int, int>> st;
        st.reserve(n+10);
        st.emplace_back(from, 0);

        while(!st.empty())
        {
            auto &top = st.back();
            int i = top.second++;
            if(i==0)
            {
                nodeUsed[top.first] = true;
                everUsed[top.first] = true;
            }

            if(i < gr[top.first].size())
            {
                int to = gr[top.first][i];
                if(nodeUsed[to])
                {
                    for(
                        auto it = st.rbegin();
                        it!=st.rend() && it->first!=to;
                        it++
                    )
                    {
                        if(componentTable[it->first][to])continue;

                        componentTable[it->first][to]=true;
                        componentTable[to][it->first]=true;
                        componentGr[it->first].push_back(to);
                        componentGr[to].push_back(it->first);
                    }
                }
                else st.emplace_back(to, 0);
            }
            else
            {
                nodeUsed[top.first]=false;
                st.pop_back();
            }
        }
    }

    void solve()
    {
        nodeUsed.resize(n+1, false);
        everUsed.resize(n+1, false);
        componentTable.resize(n+1, vector<bool>(n+1, false));
        componentGr.resize(n+1, {});

        for(int i=1;i<=n;i++)
        {
            if(!everUsed[i])go_stack(i);
        }

        vector<int> componentOf(n+1, 0);
        queue<int> bfs;

        for(int i=1;i<=n;i++)
        {
            if(componentOf[i]==0)
            {
                componentOf[i]=i;
                bfs.push(i);

                while(!bfs.empty())
                {
                    for(int y : componentGr[bfs.front()])
                    {
                        if(componentOf[y]==0)
                        {
                            componentOf[y]=i;
                            bfs.push(y);
                        }
                    }
                    bfs.pop();
                }
            }
        }

        printf("%d\n", (int)set<int>{componentOf.begin()+1, componentOf.end()}.size());
    }
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    read();

    if(m>1000)sol1::solve();
    else sol2::solve();

    return 0;
}

/**
8   9
1 2
2 3
3 1
2 4
4 5
5 6
6 4
7 8
8    7


10 11
1 2
2 3
3 4
4 5
5 6
6 7
7 8
8 9
9 10
10 1
5   10

5 7
1 2
2 3
3 5
5 4
3 4
4 2
5   1

3 4
1 2
2 3
3 2
2   1

10  11
1 2
2 3
3 4
4 5
5 6
6 1
4 7
7 8
8 9
9 10
10 4
**/
