#include <cstdio>
#include <string>
#include <vector>
#include <iostream>
using namespace std;

string s;

int calculate(char operand, int x, int y)
{
    switch(operand)
    {
    case '+': return x+y;
    case '-': return x-y;
    case '*': return x*y;
    }
}

void print_expression(const vector<vector<int>> &operandIndex, int from, int to)
{
    int length = to-from+1;
    int currentOperandIndex = operandIndex[from][to];
    if(length<3)
    {
        for(int i=from; i<=to; i++)putchar(s[i]);
    }
    else
    {
        putchar('(');
        print_expression(operandIndex, from, currentOperandIndex-1);
        putchar(s[currentOperandIndex]);
        print_expression(operandIndex, currentOperandIndex+1, to);
        putchar(')');
    }

}

void solve()
{
    vector<vector<int>> maxValue(s.size(), vector<int>(s.size(), 0));
    ///maxValue[from][to] == (maximum possible value of expression ranging in the substring S[from...to])
    ///from and to are odd numbers, i.e indices of digits.

    vector<vector<int>> operandIndex(s.size(), vector<int>(s.size(), 0));
    ///operandIndex[from][to] == index of top-level operand (that doesn't go in parentheses)
    ///...within the expression ranging in the substring S[from...to]

    for(int i=0; i<s.size(); i+=2)maxValue[i][i] = s[i]-'0';

    int answer = -1;

    for(int length = 3; length<=s.size(); length+=2)
    {
        for(int from=0; from<s.size(); from+=2)
        {
            int to = from + length-1;
            if(to>=s.size())break;

            int currentOperandIndex = -1;
            int currentMax = -1;
            for(int operandI = from+1; operandI<to; operandI+=2)
            {
                int x = maxValue[from][operandI-1];
                int y = maxValue[operandI+1][to];
                int currentValue = calculate(s[operandI], x, y);

                if(currentValue > currentMax)
                {
                    currentMax = currentValue;
                    currentOperandIndex = operandI;
                }
            }

            maxValue[from][to]=currentMax;
            operandIndex[from][to]=currentOperandIndex;
            answer = currentMax;
        }
    }

    print_expression(operandIndex, 0, s.size()-1);
    printf(" = %d\n", answer);
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin>>s;
    solve();
}

/**
3*5-1+2
**/
