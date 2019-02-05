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

ll a[20], b[20], s = 1, k;
ll x, y;
ll ans;

#define add(a, b) a = (a + b) % s

void exgcd(ll a, ll b, ll &x, ll &y)
{
    if (!b)
    {
        x = 1;
        y = 0;
        return;
    }
    exgcd(b, a % b, y, x);
    y -= (a / b) * x;
}

ll mul(ll a, ll b)
{
    ll r = 0;
    while (b)
    {
        if (b & 1)
            add(r, a);
        add(a, a);
        b >>= 1;
    }
    return r;
}

int main()
{
    scanf("%lld", &k);
    for (ll i = 1; i <= k; ++i)
        scanf("%lld", &a[i]);
    for (ll i = 1; i <= k; ++i)
        scanf("%lld", &b[i]), s *= b[i];
    for (ll i = 1; i <= k; ++i)
    {
        exgcd(s / b[i], b[i], x, y);
        x = (x % b[i] + b[i]) % b[i];
        add(ans, mul(s / b[i] * x, (a[i] % b[i] + b[i]) % b[i]));
    }
    printf("%lld\n", ans);
    return 0;
}