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

const int MAXN = 210;
const int MAXM = 50010;
int n, m;
int t[MAXM];
int dis[MAXN][MAXN], q, k;
int a, b, c;

int main()
{
    scanf("%d%d", &n, &m);
    memset(dis, 0x3f, sizeof(dis));
    memset(t, 0x3f, sizeof(t));
    for (int i = 0; i < n; i++)
        scanf("%d", &t[i]), dis[i][i] = 0;
    for (int i = 1; i <= m; i++)
    {
        scanf("%d%d%d", &a, &b, &c);
        dis[a][b] = dis[b][a] = c;
    }
    scanf("%d", &q);
    while (q--)
    {
        scanf("%d%d%d", &a, &b, &c);
        while (t[k] <= c)
        {
            for (int i = 0; i < n; i++)
                for (int j = 0; j < n; j++)
                    dis[i][j] = min(dis[i][j], dis[i][k] + dis[k][j]);
            k++;
        }
        if (dis[a][b] == 0x3f3f3f3f || t[a] > c || t[b] > c)
            printf("-1\n");
        else
            printf("%d\n", dis[a][b]);
    }
    return 0;
}