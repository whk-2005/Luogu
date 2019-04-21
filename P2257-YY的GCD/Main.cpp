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

const int N = 10000010;

int t, n, m;
int p[N], mu[N], g[N];
ll sum[N];
ll ans;
bool vis[N];
int cnt;

inline void get_mu(int n)
{
    mu[1] = 1;
    for (int i = 2; i <= n; i++)
    {
        if (!vis[i])
            mu[i] = -1, p[++cnt] = i;
        for (int j = 1; j <= cnt && p[j] * i <= n; j++)
        {
            vis[i * p[j]] = 1;
            if (i % p[j] == 0)
                break;
            else
                mu[p[j] * i] = -mu[i];
        }
    }
    for (int j = 1; j <= cnt; j++)
        for (int i = 1; i * p[j] <= n; i++)
            g[i * p[j]] += mu[i];
    for (int i = 1; i <= n; i++)
        sum[i] = sum[i - 1] + (ll)g[i];
}

int main()
{
    read(t);
    get_mu(10000000);
    while (t--)
    {
        read(n, m);
        if (n > m)
            swap(n, m);
        ans = 0;
        for (int l = 1, r; l <= n; l = r + 1)
        {
            r = min(n / (n / l), m / (m / l));
            ans += (ll)(n / l) * (m / l) * (sum[r] - sum[l - 1]);
        }
        printf("%lld\n", ans);
    }
    return 0;
}