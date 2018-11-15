#include <cstdio>
#include <vector>
#include <cstdlib>
#include <iostream>
using namespace std;

vector<int> a, b;

void read()
{
    string s;

    cin>>s;
    a.reserve(s.size());
    for(char c : s)a.push_back(c-'0');

    cin>>s;
    b.reserve(s.size());
    for(char c : s)b.push_back(c-'0');
}

void solve()
{
    vector<uint8_t> result;
    result.reserve(1000000);

    for(int bI = b.size()-1, startRI=0; bI>=0; bI--, startRI++)
    {
        uint8_t overflow = 0;
        const uint8_t x = b[bI];
        for(int aI = a.size()-1, rI=startRI; aI>=0; aI--, rI++)
        {
            const uint8_t y = a[aI];
            const uint8_t digit = ((int)x*y+overflow)%10;
            overflow = (x*y+overflow)/10;
            if(rI+1>=result.size())result.resize(rI+2, 0);
            result[rI]+=digit;
            result[rI+1]+=result[rI]/10;
            result[rI]%=10;
            //printf("%d %d -> %d  (%d)\n", x, y, digit, overflow);
        }
    }


    while(result.size()>1 && result.back()==0)result.pop_back();
    for(int i=0, j=result.size()-1; i<j; i++, j--)swap(result[i], result[j]);

    for(int x : result)printf("%d", (int)x);
    printf("\n");
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    read();
    solve();

    return EXIT_SUCCESS;
}
