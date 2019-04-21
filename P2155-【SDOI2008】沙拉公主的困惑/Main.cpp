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

ll a[N];
int inv[N];
int t, n, m, r;
int ans[N];
bool vis[N];
int prime[N], cnt;

void init(ll n)
{
    vis[0] = vis[1] = 1;
    a[0] = a[1] = 1;
    inv[0] = inv[1] = 1;
    ans[0] = ans[1] = 1;
    for (int i = 2; i <= n; i++)
    {
        a[i] = (ll)(a[i - 1] * i) % r;
        inv[i] = (ll)(r - r / i) * inv[r % i] % r;
        if (!vis[i])
            prime[++cnt] = i;
        for (int j = 1; j <= cnt && i * prime[j] <= n; j++)
        {
            vis[i * prime[j]] = 1;
            if (i % prime[j] == 0)
                break;
        }
    }
    for (int i = 2; i <= n; i++)
    {
        ans[i] = ans[i - 1];
        if (!vis[i])
            ans[i] = (ll)ans[i] % r * (i - 1) % r * inv[i] % r;
    }
}

int main()
{
    read(t, r);
    init(10000000);
    while (t--)
    {
        read(n, m);
        printf("%lld\n", (ll)a[n] % r * ans[m] % r);
    }
    return 0;
}