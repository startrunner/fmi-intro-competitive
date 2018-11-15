#include <cstdio>
#include <vector>
#include <iostream>
#include <map>
using namespace std;

int n, q;
vector<vector<int>> tree;
vector<pair<int, int>> questions;
vector<vector<int>> questionsAbout;
void read()
{
    cin>>n;
    tree.resize(n+1, {});

    for(int i=1;i<n;i++)
    {
        int parent, child;
        cin>>parent>>child;
        tree[parent].push_back(child);
    }

    cin>>q;
    questionsAbout.resize(n+1, {});
    questions.resize(q);
    for(int i=0;i<q;i++)
    {
        int edge, jumps;
        cin>>edge>>jumps;
        questions[i] = {edge, jumps};
        questionsAbout[edge].push_back(jumps);
    }
}

void solve()
{
    map<pair<int, int>, int> answers;

    vector<pair<int, int>> callStack;
    callStack.emplace_back(1, 0);

    while(!callStack.empty())
    {
        pair<int, int> &top = callStack.back();
        if(top.second==0)
        {
            /*
            printf("%d: ", top.first);
            for(int i=0;i<callStack.size();i++)
            {
                printf("%d ", callStack[i].first);
                if(i+1<callStack.size())printf("-> ");
            }
            puts("");
            printf("questions: ");
            for(int len : questionsAbout[top.first])printf("%d ", len);
            puts("");

            puts("");*/

            for(int len : questionsAbout[top.first])
            {
                answers[{top.first, len}] = (callStack.end()-len-1)->first;
            }

        }

        int i = top.second++;
        if(i<tree[top.first].size())
        {
            callStack.emplace_back(tree[top.first][i], 0);
        }
        else callStack.pop_back();
    }

    for(const auto &q : questions)printf("%d\n", answers[q]);
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    read();
    solve();

    return 0;
}

/**
10
1 9
1 2
9 10
2 3
3 4
4 5
4 6
5 8
6 7
5
10 2
1 0
3 1
6 3
8 4
**/
