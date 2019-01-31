#include <algorithm>
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

ll t;
ll n, m, p;

ll quick_pow(ll n, ll m)
{
    ll s = 1;
    for (; m; m >>= 1)
    {
        if (m & 1)
            s = s * n % p;
        n = n * n % p;
    }
    return s;
}

ll C(ll n, ll m)
{
    if (m > n)
        return 0;
    ll a = 1, b = 1;
    for (int i = n - m + 1; i <= n; i++)
        a = a * i % p;
    for (int i = 2; i <= m; i++)
        b = b * i % p;
    return a * quick_pow(b, p - 2) % p;
}

ll Lucas(ll n, ll m)
{
    if (!m)
        return 1;
    return (C(n % p, m % p) * Lucas(n / p, m / p)) % p;
}

int main()
{
    scanf("%lld", &t);
    while (t--)
    {
        scanf("%lld%lld%lld", &n, &m, &p);
        printf("%lld\n", Lucas(n + m, m));
    }
    return 0;
}
