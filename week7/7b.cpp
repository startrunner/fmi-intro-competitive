#include <cstdio>
#include <vector>
#include <array>
#include <string>
#include <stack>
#include <iostream>

using namespace std;

string expression;
vector<int> closesAt;

void match_brackets()
{
    closesAt.resize(expression.size(), 0);
    stack<pair<char, int>> bracketStack;

    for(int i=0;i<expression.size();i++)
    {
        if(expression[i]!='(' && expression[i]!=')')continue;

        if(expression[i]=='(')bracketStack.emplace('(', i);
        else if(!bracketStack.empty() && bracketStack.top().first=='(')
        {
            closesAt[bracketStack.top().second] = i;
            bracketStack.pop();
        }
        else bracketStack.emplace(')', i);
    }

    if(!bracketStack.empty())throw runtime_error("unbalanced braces");
}

int operate(char operator_, int x, int y)
{
    switch(operator_)
    {
        case '+': return x+y;
        case '-': return x-y;
        case '*': return x*y;
        case '/': return x/y;
        default: throw runtime_error("invalid operator: "s + operator_);
    }
}

int evaluate(int from, int to, int precedenceLevel)
{
    static const array<string, 2> PRECEDENCE_GROUPS = {"+-", "*/"};

    if(from==to)return expression[from]-'0';
    if(closesAt[from]==to)return evaluate(from+1, to-1, 0);

    const string &group = PRECEDENCE_GROUPS[precedenceLevel];
    vector<int> operatorIndices;
    for(int i=from;i<=to;i++)
    {
        if(closesAt[i]!=0)i=closesAt[i];
        if(group.find_first_of(expression[i])!=string::npos)
        {
            operatorIndices.push_back(i);
        }
    }

    if(operatorIndices.empty())return evaluate(from, to, precedenceLevel+1);

    int value = evaluate(from, operatorIndices[0]-1, precedenceLevel+1);
    for(int i=1;i<operatorIndices.size();i++)
    {
        int prevIndex = operatorIndices[i-1];
        int index = operatorIndices[i];
        value = operate(expression[prevIndex], value, evaluate(prevIndex+1, index-1, precedenceLevel+1));
    }
    value = operate(expression[operatorIndices.back()], value, evaluate(operatorIndices.back()+1, to, precedenceLevel+1));

    return value;
}

void solve()
{
    match_brackets();
    int value = evaluate(0, expression.size()-1, 0);
    printf("%d\n", value);
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin>>expression;
    solve();
    return 0;
}
/**
(5+5)/(2+3)*(7+6)
4*8-1*3
(5+5)/(2+3)

5+2*3
**/
