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

const int MOD = 999911658;

ll n, g;
ll f[50010];
ll a[10], b[10] = {0, 2, 3, 4679, 35617};
ll ans;

inline ll qpow(ll a, ll b, ll p)
{
    ll ans = 1;
    while (b)
    {
        if (b & 1)
            ans = (ans * a) % p;
        a = (a * a) % p;
        b >>= 1;
    }
    return ans;
}

inline ll C(ll n, ll m, ll p)
{
    if (n < m)
        return 0;
    return ((f[n] * qpow(f[m], p - 2, p)) % p * qpow(f[n - m], p - 2, p)) % p;
}

inline ll lucas(ll n, ll m, ll p)
{
    if (n < m)
        return 0;
    if (!n)
        return 1;
    return (lucas(n / p, m / p, p) * C(n % p, m % p, p)) % p;
}

int main()
{
    read(n, g);
    if (g % (MOD + 1) == 0)
        return printf("0\n"), 0;
    for (ll k = 1; k <= 4; k++)
    {
        f[0] = 1;
        for (ll i = 1; i <= b[k]; i++)
            f[i] = (f[i - 1] * i) % b[k];
        for (ll i = 1; i * i <= n; i++)
            if (n % i == 0)
            {
                a[k] = (a[k] + lucas(n, i, b[k])) % b[k];
                if (i * i != n)
                    a[k] = (a[k] + lucas(n, n / i, b[k])) % b[k];
            }
    }
    for (ll i = 1; i <= 4; i++)
        ans = (ans + a[i] * (MOD / b[i]) % MOD * qpow(MOD / b[i], b[i] - 2, b[i])) % MOD;
    printf("%lld\n", qpow(g, ans, MOD + 1));
    return 0;
}