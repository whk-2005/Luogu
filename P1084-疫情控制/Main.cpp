#include <cstdio>
#include <algorithm>
#include <iostream>
#include <cstring>

using namespace std;

typedef long long ll;

const int MAXN = 50010;

int n, m;
int head[MAXN], nxt[MAXN << 1], to[MAXN << 1], cnt;
ll w[MAXN << 1];
int f[MAXN][20];
int army[MAXN];
ll dis[MAXN][20];
struct node
{
    ll rest;
    int id;
} a[MAXN], b[MAXN];
int vis[MAXN], used[MAXN], restbj[MAXN];
ll restmin[MAXN];
int na, nb;

inline void addedge(int x, int y, int z)
{
    to[++cnt] = y;
    nxt[cnt] = head[x];
    head[x] = cnt;
    w[cnt] = z;
}

inline void dfs(int x, int las, ll gone)
{
    f[x][0] = las, dis[x][0] = gone;
    for (int i = 1; i <= 17; i++)
    {
        f[x][i] = f[f[x][i - 1]][i - 1];
        dis[x][i] = dis[x][i - 1] + dis[f[x][i - 1]][i - 1];
    }
    for (int i = head[x]; ~i; i = nxt[i])
        if (to[i] != las)
            dfs(to[i], x, w[i]);
}

inline int check1(int x, int las)
{
    int tmp1 = 1, tmp2 = 0;
    if (vis[x])
        return 1;
    for (int i = head[x]; ~i; i = nxt[i])
    {
        if (to[i] == las)
            continue;
        tmp2 = 1;
        if (!check1(to[i], x))
        {
            tmp1 = 0;
            if (x == 1)
                b[++nb].id = to[i], b[nb].rest = w[i];
            else
                return 0;
        }
    }
    if (!tmp2)
        return 0;
    return tmp1;
}

inline bool cmp(node x, node y) { return x.rest > y.rest; }

inline int check(ll lim)
{
    na = nb = 0;
    for (int i = 1; i <= n; i++)
        vis[i] = restbj[i] = 0;
    for (int i = 1; i <= m; i++)
        used[i] = 0;
    for (int i = 1; i <= m; i++)
    {
        int x = army[i], num = 0;
        for (int j = 17; j >= 0; j--)
            if (f[x][j] > 1 && num + dis[x][j] <= lim)
                num += dis[x][j], x = f[x][j];
        if (f[x][0] == 1 && num + dis[x][0] <= lim)
        {
            a[++na].rest = lim - num - dis[x][0], a[na].id = i;
            if (!restbj[x] || a[na].rest < restmin[x])
                restmin[x] = a[na].rest, restbj[x] = i;
        }
        else
            vis[x] = 1;
    }
    // cout << ' ' << check1(1, 0) << endl;
    ll tmp;
    tmp = check1(1, 0);
        // cout << ' ' << tmp << endl;
    if (tmp)
        return 1;
    sort(a + 1, a + na + 1, cmp);
    sort(b + 1, b + nb + 1, cmp);
    int now = 1;
    used[0] = 1;
    for (int i = 1; i <= nb; i++)
    {
        if (!used[restbj[b[i].id]])
        {
            used[restbj[b[i].id]] = 1;
            continue;
        }
        while (now <= na && (used[a[now].id] || a[now].rest < b[i].rest))
            ++now;
        if (now > na)
            return 0;
        used[a[now].id] = 1;
    }
    return 1;
}

int main()
{
    scanf("%d", &n);
    memset(head, -1, sizeof(head));
    for (int i = 1; i < n; i++)
    {
        int x, y, z;
        scanf("%d%d%d", &x, &y, &z);
        addedge(x, y, z);
        addedge(y, x, z);
    }
    dfs(1, 0, 0);
    scanf("%d", &m);
    for (int i = 1; i <= m; i++)
        scanf("%d", &army[i]);
    ll l = 0, r = 500000;
    ll ans = -1;
    while (l <= r)
    {
        ll mid = (l + r) >> 1;
        ll tmp = check(mid);
        if (tmp)
            r = mid - 1, ans = mid;
        else
            l = mid + 1;
         // cout << tmp << endl;
    }
    printf("%lld\n", ans);
    return 0;
}