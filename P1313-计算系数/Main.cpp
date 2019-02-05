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

const int MOD = 10007;

ll a, b, k, n, m;
ll g[2010][2010];

inline void init()
{
    g[1][1] = 1;
    for (int i = 2; i <= k + 1; i++)
        for (int j = 1; j <= i; j++)
            g[i][j] = (g[i - 1][j - 1] + g[i - 1][j]) % MOD;
}

ll mul(ll a, ll b)
{
    if (b == 0)
        return 1;
    if (b == 1)
        return a % MOD;
    ll tmp = mul(a, b / 2);
    if (b & 1)
        return ((tmp * tmp) % MOD) * a % MOD;
    return (tmp * tmp) % MOD;
}

int main()
{
    scanf("%lld %lld %lld %lld %lld", &a, &b, &k, &n, &m);
    init();
    printf("%lld", ((((g[k + 1][k - n + 1] % MOD) * mul(a, n)) % MOD) * mul(b, m)) % MOD);
    return 0;
}