#include <algorithm>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <queue>

using namespace std;

int n, m, k, e;
int map[30][30];
int d, u, v, w;
int a[30][110];
int dp[110];
int now[30];
int p, st, en;

int spfa()
{
    queue<int> q;
    int dis[30];
    int vis[30];
    for (int i = 1; i <= m; i++)
        dis[i] = 0x7ffffff, vis[i] = 0;
    dis[1] = 0;
    q.push(1);
    while (!q.empty())
    {
        int u = q.front();
        q.pop();
        vis[u] = 0;
        for (int i = 1; i <= m; i++)
        {
            if (now[i])
                continue;
            if (map[u][i] > 0 && dis[i] > dis[u] + map[u][i])
            {
                dis[i] = dis[u] + map[u][i];
                if (vis[i] == 0)
                {
                    q.push(i);
                    vis[i] = 1;
                }
            }
        }
    }
    return dis[m];
}

int main()
{
    scanf("%d%d%d%d", &n, &m, &k, &e);
    for (int i = 1; i <= m; i++)
        for (int j = 1; j <= m; j++)
            map[i][j] = 0x7ffffff;
    for (int i = 1; i <= e; i++)
    {
        scanf("%d%d%d", &u, &v, &w);
        map[u][v] = w;
        map[v][u] = w;
    }
    scanf("%d", &d);
    for (int i = 1; i <= d; i++)
    {
        scanf("%d%d%d", &p, &st, &en);
        for (int j = st; j <= en; j++)
            a[p][j] = 1;
    }
    for (int i = 1; i <= n; i++)
        dp[i] = 0x7ffffff;
    dp[0] = -k;
    for (int i = 1; i <= n; i++)
    {
        memset(now, 0, sizeof(now));
        for (int j = i; j >= 1; j--)
        {
            for (int l = 1; l <= m; l++)
            {
                now[l] |= a[l][j];
            }
            int ll = spfa();
            if (ll == 0x7ffffff)
                continue;
            dp[i] = min(dp[i], dp[j - 1] + ll * (i - j + 1) + k);
        }
    }
    cout << dp[n];
    return 0;
}