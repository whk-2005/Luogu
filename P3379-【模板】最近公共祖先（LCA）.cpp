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

const int MAXN = 500010;
int n, m, s;
struct edge
{
    int to, next;
} e[MAXN * 2];
int head[MAXN], depth[MAXN], f[MAXN][30];
int lg[MAXN];
int tot;

inline void add_edge(int u, int v)
{
    e[++tot].to = v;
    e[tot].next = head[u];
    head[u] = tot;
}

void dfs(int x, int y)
{
    depth[x] = depth[y] + 1;
    f[x][0] = y;
    for (int i = 1; (1 << i) <= depth[x]; i++)
        f[x][i] = f[f[x][i - 1]][i - 1];
    for (int i = head[x]; i; i = e[i].next)
        if (e[i].to != y)
            dfs(e[i].to, x);
}

int lca(int x, int y)
{
    if (depth[x] < depth[y])
        swap(x, y);
    while (depth[x] > depth[y])
        x = f[x][lg[depth[x] - depth[y]] - 1];
    if (x == y)
        return x;
    for (int i = lg[depth[x]] - 1; i >= 0; i--)
        if (f[x][i] != f[y][i])
            x = f[x][i], y = f[y][i];
    return f[x][0];
}

int main()
{
    scanf("%d%d%d", &n, &m, &s);
    for (int i = 1; i < n; i++)
    {
        int u, v;
        scanf("%d%d", &u, &v);
        add_edge(u, v), add_edge(v, u);
    }
    dfs(s, 0);
    for (int i = 1; i <= n; i++)
        lg[i] = lg[i - 1] + (1 << lg[i - 1] == i);
    for (int i = 1; i <= m; i++)
    {
        int u, v;
        scanf("%d%d", &u, &v);
        printf("%d\n", lca(u, v));
    }
    return 0;
}