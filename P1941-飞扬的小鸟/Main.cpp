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

inline int read(int &num)
{
    num = 0;
    int w = 1;
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
    return num;
}

const int MAXN = 10010;
const int MAXM = 2010;

int n, m, k;
int x[MAXN], y[MAXN];
int l[MAXN], h[MAXN];
int dp[MAXN][MAXM];
bool have[MAXN];
int ans;

int main()
{
    read(n), read(m), read(k);
    for (int i = 1; i <= n; i++)
        read(x[i]), read(y[i]), l[i] = 1, h[i] = m;
    for (int i = 1; i <= k; i++)
    {
        int a, b, c;
        read(a), read(b), read(c);
        have[a] = 1;
        l[a] = b + 1;
        h[a] = c - 1;
    }
    memset(dp, 0x3f, sizeof(dp));
    for (int i = 1; i <= m; i++)
        dp[0][i] = 0;
    for (int i = 1; i <= n; i++)
    {
        for (int j = x[i] + 1; j <= x[i] + m; j++)
            dp[i][j] = min(dp[i - 1][j - x[i]] + 1, dp[i][j - x[i]] + 1);
        for (int j = m + 1; j <= m + x[i]; j++)
            dp[i][m] = min(dp[i][m], dp[i][j]);
        for (int j = 1; j <= m - y[i]; j++)
            dp[i][j] = min(dp[i][j], dp[i - 1][j + y[i]]);
        for (int j = 1; j < l[i]; j++)
            dp[i][j] = dp[0][0];
        for (int j = h[i] + 1; j <= m; j++)
            dp[i][j] = dp[0][0];
    }
    ans = dp[0][0];
    for (int i = 1; i <= m; i++)
        ans = min(ans, dp[n][i]);
    if (ans != dp[0][0])
        printf("1\n%d\n", ans);
    else
    {
        int i, j;
        for (i = n; i >= 1; i--)
        {
            for (j = 1; j <= m; j++)
                if (dp[i][j] < dp[0][0])
                    break;
            if (j <= m)
                break;
        }
        ans = 0;
        for (j = 1; j <= i; j++)
            if (have[j])
                ans++;
        printf("0\n%d\n", ans);
    }
    return 0;
}