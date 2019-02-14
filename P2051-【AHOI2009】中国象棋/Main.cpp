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

inline void read(ll &num)
{
    num = 0;
    ll w = 1;
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

const ll MAXN = 110;
const ll MOD = 9999973;

ll n, m;
ll dp[MAXN][MAXN][MAXN];
ll ans;

inline ll C(ll x) { return x * (x - 1) / 2; }

int main()
{
    read(n), read(m);
    dp[0][0][0] = 1;
    for (ll i = 1; i <= n; i++)
        for (ll j = 0; j <= m; j++)
            for (ll k = 0; k + j <= m; k++)
            {
                dp[i][j][k] = (dp[i][j][k] + dp[i - 1][j][k]) % MOD;
                if (m - j - k >= 1)
                    dp[i][j + 1][k] = (dp[i][j + 1][k] + dp[i - 1][j][k] * (m - j - k)) % MOD;
                if (m - j - k >= 1 && j >= 1)
                    dp[i][j][k + 1] = (dp[i][j][k + 1] + dp[i - 1][j][k] * (m - j - k) * j) % MOD;
                if (m - j - k >= 2)
                    dp[i][j + 2][k] = (dp[i][j + 2][k] + dp[i - 1][j][k] * C(m - j - k)) % MOD;
                if (j >= 1)
                    dp[i][j - 1][k + 1] = (dp[i][j - 1][k + 1] + dp[i - 1][j][k] * j) % MOD;
                if (j >= 2)
                    dp[i][j - 2][k + 2] = (dp[i][j - 2][k + 2] + dp[i - 1][j][k] * C(j)) % MOD;
            }
    // for (ll i = 0; i <= m; i++)
    // {
    //     for (ll j = 0; i + j <= m; j++)
    //         printf("%d ", dp[n][i][j]);
    //     printf("\n");
    // }
    for (ll i = 0; i <= m; i++)
        for (ll j = 0; i + j <= m; j++)
            ans = (ans + dp[n][i][j]) % MOD;
    printf("%lld\n", ans);
    return 0;
}