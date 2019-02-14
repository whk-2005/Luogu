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

const int MAXN = 2e3 + 10;
const int MAXV = 310;
const double INF = 1e17;

int n, m, v, e;
int c[MAXN], d[MAXN];
double k[MAXN];
int x, y, z;
int Map[MAXV][MAXV];
double dp[MAXN][MAXN][2];
double ans;

int main()
{
    memset(Map, 63, sizeof(Map));
    read(n), read(m), read(v), read(e);
    for (int i = 1; i <= n; i++)
        read(c[i]);
    for (int i = 1; i <= n; i++)
        read(d[i]);
    for (int i = 1; i <= n; i++)
        scanf("%lf", &k[i]);
    for (int i = 1; i <= e; i++)
    {
        read(x), read(y), read(z);
        Map[x][y] = Map[y][x] = min(Map[x][y], z);
    }
    for (int k = 1; k <= v; k++)
        for (int i = 1; i <= v; i++)
            for (int j = 1; j <= v; j++)
                Map[i][j] = min(Map[i][j], Map[i][k] + Map[k][j]);
    for (int i = 1; i <= v; i++)
        Map[i][i] = Map[i][0] = Map[0][i] = 0;
    for (int i = 0; i <= n; i++)
        for (int j = 0; j <= m; j++)
            dp[i][j][0] = dp[i][j][1] = INF;
    dp[1][0][0] = dp[1][1][1] = 0;
    for (int i = 2; i <= n; i++)
    {
        dp[i][0][0] = dp[i - 1][0][0] + Map[c[i - 1]][c[i]];
        for (int j = 1; j <= min(i, m); j++)
        {
            int C1 = c[i - 1], C2 = d[i - 1], C3 = c[i], C4 = d[i];
            dp[i][j][0] = min(dp[i][j][0], min(dp[i - 1][j][0] + Map[C1][C3], dp[i - 1][j][1] + Map[C1][C3] * (1 - k[i - 1]) + Map[C2][C3] * k[i - 1]));
            dp[i][j][1] = min(dp[i][j][1], min(dp[i - 1][j - 1][0] + Map[C1][C3] * (1 - k[i]) + Map[C1][C4] * k[i], dp[i - 1][j - 1][1] + Map[C2][C4] * k[i] * k[i - 1] + Map[C2][C3] * k[i - 1] * (1 - k[i]) + Map[C1][C4] * (1 - k[i - 1]) * k[i] + Map[C1][C3] * (1 - k[i - 1]) * (1 - k[i])));
        }
    }
    ans = INF;
    for (int i = 0; i <= m; i++)
        ans = min(ans, min(dp[n][i][0], dp[n][i][1]));
    printf("%.2lf", ans);
    return 0;
}