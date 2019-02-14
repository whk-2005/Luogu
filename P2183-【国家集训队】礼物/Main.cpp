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

ll p, n, m;
ll w[10];
ll sum, ans = 1;

inline ll qpow(ll a, ll b, ll mod)
{
    ll ans = 1;
    while (b)
    {
        if (b & 1)
            ans = (ans * a) % mod;
        a = (a * a) % mod;
        b >>= 1;
    }
    return ans;
}

inline ll exgcd(ll a, ll b, ll &x, ll &y)
{
    if (b == 0)
    {
        x = 1;
        y = 0;
        return a;
    }
    ll d = exgcd(b, a % b, y, x);
    y -= a / b * x;
    return d;
}

inline ll inv(ll k, ll p)
{
    if (!k)
        return 0;
    ll x, y, d;
    d = exgcd(k, p, x, y);
    x = (x % p + p) % p;
    if (!x)
        x += p;
    return x;
}

inline ll mul(ll n, ll p1, ll p2)
{
    if (!n)
        return 1;
    ll ans = 1;
    for (ll i = 2; i <= p2; i++)
        if (i % p1)
            ans = (ans * i) % p2;
    // printf("1\n");
    ans = qpow(ans, n / p2, p2);
    ll tmp = n % p2;
    for (ll i = 2; i <= tmp; i++)
        if (i % p1)
            ans = (ans * i) % p2;
    return ans * mul(n / p1, p1, p2) % p2;
}

inline ll C(ll n, ll m, ll mod, ll p1, ll p2)
{
    if (m > n)
        return 0;
    ll a = mul(n, p1, p2);
    ll b = mul(m, p1, p2);
    ll c = mul(n - m, p1, p2);
    ll k = 0;
    for (ll i = n; i; i /= p1)
        k += i / p1;
    for (ll i = m; i; i /= p1)
        k -= i / p1;
    for (ll i = n - m; i; i /= p1)
        k -= i / p1;
    ll ans = a * inv(b, p2) % p2 * inv(c, p2) % p2 * qpow(p1, k, p2) % p2;
    return ans * (mod / p2) % mod * inv(mod / p2, p2) % mod;
}

int main()
{
    read(p, n, m);
    for (ll i = 1; i <= m; i++)
        read(w[i]), sum += w[i];
    if (sum > n)
        return printf("Impossible\n"), 0;
    for (ll i = 1; i <= m; i++)
    {
        n -= w[i - 1];
        ll now = 0, x = p;
        for (ll j = 2; j <= sqrt(p); j++)
            if (!(x % j))
            {
                ll p1 = 1;
                while (!(x % j))
                    p1 *= j, x /= j;
                now = (now + C(n, w[i], p, j, p1)) % p;
            }
        if (x > 1)
            now = (now + C(n, w[i], p, x, x)) % p;
        ans = ans * now % p;
    }
    printf("%lld\n", ans);
    return 0;
}