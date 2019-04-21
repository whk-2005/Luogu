#include <algorithm>
#include <bitset>
#include <cctype>
#include <cmath>
#include <cstdio>
#include <cstring>
#include <deque>
#include <iostream>
#include <list>
#include <map>
#include <queue>
#include <set>
#include <stack>
#include <string>
#include <vector>

using namespace std;

typedef long long ll;

template <typename T>
inline void read(T &num)
{
    num = 0;
    int w = 1;
    char ch = getchar();
    if (ch == '-')
        w = -1;
    while (ch < '0' || ch > '9')
    {
        ch = getchar();
        if (ch == '-')
            w = -1;
    }
    while ((ch >= '0' && ch <= '9'))
        num = num * 10 + ch - '0', ch = getchar();
    num = num * w;
}

template <typename T, typename... Args>
inline void read(T &num, Args &... args) { read(num), read(args...); }

const int N = 1e7 + 100;

int phi[N];
ll t, p;

inline int qpow(ll x, ll y, ll z)
{
    ll ret = 1;
    while (y)
    {
        if (y & 1)
            ret = (ret * x) % z;
        x = (x * x) % z;
        y >>= 1;
    }
    return ret;
}

inline ll solve(ll x)
{
    if (x == 1)
        return 0;
    return qpow(2, solve(phi[x]) + phi[x], x);
}

inline void init()
{
    phi[1] = 1;
    for (int i = 2; i <= N - 10; i++)
        if (!phi[i])
        {
            for (int j = i; j <= N - 10; j += i)
            {
                if (!phi[j])
                    phi[j] = j;
                phi[j] = phi[j] / i * (i - 1);
            }
        }
}

int main()
{
    init();
    read(t);
    while (t--)
    {
        read(p);
        printf("%lld\n", solve(p));
    }
}