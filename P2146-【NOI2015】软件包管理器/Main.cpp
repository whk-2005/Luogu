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

const int MAXN = 100010;

int n, k, q;
int tot, cnt;
struct node
{
    int v, nxt;
} edge[MAXN << 1];
int head[MAXN];
int dep[MAXN], sze[MAXN], fa[MAXN], top[MAXN], son[MAXN], num[MAXN];
int sum[MAXN * 5], val[MAXN * 5], orsum[MAXN * 5];
char ss[20];

inline void addedge(int u, int v)
{
    edge[++tot].nxt = head[u];
    edge[tot].v = v;
    head[u] = tot;
}

inline void dfs1(int u, int f)
{
    sze[u] = 1;
    for (int i = head[u]; i; i = edge[i].nxt)
    {
        int v = edge[i].v;
        dep[v] = dep[u] + 1;
        dfs1(v, u);
        sze[u] += sze[v];
        if (sze[v] > sze[son[u]])
            son[u] = v;
    }
}

inline void dfs2(int u, int tp)
{
    top[u] = tp;
    num[u] = ++cnt;
    if (son[u])
        dfs2(son[u], tp);
    for (int i = head[u]; i; i = edge[i].nxt)
    {
        int v = edge[i].v;
        if (v == fa[u] || v == son[u])
            continue;
        dfs2(v, v);
    }
}

#define lc (p << 1)
#define rc (lc | 1)

inline void update(int mid, int s, int t, int p)
{
    val[lc] = val[rc] = val[p];
    if (val[p] == 0)
        sum[lc] = sum[rc] = 0;
    else
    {
        sum[lc] = mid - s + 1;
        sum[rc] = t - mid;
    }
    val[p] = -1;
}

inline int query(int ll, int rr, int s, int t, int p, int w)
{
    if (ll <= s && t <= rr)
    {
        int ans = sum[p];
        val[p] = w;
        sum[p] = (t - s + 1) * w;
        return ans;
    }
    int mid = (s + t) >> 1;
    if (val[p] >= 0)
        update(mid, s, t, p);
    int ans = 0;
    if (ll <= mid)
        ans += query(ll, rr, s, mid, lc, w);
    if (rr > mid)
        ans += query(ll, rr, mid + 1, t, rc, w);
    sum[p] = sum[lc] + sum[rc];
    return ans;
}

inline int qsum(int u, int v)
{
    int ans = 0;
    while (top[u] != top[v])
    {
        if (dep[top[u]] < dep[top[v]])
            swap(u, v);
        ans += query(num[top[u]], num[u], 1, n, 1, 1);
        u = fa[top[u]];
    }
    if (dep[u] > dep[v])
        swap(u, v);
    ans += query(num[u], num[v], 1, n, 1, 1);
    return ans;
}

int main()
{
    read(n);
    for (int i = 1; i < n; i++)
    {
        int u;
        u = read(u) + 1;
        fa[i + 1] = u;
        addedge(u, i + 1);
    }
    dep[1] = 1;
    dfs1(1, -1);
    dfs2(1, 1);
    memset(val, -1, sizeof(val));
    read(q);
    while (q--)
    {
        scanf("%s", ss);
        int u, ans;
        u = read(u) + 1;
        if (ss[0] == 'i')
        {
            ans = qsum(u, 1);
            ans = dep[u] - ans;
        }
        else if (ss[0] == 'u')
            ans = query(num[u], num[u] + sze[u] - 1, 1, n, 1, 0);
        printf("%d\n", ans);
    }
    return 0;
}