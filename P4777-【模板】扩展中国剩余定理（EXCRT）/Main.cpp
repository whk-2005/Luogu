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

const int maxn = 100010;
int n;
ll a[maxn], b[maxn];

ll mul(ll a, ll b, ll mod)
{
    ll res = 0;
    while (b)
    {
        if (b & 1)
            res = (res + a) % mod;
        a = (a + a) % mod;
        b >>= 1;
    }
    return res;
}

ll exgcd(ll a, ll b, ll &x, ll &y)
{
    if (b == 0)
    {
        x = 1;
        y = 0;
        return a;
    }
    ll gcd = exgcd(b, a % b, y, x);
    y -= (a / b) * x;
    return gcd;
}

ll excrt()
{
    ll x, y, k;
    ll m = b[1], ans = a[1];
    for (int i = 2; i <= n; i++)
    {
        ll at = m, bt = b[i], c = (a[i] - ans % bt + bt) % bt;
        ll gcd = exgcd(at, bt, x, y);
        ll tmp = bt / gcd;
        if (c % gcd != 0)
            return -1;

        x = mul(x, c / gcd, tmp);
        ans += x * m;
        m *= tmp; 
        ans = (ans % m + m) % m;
    }
    return (ans % m + m) % m;
}

int main()
{
    scanf("%d", &n);
    for (int i = 1; i <= n; ++i)
        scanf("%lld%lld", &b[i], &a[i]);
    printf("%lld", excrt());
    return 0;
}