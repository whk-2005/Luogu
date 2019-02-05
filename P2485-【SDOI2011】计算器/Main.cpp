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

ll t, k;
ll y, z, p;
ll x;

ll fast_pow(ll a, ll b, ll p)
{
    if (b == 0)
        return 1 % p;
    if (b == 1)
        return a % p;
    ll tmp = fast_pow(a, b >> 1, p) % p;
    if (b & 1)
        return (tmp * tmp) % p * a % p;
    return (tmp * tmp) % p;
}

ll exgcd(ll a, ll b, ll &x, ll &y)
{
    if (b == 0)
    {
        x = 1;
        y = 0;
        return a;
    }
    ll tmp = exgcd(b, a % b, y, x);
    y -= a / b * x;
    return tmp;
}

ll mul(ll a, ll b, ll mod)
{
    a %= mod, b %= mod;
    return (a * b - (ll)(((double)a * b + 0.5) / mod) * mod + mod) % mod;
}

ll bsgs(ll a, ll b, ll p)
{
    int block = sqrt(p) + 0.5;
    int base = 1;
    map<ll, ll> maps;
    int tmp = 0;
    for (int i = 0; i <= block; i++)
    {
        maps[mul(base, b, p)] = i + 1;
        tmp = base;
        base = mul(base, a, p);
    }
    base = tmp;
    for(int i = 1; i <= block; i++)
    {
        if (maps[base])
            return i * block - (maps[base] - 1);
        base = mul(base, tmp, p);
    }
    return -1;
}

int main()
{
    scanf("%lld %lld", &t, &k);
    if (k == 1)
    {
        while (t--)
        {
            scanf("%lld %lld %lld", &y, &z, &p);
            y %= p;
            x = fast_pow(y, z, p);
            printf("%lld\n", x);
        }
    }
    if (k == 2)
    {
        while (t--)
        {
            scanf("%lld %lld %lld", &y, &z, &p);
            y %= p, z %= p;
            ll a, b;
            ll gcd = exgcd(y, p, a, b);
            if (z % gcd)
            {
                printf("Orz, I cannot find x!\n");
                continue;
            }
            ll tmp = p / gcd;
            while (a < 0)
                a += tmp;
            printf("%lld\n", ((a * z / gcd) % tmp + tmp) % tmp);
        }
    }
    if (k == 3)
    {
        while (t--)
        {
            scanf("%lld %lld %lld", &y, &z, &p);
            y %= p;
            if (y == 0 && z == 0)
            {
                printf("1\n");
                continue;
            }
            if (y == 0 && z != 0)
            {
                printf("Orz, I cannot find x!\n");
                continue;
            }
            ll tmp = bsgs(y, z, p);
            if (tmp != -1)
                printf("%lld\n", tmp);
            else
                printf("Orz, I cannot find x!\n");
        }
    }
    return 0;
}