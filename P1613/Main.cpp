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

int dis[60][60], n, m;
bool g[60][60][65];

int main()
{
    memset(dis, 10, sizeof(dis));
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= m; i++)
    {
        int x, y;
        scanf("%d%d", &x, &y);
        dis[x][y] = 1;
        g[x][y][0] = true;
    }
    for (int k = 1; k <= 64; k++)
        for (int i = 1; i <= n; i++)
            for (int t = 1; t <= n; t++)
                for (int j = 1; j <= n; j++)
                    if (g[i][t][k - 1] && g[t][j][k - 1])
                    {
                        g[i][j][k] = true;
                        dis[i][j] = 1;
                    }
    for (int k = 1; k <= n; k++)
        for (int i = 1; i <= n; i++)
            for (int j = 1; j <= n; j++)
                dis[i][j] = min(dis[i][j], dis[i][k] + dis[k][j]);
    printf("%d", dis[1][n]);
    return 0;
}