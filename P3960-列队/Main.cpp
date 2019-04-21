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

#include <ctime>

using namespace std;

typedef long long ll;

template <typename T>
inline void read(T &num)
{
    num = 0;
    ll w = 1;
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

const ll N = 3e5 + 10;

ll n, m, q;
ll rt[N];
ll ch[N << 5][2];
ll l[N << 5], r[N << 5];
ll sze[N << 5], val[N << 5];
ll tot;
ll a, b;
ll x, y, z, xa, ya, za;

#define lc(x) ch[x][0]
#define rc(x) ch[x][1]

inline ll newnode(ll x, ll y)
{
    l[++tot] = x;
    r[tot] = y;
    sze[tot] = y - x + 1;
    val[tot] = rand();
    return tot;
}

inline void pushup(ll x) { sze[x] = sze[lc(x)] + sze[rc(x)] - l[x] + r[x] + 1; }

inline ll merge(ll x, ll y)
{
    if (!x || !y)
        return x + y;
    if (val[x] < val[y])
    {
        rc(x) = merge(rc(x), y);
        pushup(x);
        return x;
    }
    lc(y) = merge(x, lc(y));
    pushup(y);
    return y;
}

inline void split_new(ll now, ll k)
{
    if (k >= r[now] - l[now] + 1)
        return;
    ll want = l[now] + k - 1;
    ll n = newnode(want + 1, r[now]);
    r[now] = want;
    rc(now) = merge(n, rc(now));
    pushup(now);
}

inline void split(ll now, ll k, ll &x, ll &y)
{
    if (!now)
        x = y = 0;
    else
    {
        if (sze[lc(now)] >= k)
            y = now, split(lc(now), k, x, lc(now));
        else
        {
            split_new(now, k - sze[lc(now)]);
            x = now, split(rc(now), k - sze[lc(now)] - (r[now] - l[now] + 1), rc(now), y);
        }
        pushup(now);
    }
}

int main()
{
    srand(time(0));
    read(n, m, q);
    for (ll i = 1; i <= n; i++)
        rt[i] = newnode((i - 1) * m + 1, i * m - 1);
    for (ll i = 1; i <= n; i++)
        rt[n + 1] = merge(rt[n + 1], newnode(i * m, i * m));
    while (q--)
    {
        read(a, b);
        if (b != m)
        {
            split(rt[a], b, x, y);
            split(x, b - 1, x, z);
            printf("%lld\n", l[z]);
            split(rt[n + 1], a, xa, ya);
            split(xa, a - 1, xa, za);
            rt[a] = merge(x, merge(y, za));
            rt[n + 1] = merge(xa, merge(ya, z));
        }
        else
        {
            split(rt[n + 1], a, x, y);
            split(x, a - 1, x, z);
            printf("%lld\n", l[z]);
            rt[n + 1] = merge(x, merge(y, z));
        }
    }
    return 0;
}