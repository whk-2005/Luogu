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

const int N = 50010;

bool vis[N];
int prim[N], cnt;
int mu[N], sum[N];
int t, n, m;
ll g[N];
ll ans;

inline void get_mu(int n)
{
    mu[1] = 1;
    for (int i = 2; i <= n; i++)
    {
        if (!vis[i])
            prim[++cnt] = i, mu[i] = -1;
        for (int j = 1; j <= cnt && prim[j] * i <= n; j++)
        {
            vis[prim[j] * i] = 1;
            if (i % prim[j] == 0)
                break;
            else
                mu[i * prim[j]] = -mu[i];
        }
    }
    for (int i = 1; i <= n; i++)
        sum[i] = sum[i - 1] + mu[i];
    for (int i = 1; i <= n; i++)
    {
        ans = 0;
        for (int l = 1, r; l <= i; l = r + 1)
        {
            r = (i / (i / l));
            ans += 1ll * (r - l + 1) * 1ll * (i / l);
        }
        g[i] = ans;
    }
}

int main()
{
    get_mu(50000);
    read(t);
    while (t--)
    {
        read(n, m);
        ans = 0;
        for (int l = 1, r; l <= min(n, m); l = r + 1)
        {
            r = min(n / (n / l), m / (m / l));
            ans += 1ll * (sum[r] - sum[l - 1]) * g[n / l] * g[m / l];
        }
        printf("%lld\n", ans);
    }
    return 0;
}