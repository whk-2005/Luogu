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

const int MAXN = 100010;

int n, m;
int head[MAXN], nxt[MAXN << 1], to[MAXN << 1], cnt;
int id[MAXN], size[MAXN], tot;
int dis[MAXN];
ll a[MAXN << 2], b[MAXN << 2], val[MAXN << 2];

inline void addedge(int u, int v)
{
    to[++cnt] = v;
    nxt[cnt] = head[u];
    head[u] = cnt;
}

inline void dfs(int u)
{
    id[u] = ++tot;
    size[u] = 1;
    for (int i = head[u]; i; i = nxt[i])
    {
        int v = to[i];
        if (!size[v])
        {
            dis[v] = dis[u] + 1;
            dfs(v);
            size[u] += size[v];
        }
    }
}

inline int lc(int rt) { return rt << 1; }
inline int rc(int rt) { return rt << 1 | 1; }

inline void pushdown(int u)
{
    a[lc(u)] += a[u];
    a[rc(u)] += a[u];
    b[lc(u)] += b[u];
    b[rc(u)] += b[u];
    a[u] = b[u] = 0;
}

inline void update(int rt, int ql, int qr, int l, int r, ll x, ll y)
{
    if (ql <= l && qr >= r)
    {
        a[rt] += x;
        b[rt] += y;
        return;
    }
    pushdown(rt);
    int mid = (l + r) >> 1;
    if (ql <= mid)
        update(lc(rt), ql, qr, l, mid, x, y);
    if (qr > mid)
        update(rc(rt), ql, qr, mid + 1, r, x, y);
}

inline ll query(int rt, int l, int r, int u, int x)
{
    if (l == r)
        return dis[u] * a[rt] + b[rt];
    pushdown(rt);
    int mid = (l + r) >> 1;
    if (x <= mid)
        return query(lc(rt), l, mid, u, x);
    else
        return query(rc(rt), mid + 1, r, u, x);
}

int main()
{
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; i++)
        scanf("%lld", &val[i]);
    for (int i = 1; i < n; i++)
    {
        int x, y;
        scanf("%d%d", &x, &y);
        addedge(x, y);
        addedge(y, x);
    }
    dis[1] = 1;
    dfs(1);
    for (int i = 1; i <= n; i++)
        update(1, id[i], id[i] + size[i] - 1, 1, n, 0, val[i]);
    for (int i = 1; i <= m; i++)
    {
        int x, z;
        ll y;
        scanf("%d%d", &z, &x);
        // cout << ">>" << z << ' ' << x << ' ' << y << endl;
        if (z == 1)
            scanf("%lld", &y), update(1, id[x], id[x] + size[x] - 1, 1, n, 0, y);
        if (z == 2)
            scanf("%lld", &y), update(1, id[x], id[x] + size[x] - 1, 1, n, y, -((dis[x] - 1) * y));
        if (z == 3)
            printf("%lld\n", query(1, 1, n, x, id[x]));
    }
    return 0;
}