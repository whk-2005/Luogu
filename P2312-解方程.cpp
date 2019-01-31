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

const int p = 1e9 + 7;
ll n, m;
ll ans, cnt, sum;
ll a[110], key[1000010];

inline void read(ll &num)
{
    ll sum = 0, fg = 1;
    char c = getchar();
    while (!isdigit(c))
    {
        if (c == '-')
            fg = -1;
        c = getchar();
    }
    while (isdigit(c))
    {
        sum = ((sum * 10) + c - '0') % p;
        c = getchar();
    }
    num = sum * fg;
}

inline bool calc(ll x)
{
    sum = 0;
    for (ll i = n; i >= 1; i--)
        sum = ((a[i] + sum) * x) % p;
    sum = (sum + a[0]) % p;
    return (sum == 0);
}

int main()
{
    read(n);
    read(m);
    for (ll i = 0; i <= n; i++)
        read(a[i]);
    for (ll i = 1; i <= m; i++)
        if (calc(i))
        {
            ans++;
            key[++cnt] = i;
        }
    printf("%lld\n", ans);
    for (ll i = 1; i <= cnt; i++)
        printf("%lld\n", key[i]);
    return 0;
}