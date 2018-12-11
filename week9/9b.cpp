#include <vector>
#include <cstdio>
#include <cstdlib>
#include <iostream>
using namespace std;

struct node
{
    node(const node *left, const node *right):
        sum(left->sum + right->sum),
        left(left),
        right(right)
        {}

    node(int sum):
        sum(sum){}

    node(const vector<int> &values, int from, int to)
    {
        if(from==to)
        {
            sum = values[from];
            return;
        }

        int middle = (from+to)/2;
        left = new node(values, from, middle);
        right = new node(values, middle+1, to);
        sum = left->sum + right->sum;
    }

    int sum = 0;
    const node *left = nullptr, *right = nullptr;

    int get_value(int index, int from, int to)const
    {
        if(from == to)return sum;

        int middle = (from+to)/2;

        if(index <= middle)return left->get_value(index, from, middle);
        else return right->get_value(index, middle+1, to);
    }

    const node* set_value(int index, int value, int from, int to)const
    {
        if(index < from || index > to)return this; //this node is unchanged.
        if(from == to)return new node(value);

        int middle = (from+to)/2;

        return new node(
            left->set_value(index, value, from, middle),
            right->set_value(index, value, middle+1, to)
        );
    }
};

int n, q;
vector<int> initialValues;
vector<const node*> versions;

void read()
{
    cin>>n;

    initialValues.resize(n);
    for(int &x : initialValues)cin>>x;

    versions.resize(2, nullptr);
    versions[1] = new node(initialValues, 0, n-1);
}

void solve()
{
    cin>>q;
    for(int i=0;i<q;i++)
    {
        string command;
        cin>>command;

        if(command == "create")
        {
            int basedOn, index, value;
            cin>>basedOn>>index>>value;
            versions.push_back(versions[basedOn]->set_value(index-1, value, 0, n-1));
        }
        else if(command == "get")
        {
            int version, index;
            cin>>version>>index;
            printf("%d\n", versions[version]->get_value(index-1, 0, n-1));
        }
        else throw runtime_error("invalid command: " + command);
    }
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    read();
    solve();
    return EXIT_SUCCESS;
}

/**
6
1 2 3 4 5 6
11
create 1 6 10
create 2 5 8
create 1 5 30
get 1 6
get 1 5
get 2 6
get 2 5
get 3 6
get 3 5
get 4 6
get 4 5
**/
