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

const int MAXN = 50050;
ll n, l;
ll sum[MAXN];
ll dp[MAXN];
ll val[MAXN];
ll g[MAXN];
ll q[MAXN], head, tail;

inline double clac(int x, int y) { return (double)(dp[y] + g[y] - dp[x] - g[x]) / (val[y] - val[x]); }

int main()
{
    read(n, l);
    for (int i = 1; i <= n; i++)
    {
        read(sum[i]);
        sum[i] += sum[i - 1];
        val[i] = sum[i] + i;
        g[i] = (val[i] + l + 1) * (val[i] + l + 1);
    }
    g[0] = (l + 1) * (l + 1);
    for (int i = 1; i <= n; i++)
    {
        while (head < tail && clac(q[head], q[head + 1]) <= val[i] * 2)
            head++;
        dp[i] = dp[q[head]] + (val[i] - val[q[head]] - l - 1) * (val[i] - val[q[head]] - l - 1);
        while (head < tail && clac(q[tail], i) < clac(q[tail - 1], q[tail]))
            tail--;
        q[++tail] = i;
    }
    printf("%lld\n", dp[n]);
    return 0;
}