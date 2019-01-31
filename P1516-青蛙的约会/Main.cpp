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

ll ans, xx, yy;

ll exgcd(ll a, ll b, ll &xx, ll &yy)
{
    if (b == 0)
    {
        xx = 1;
        yy = 0;
        return a;
    }
    ans = exgcd(b, a % b, xx, yy);
    ll t = xx;
    xx = yy;
    yy = t - a / b * yy;
    return ans;
}

ll x, y, m, n, l;

int main()
{
    scanf("%lld%lld%lld%lld%lld", &x, &y, &m, &n, &l);
    ll a = x - y, b = n - m;
    if (b < 0)
    {
        a = -a;
        b = -b;
    }
    exgcd(b, l, xx, yy);
    if (a % ans != 0)
        printf("Impossible\n");
    else
        printf("%lld\n", ((xx * (a / ans)) % (l / ans) + (l / ans)) % (l / ans));
    return 0;
}