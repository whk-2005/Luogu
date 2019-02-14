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
ll prime[N], mu[N], sum[N];
ll cnt;

inline void get_mu(ll n)
{
    mu[1] = 1;
    for (ll i = 2; i <= n; i++)
    {
        if (!vis[i])
            mu[i] = -1, prime[++cnt] = i;
        for (ll j = 1; j <= cnt && i * prime[j] <= n; j++)
        {
            vis[i * prime[j]] = 1;
            if (i % prime[j] == 0)
                break;
            mu[i * prime[j]] = -mu[i];
        }
    }
    for (int i = 1; i <= n; i++)
        sum[i] = sum[i - 1] + mu[i];
}

int main()
{
    ll t;
    read(t);
    get_mu(50000);
    while (t--)
    {
        ll a, b, c, maxx, ans = 0;
        read(a, b, c);
        maxx = min(a, b);
        for (int l = 1, r; l <= maxx; l = r + 1)
        {
            r = min(a / (a / l), b / (b / l));
            ans += (a / (l * c)) * (b / (l * c )) * (sum[r] - sum[l - 1]);
        }
        printf("%lld\n", ans);
    }
    return 0;
}