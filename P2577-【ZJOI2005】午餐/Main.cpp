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

inline void read(int &num)
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
}

const int MAXN = 210;

int n;
struct node
{
    int a, b;
    bool operator<(node x) const
    {
        return b > x.b;
    }
} s[MAXN];
int sum[MAXN];
int dp[MAXN][MAXN * MAXN];
int ans;

int main()
{
    read(n);
    for (int i = 1; i <= n; i++)
        read(s[i].a), read(s[i].b);
    sort(s + 1, s + n + 1);
    for (int i = 1; i <= n; i++)
        sum[i] = sum[i - 1] + s[i].a;
    memset(dp, 0x7f, sizeof(dp));
    dp[0][0] = 0;
    for (int i = 1; i <= n; i++)
        for (int j = 0; j <= sum[i]; j++)
        {
            if (j >= s[i].a)
                dp[i][j] = min(dp[i][j], max(dp[i - 1][j - s[i].a], j + s[i].b));
            dp[i][j] = min(dp[i][j], max(dp[i - 1][j], sum[i] - j + s[i].b));
        }
    ans = 0x7fffffff;
    for (int i = 0; i <= sum[n]; i++)
        ans = min(ans, dp[n][i]);
    printf("%d\n", ans);
    return 0;
}