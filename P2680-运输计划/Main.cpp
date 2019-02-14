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

const int MAXN = 3e5 + 10;
const int INF = 0x7fffffff;

int n, m;
int head[MAXN << 1], nxt[MAXN << 1], v[MAXN << 1], cnt;
int x[MAXN], y[MAXN], z[MAXN], p[MAXN];
int son[MAXN], fa[MAXN], sz[MAXN], dep[MAXN], root;
int id[MAXN], top[MAXN], rnk[MAXN], num;
int c[MAXN], d[MAXN], srt[MAXN];
int ma, mb, mc;

inline int max(int a, int b) { return a > b ? a : b; }
inline int min(int a, int b) { return a < b ? a : b; }

struct Binary_Indexed_Tree
{
    int a[MAXN];

    inline int lowbit(int k) { return k & (-k); }

    inline void update(int x, int k)
    {
        for (int i = x; i <= n; i += lowbit(i))
            a[i] += k;
    }

    inline int query(int x)
    {
        int ans = 0;
        for (int i = x; i >= 1; i -= lowbit(i))
            ans += a[i];
        return ans;
    }

    inline void build(int x)
    {
        for (int i = 1; i <= n; i++)
            update(i, p[rnk[i]]);
    }

    inline int sum(int x, int y)
    {
        return query(y) - query(x - 1);
    }
} BIT;

struct Segment_Tree
{
#define mid ((x + y) >> 1)
#define lson (rt << 1)
#define rson (rt << 1 | 1)

    int mx[MAXN << 2], tag[MAXN << 2];

    inline void pushdown(int rt)
    {
        if (tag[rt])
        {
            mx[lson] = max(mx[lson], tag[rt]);
            mx[rson] = max(mx[rson], tag[rt]);
            tag[lson] = max(tag[lson], tag[rt]);
            tag[rson] = max(tag[rson], tag[rt]);
            tag[rt] = 0;
        }
    }

    inline void pushup(int rt) { mx[rt] = max(mx[lson], mx[rson]); }

    inline void update(int x, int y, int rt, int l, int r, int k)
    {
        if (x > y || y < l || x > r)
            return;
        if (l <= x && y <= r)
        {
            mx[rt] = max(mx[rt], k);
            tag[rt] = max(tag[rt], k);
            return;
        }
        pushdown(rt);
        update(x, mid, lson, l, r, k);
        update(mid + 1, y, rson, l, r, k);
        pushup(rt);
    }

    inline int query(int x, int y, int rt, int p)
    {
        if (x == y)
            return mx[rt];
        pushdown(rt);
        if (p <= mid)
            return query(x, mid, lson, p);
        else
            return query(mid + 1, y, rson, p);
    }
} ST;

inline void addedge(int x, int y)
{
    v[cnt] = y;
    nxt[cnt] = head[x];
    head[x] = cnt++;
}

inline void dfs1(int x, int f, int d)
{
    fa[x] = f;
    dep[x] = d;
    sz[x] = 1;
    for (int i = head[x]; ~i; i = nxt[i])
    {
        if (v[i] == f)
            continue;
        dfs1(v[i], x, d + 1);
        sz[x] += sz[v[i]];
        if (sz[v[i]] > sz[son[x]])
            son[x] = v[i];
    }
}

inline void dfs2(int x, int t)
{
    top[x] = t;
    id[x] = ++num;
    rnk[id[x]] = x;
    if (!son[x])
        return;
    dfs2(son[x], t);
    for (int i = head[x]; ~i; i = nxt[i])
        if (v[i] != fa[x] && v[i] != son[x])
            dfs2(v[i], v[i]);
}

inline int sum(int x, int y)
{
    int tx = top[x], ty = top[y];
    int ans = 0;
    while (tx != ty)
    {
        if (dep[tx] >= dep[ty])
            ans += BIT.sum(id[tx], id[x]), x = fa[tx], tx = top[x];
        else
            ans += BIT.sum(id[ty], id[y]), y = fa[ty], ty = top[y];
    }
    if (id[x] <= id[y])
        ans += BIT.sum(id[x] + 1, id[y]);
    else
        ans += BIT.sum(id[y] + 1, id[x]);
    return ans;
}

inline bool cmp(int x, int y) { return c[x] < c[y]; }

inline void update(int x, int y, int z)
{
    int tx = top[x], ty = top[y], t = 0;
    while (tx != ty)
    {
        if (dep[tx] >= dep[ty])
            c[++t] = id[tx], d[t] = id[x], x = fa[tx], tx = top[x];
        else
            c[++t] = id[ty], d[t] = id[y], y = fa[ty], ty = top[y];
    }
    if (id[x] <= id[y])
        c[++t] = id[x] + 1, d[t] = id[y];
    else
        c[++t] = id[y] + 1, d[t] = id[x];
    for (int i = 1; i <= t; i++)
        srt[i] = i;
    sort(srt + 1, srt + t + 1, cmp);
    if (c[srt[1]] > 1)
        ST.update(1, n, 1, 1, c[srt[1]] - 1, z);
    if (d[srt[t]] < n)
        ST.update(1, n, 1, d[srt[t]] + 1, n, z);
    for (int i = 1; i < t; i++)
        ST.update(1, n, 1, d[srt[i]] + 1, c[srt[i + 1]] - 1, z);
}

inline int find(int x, int y)
{
    int ans = INF;
    if (x == y)
        return 0;
    if (dep[x] < dep[y])
        swap(x, y);
    while (dep[x] != dep[y])
        ans = min(ans, max(mc - p[x], ST.query(1, n, 1, id[x]))), x = fa[x];
    while (x != y)
    {
        if (dep[x] > dep[y])
            ans = min(ans, max(mc - p[x], ST.query(1, n, 1, id[x]))), x = fa[x];
        else
            ans = min(ans, max(mc - p[y], ST.query(1, n, 1, id[y]))), y = fa[y];
    }
    return ans;
}

int main()
{
    memset(head, -1, sizeof(head));
    read(n), read(m);
    for (int i = 1; i < n; i++)
        read(x[i]), read(y[i]), read(z[i]), addedge(x[i], y[i]), addedge(y[i], x[i]);
    root = 1;
    dfs1(root, 0, 1);
    dfs2(root, root);
    for (int i = 1; i < n; i++)
    {
        if (dep[x[i]] > dep[y[i]])
            p[x[i]] = z[i];
        else
            p[y[i]] = z[i];
    }
    BIT.build(n);
    for (int i = 1; i <= m; i++)
    {
        int a, b, tmp;
        read(a), read(b);
        tmp = sum(a, b);
        update(a, b, tmp);
        if (tmp >= mc)
            ma = a, mb = b, mc = tmp;
    }
    printf("%d\n", find(ma, mb));
    return 0;
}