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

const int MAXN = 3010;

int n, m, cnt;
int dp[MAXN][MAXN], val[MAXN], haed[MAXN];
struct Edge
{
    int to, w, next;
} e[MAXN * MAXN];
int t[MAXN];

void addedge(int u, int v, int w)
{
    e[++cnt].to = v;
    e[cnt].w = w;
    e[cnt].next = haed[u];
    haed[u] = cnt;
}

int dfs(int u)
{
    if (u > n - m)
    {
        dp[u][1] = val[u];
        return 1;
    }
    int sum = 0;
    for (int i = haed[u]; i; i = e[i].next)
    {
        int v = e[i].to;
        int tmp = dfs(v);
        for (int j = 0; j <= sum; j++)
            t[j] = dp[u][j];
        for (int j = 0; j <= sum; j++)
            for (int k = 0; k <= tmp; k++)
                dp[u][j + k] = max(dp[u][j + k], dp[v][k] + t[j] - e[i].w);
        sum += tmp;
    }
    return sum;
}

int main()
{
    scanf("%d%d", &n, &m);
    memset(dp, ~0x3f, sizeof(dp));
    for (int u = 1, v, w; u <= n - m; u++)
    {
        int k;
        scanf("%d", &k);
        for (int j = 1; j <= k; j++)
        {
            scanf("%d%d", &v, &w);
            addedge(u, v, w);
        }
    }
    for (int i = n - m + 1; i <= n; i++)
        scanf("%d", &val[i]);
    for (int i = 1; i <= n; i++)
        dp[i][0] = 0;
    dfs(1);
    for (int i = m; i > 0; i--)
        if (dp[1][i] >= 0)
        {
            printf("%d", i);
            break;
        }
    return 0;
}