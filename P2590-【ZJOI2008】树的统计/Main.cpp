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

const int MAXN = 100010;
const int INF = 2e9;

int n, q, a[MAXN << 2];
struct edge
{
    int u, v, nxt;
} g[MAXN];
int head[MAXN], tot;
int size[MAXN], wson[MAXN], fa[MAXN], d[MAXN], top[MAXN];
int tpos[MAXN], pre[MAXN], cnt;

inline void addedge(int u, int v)
{
    g[++tot].u = u, g[tot].v = v, g[tot].nxt = head[u], head[u] = tot;
    g[++tot].u = v, g[tot].v = u, g[tot].nxt = head[v], head[v] = tot;
}

inline void dfs1(int u, int f)
{
    size[u] = 1;
    for (int i = head[u]; i; i = g[i].nxt)
    {
        int v = g[i].v;
        if (v == f)
            continue;
        d[v] = d[u] + 1;
        fa[v] = u;
        dfs1(v, u);
        size[u] += size[v];
        if (size[v] > size[wson[u]])
            wson[u] = v;
    }
}

inline void dfs2(int u, int tp)
{
    tpos[u] = ++cnt;
    pre[cnt] = u;
    top[u] = tp;
    if (wson[u])
        dfs2(wson[u], tp);
    for (int i = head[u]; i; i = g[i].nxt)
    {
        int v = g[i].v;
        if (v == fa[u] || v == wson[u])
            continue;
        dfs2(v, v);
    }
}

int sumv[MAXN << 2], maxv[MAXN << 2];

inline int lc(int rt) { return rt << 1; }
inline int rc(int rt) { return rt << 1 | 1; }

inline void pushup(int rt)
{
    sumv[rt] = sumv[lc(rt)] + sumv[rc(rt)];
    maxv[rt] = max(maxv[lc(rt)], maxv[rc(rt)]);
}

inline void build(int rt, int l, int r)
{
    if (l == r)
    {
        sumv[rt] = maxv[rt] = a[pre[l]];
        return;
    }
    int mid = (l + r) >> 1;
    build(lc(rt), l, mid);
    build(rc(rt), mid + 1, r);
    pushup(rt);
}

inline void update(int rt, int l, int r, int q, int v)
{
    if (l == r)
    {
        sumv[rt] = maxv[rt] = v;
        return;
    }
    int mid = (l + r) >> 1;
    if (q <= mid)
        update(lc(rt), l, mid, q, v);
    else
        update(rc(rt), mid + 1, r, q, v);
    pushup(rt);
}

inline int querysum(int rt, int l, int r, int ql, int qr)
{
    int mid = (l + r) >> 1, ans = 0;
    if (ql <= l && qr >= r)
        return sumv[rt];
    if (ql <= mid)
        ans += querysum(lc(rt), l, mid, ql, qr);
    if (qr > mid)
        ans += querysum(rc(rt), mid + 1, r, ql, qr);
    pushup(rt);
    return ans;
}

inline int querymax(int rt, int l, int r, int ql, int qr)
{
    int mid = (l + r) >> 1, ans = -INF;
    if (ql <= l && qr >= r)
        return maxv[rt];
    if (ql <= mid)
        ans = max(ans, querymax(lc(rt), l, mid, ql, qr));
    if (qr > mid)
        ans = max(ans, querymax(rc(rt), mid + 1, r, ql, qr));
    pushup(rt);
    return ans;
}

inline int qsum(int u, int v)
{
    int ans = 0;
    while (top[u] != top[v])
    {
        if (d[top[u]] < d[top[v]])
            swap(u, v);
        ans += querysum(1, 1, n, tpos[top[u]], tpos[u]);
        u = fa[top[u]];
    }
    if (d[u] < d[v])
        swap(u, v);
    ans += querysum(1, 1, n, tpos[v], tpos[u]);
    return ans;
}

inline int qmax(int u, int v)
{
    int ans = -INF;
    while (top[u] != top[v])
    {
        if (d[top[u]] < d[top[v]])
            swap(u, v);
        ans = max(ans, querymax(1, 1, n, tpos[top[u]], tpos[u]));
        u = fa[top[u]];
    }
    if (d[u] < d[v])
        swap(u, v);
    ans = max(ans, querymax(1, 1, n, tpos[v], tpos[u]));
    return ans;
}

int main()
{
    read(n);
    for (int i = 1; i <= n - 1; i++)
    {
        int u, v;
        read(u), read(v);
        addedge(u, v);
    }
    for (int i = 1; i <= n; i++)
        read(a[i]);
    d[1] = 1;
    fa[1] = 1;
    dfs1(1, -1);
    dfs2(1, 1);
    build(1, 1, n);
    read(q);
    while (q--)
    {
        char s[10];
        int x, y;
        scanf("%s%d%d", s, &x, &y);
        if (s[1] == 'H')
            update(1, 1, n, tpos[x], y);
        if (s[1] == 'M')
            printf("%d\n", qmax(x, y));
        if (s[1] == 'S')
            printf("%d\n", qsum(x, y));
    }
    return 0;
}