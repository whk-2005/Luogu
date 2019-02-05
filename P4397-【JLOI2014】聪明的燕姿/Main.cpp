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

const int N = 100000;

ll s;
ll p[N + 10], pnum;
ll a[(N + 10) << 2], cnt;
bool isPrime[N + 10];

inline void get_prime()
{
    memset(isPrime, 0, sizeof(isPrime));
    for (ll i = 2; i <= N; i++)
    {
        if (!isPrime[i])
            p[++pnum] = i;
        for (ll j = 1; j <= pnum && p[j] * i <= N; j++)
        {
            isPrime[p[j] * i] = 1;
            if (i % p[j] == 0)
                break;
        }
    }
}

inline bool is_prime(ll x)
{
    if (x == 1)
        return 0;
    if (x <= N)
        return !isPrime[x];
    for (int i = 1; p[i] * p[i] <= x; i++)
        if (x % p[i] == 0)
            return 0;
    return 1;
}

void dfs(ll now, ll x, ll y)
{
    if (now == 1)
    {
        a[++cnt] = y;
        return;
    }
    if (now - 1 >= p[x] && is_prime(now - 1))
        a[++cnt] = y * (now - 1);
    ll tmp1, tmp2;
    for (ll i = x; p[i] * p[i] <= now; i++)
    {
        tmp1 = p[i];
        tmp2 = p[i] + 1;
        for (; tmp2 <= now; tmp1 *= p[i], tmp2 += tmp1)
            if (now % tmp2 == 0)
                dfs(now / tmp2, i + 1, y * tmp1);
    }
}

int main()
{
    get_prime();
    while (scanf("%lld", &s) == 1)
    {
        memset(a, 0, sizeof(a));
        cnt = 0;
        dfs(s, 1, 1);
        printf("%lld\n", cnt);
        sort(a + 1, a + cnt + 1);
        for (int i = 1; i < cnt; i++)
            printf("%lld ", a[i]);
        if (cnt)
            printf("%lld\n", a[cnt]);
    }
    return 0;
}