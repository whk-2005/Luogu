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

template <typename T>
inline void read(T &num)
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

template <typename T, typename... Args>
inline void read(T &num, Args&... args) { read(num), read(args...); }

const int MAXN = 300010;

struct Edge
{
    int next, ends;
    int wei;
} edge[MAXN << 1];
int head[MAXN], fa[40][MAXN], d[MAXN], s[MAXN], e;
int cnt[MAXN];
int vis[MAXN];
int n;

void dfs(int p, int dpt)
{
    vis[p] = true;
    d[p] = dpt;
    for (int i = head[p]; i; i = edge[i].next)
    {
        if (vis[edge[i].ends])
            continue;
        fa[0][edge[i].ends] = p;
        dfs(edge[i].ends, dpt + 1);
    }
}

void addedge(int u, int v)
{
    edge[++e].ends = v;
    edge[e].next = head[u];
    head[u] = e;
}

int lca(int x, int y)
{
    if (d[x] < d[y])
        swap(x, y);
    int dif = d[x] - d[y];
    for (int i = 30; i >= 0; --i)
        if (1 << i <= dif)
            dif -= 1 << i,
                x = fa[i][x];
    if (x == y)
        return x;
    for (int i = 30; i >= 0; --i)
        if (fa[i][x] != fa[i][y])
            x = fa[i][x], y = fa[i][y];
    if (x == y)
        return x;
    else
        return fa[0][x];
}

int dfs_ans(int p)
{
    int ans = cnt[p];
    vis[p] = true;
    for (int i = head[p]; i; i = edge[i].next)
    {
        if (vis[edge[i].ends])
            continue;
        ans += edge[i].wei = dfs_ans(edge[i].ends);
    }
    for (int i = head[p]; i; i = edge[i].next)
    {
        if (edge[i].ends == fa[0][p])
            edge[i].wei = ans, i = 0;
    }
    return ans;
}

int main()
{
    read(n);
    for (int i = 1; i <= n; i++)
        read(s[i]);
    for (int i = 1; i < n; i++)
    {
        int a, b;
        read(a, b);
        addedge(a, b);
        addedge(b, a);
    }
    fa[0][s[1]] = s[1];
    dfs(s[1], 1);
    for (int i = 1; 1 << i <= n; i++)
        for (int j = 1; j <= n; j++)
            fa[i][j] = fa[i - 1][fa[i - 1][j]];
    for (int i = 1; i < n; i++)
        cnt[s[i]]++, cnt[s[i + 1]]++, cnt[lca(s[i], s[i + 1])] -= 2;
    memset(vis, 0, sizeof(vis));
    dfs_ans(s[1]);
    for (int i = 1; i <= n; i++)
    {
        int ans = 0;
        for (int j = head[i]; j; j = edge[j].next)
            ans += edge[j].wei;
        if (i == s[n])
            ans--;
        printf("%d\n", (ans + 1) >> 1);
    }
    return 0;
}