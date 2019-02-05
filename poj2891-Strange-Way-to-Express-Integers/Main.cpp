// poj2891 Strange Way to Express Integers

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

ll n, a, b;
ll lcm, now, fail;
ll d, k, x, y;

ll exgcd(ll a, ll b, ll &x, ll &y)
{
    if (b == 0)
    {
        x = 1;
        y = 0;
        return a;
    }
    else
    {
        ll c = exgcd(b, a % b, y, x);
        y -= (a / b) * x;
        return c;
    }
}

int main()
{
    while (scanf("%lld", &n) == 1)
    {
        scanf("%lld%lld", &a, &b);
        lcm = a;
        now = b;
        fail = 0;
        for (ll i = 1; i < n; i++)
        {
            scanf("%lld%lld", &a, &b);
            b = (b - now % a + a) % a;
            d = exgcd(lcm, a, x, y);
            if (b % d == 0)
                k = x * (b / d) % a;
            else
                fail = 1;
            now += k * lcm;
            lcm = lcm / d * a;
            now = (now % lcm + lcm) % lcm;
        }
        if (fail)
            printf("-1\n");
        else
            printf("%lld\n", now);
    }
    return 0;
}