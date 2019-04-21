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
inline void read(T &num, Args &... args) { read(num), read(args...); }

const int N = 400010;
const int M = 800010;

int t;
int n, m;
int lastans;
struct point
{
    int u, v, l, a;
} e[M], p[M];
struct edge
{
    int v, nxt;
} e1[M << 1];
struct node
{
    int v, nxt, w;
} e2[M];
int head1[M], head2[M], cnt1, cnt2;
int f[N][20];
int fa[M];
int dis[N], vis[N];
int dep[N];
int q, k, s;
struct heap
{
    int u, v;
};

inline bool operator<(heap a, heap b) { return a.v > b.v; }

inline void addedge1(int u, int v)
{
    e1[++cnt1].v = v;
    e1[cnt1].nxt = head1[u];
    head1[u] = cnt1;
}

inline void addedge2(int u, int v, int w)
{
    e2[++cnt2].v = v;
    e2[cnt2].nxt = head2[u];
    e2[cnt2].w = w;
    head2[u] = cnt2;
}

inline void dijkstra(int s = 1)
{
    memset(vis, false, sizeof(vis));
    memset(dis, 0x3f, sizeof(dis));
    priority_queue<heap> q;
    dis[s] = 0;
    q.push((heap){s, dis[s]});
    while (!q.empty())
    {
        heap x = q.top();
        q.pop();
        if (vis[x.u])
            continue;
        vis[x.u] = true;
        for (int i = head2[x.u]; i; i = e2[i].nxt)
        {
            int v = e2[i].v;
            if (vis[v])
                continue;
            if (dis[v] > dis[x.u] + e2[i].w)
            {
                dis[v] = dis[x.u] + e2[i].w;
                q.push((heap){v, dis[v]});
            }
        }
    }
    for (int i = 1; i <= n; ++i)
        p[i].l = dis[i];
}

inline void dfs(int u, int pa)
{
    dep[u] = dep[pa] + 1;
    f[u][0] = pa;
    for (int i = 1; i <= 19; i++)
        f[u][i] = f[f[u][i - 1]][i - 1];
    for (int i = head1[u]; i; i = e1[i].nxt)
    {
        int v = e1[i].v;
        dfs(v, u);
        p[u].l = min(p[u].l, p[v].l);
    }
}

inline bool cmp(point a, point b) { return a.a > b.a; }

inline int find(int u) { return u == fa[u] ? fa[u] : fa[u] = find(fa[u]); }

inline int findans(int x, int y)
{
    for (int i = 19; i >= 0; i--)
        if (dep[x] - (1 << i) > 0 && p[f[x][i]].a > y)
            x = f[x][i];
    return p[x].l;
}

inline void kruskal()
{
    int tot = 0;
    int cnt = n;
    for (int i = 1; i <= (n << 1); i++)
        fa[i] = i;
    sort(e + 1, e + m + 1, cmp);
    for (int i = 1; i <= m; i++)
    {
        int u = e[i].u, v = e[i].v;
        int fu = find(u), fv = find(v);
        if (fu != fv)
        {
            addedge1(++cnt, fu);
            addedge1(cnt, fv);
            fa[fu] = cnt;
            fa[fv] = cnt;
            p[cnt].a = e[i].a;
            tot++;
        }
        if (tot == n - 1)
            break;
    }
    dfs(cnt, 0);
    while (q--)
    {
        int t1, t2;
        read(t1, t2);
        int x = (k * lastans + t1 - 1) % n + 1;
        int y = (k * lastans + t2) % (s + 1);
        printf("%d\n", lastans = findans(x, y));
    }
}

int main()
{
    read(t);
    while (t--)
    {
        read(n, m);
        lastans = 0;
        cnt1 = cnt2 = 0;
        memset(e1, 0, sizeof(e1));
        memset(head1, 0, sizeof(head1));
        memset(head2, 0, sizeof(head2));
        memset(f, 0, sizeof(f));
        for (int i = 1; i <= m; i++)
        {
            read(e[i].u, e[i].v, e[i].l, e[i].a);
            addedge2(e[i].u, e[i].v, e[i].l);
            addedge2(e[i].v, e[i].u, e[i].l);
        }
        for (int i = n + 1; i <= (n << 1); i++)
            p[i].l = 0x3f3f3f3f;
        dijkstra();
        read(q, k, s);
        kruskal();
    }
    return 0;
}