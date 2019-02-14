// 好难啊~

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

template <typename t>
inline void read(t &num)
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

template <typename t, typename... Args>
inline void read(t &num, Args &... args) { read(num), read(args...); }

const int MAXN = 700005;
const int MAXM = 2000100;
const int INF = 0x7fffffff;

int heada[MAXN], cnt;
struct EDGE
{
    int to, nxt;
} edge[MAXM];
int n, m;
int w[MAXN];
int rt, sze[MAXN], disrt = INF;
int headb[MAXN], nlca;
int pathi, temp;
struct LCA
{
    int to, flag, nxt;
} Lca[MAXM];
vector<int> su[MAXN], sd[MAXN], tu[MAXN], td[MAXN];
int pre[MAXN], dep[MAXN], dis[MAXN], s[MAXN], t[MAXN], pret[MAXN];
int cnts[MAXM], cntt[MAXM], ans[MAXN];
int lca0[MAXN];
bool vis[MAXN];

inline void addedge(int a, int b)
{
    edge[cnt].to = b;
    edge[cnt].nxt = heada[a];
    heada[a] = cnt++;
    edge[cnt].to = a;
    edge[cnt].nxt =  heada[b];
    heada[b] = cnt++;
}

inline void link(int a, int b)
{
    Lca[nlca] = (LCA){b, 0, headb[a]};
    headb[a] = nlca++;
    Lca[nlca] = (LCA){a, 0, headb[b]};
    headb[b] = nlca++;
}

inline int find(int u)
{
    return u == pre[u] ? u : pre[u] = find(pre[u]);
}

inline void dfs1(int u, int f)
{
    int to, minn = INF, maxx = -INF;
    sze[u] = 1;
    for (int k = heada[u]; ~k; k = edge[k].nxt)
        if ((to = edge[k].to) != f)
        {
            dfs1(to, u);
            sze[u] += sze[to];
            minn = min(minn, sze[to]);
            maxx = max(maxx, sze[to]);
        }
    if (minn == INF)
        return;
    if (n - sze[u] < minn && f)
        minn = n - sze[u];
    if (n - sze[u] > maxx)
        maxx = n - sze[u];
    if (maxx - minn < disrt)
    {
        disrt = maxx - minn;
        rt = u;
    }
}

inline void dfs2(int u, int f)
{
    int to;
    pre[u] = u;
    dep[u] = dep[f] + 1;
    vis[u] = 1;
    for (int k = heada[u]; ~k; k = edge[k].nxt)
    {
        if ((to = edge[k].to) != f)
        {
            dfs2(to, u);
            pre[to] = u;
        }
    }
    for (int k = headb[u]; ~k; k = Lca[k].nxt)
    {
        if (!Lca[k].flag && vis[to = Lca[k].to])
        {
            Lca[k].flag = Lca[k ^ 1].flag = 1;
            int flag = 0, m = find(to);
            if (!(k & 1))
            {
                flag = 1;
                to ^= u ^= to ^= u;
            }
            pathi++;
            if (to == m)
            {
                s[pathi] = to;
                t[pathi] = u;
                dis[pathi] = dep[u] - dep[to];
                pret[pathi] = 0;
                sd[to].push_back(pathi);
                tu[u].push_back(pathi);
            }
            else if (u == m)
            {
                s[pathi] = to;
                t[pathi] = u;
                dis[pathi] = dep[to] - dep[u];
                td[u].push_back(pathi);
                su[to].push_back(pathi);
            }
            else
            {
                lca0[pathi] = m;
                s[pathi] = to;
                t[pathi] = m;
                dis[pathi] = dep[to] - dep[m];
                su[to].push_back(pathi);
                td[m].push_back(pathi);
                s[++pathi] = m;
                t[pathi] = u;
                dis[pathi] = dep[u] - dep[m];
                pret[pathi] = dep[to] - dep[m];
                sd[m].push_back(pathi);
                tu[u].push_back(pathi);
            }
            if (flag)
                u = to;
        }
    }
}

inline void dfs3(int u, int f)
{
    int ds = dep[u] + w[u] + MAXN, oris = cnts[ds], dt = dep[u] - w[u] + MAXN, orit = cntt[dt], to;
    for (int i = 0; i < su[u].size(); i++)
        cnts[dep[s[su[u][i]]] + MAXN]++;
    for (int i = 0; i < tu[u].size(); i++)
        cntt[dep[t[tu[u][i]]] - dis[tu[u][i]] - pret[tu[u][i]] + MAXN]++;
    for (int k = heada[u]; ~k; k = edge[k].nxt)
        if ((to = edge[k].to) != f)
            dfs3(to, u);
    ans[u] = cnts[ds] - oris + cntt[dt] - orit;
    for (int i = 0; i < td[u].size(); i++)
    {
        cnts[dep[s[td[u][i]]] + MAXN]--;
        if (lca0[td[u][i]] == u && dep[s[td[u][i]]] + MAXN == ds)
            ans[u]--;
    }
    for (int i = 0; i < sd[u].size(); i++)
        cntt[dep[t[sd[u][i]]] - dis[sd[u][i]] - pret[sd[u][i]] + MAXN]--;
}

int main()
{
    fill(heada, heada + MAXN, -1);
    fill(headb, headb + MAXN, -1);
    read(n, m);
    for (int i = 1; i < n; i++)
    {
        int u, v;
        read(u, v);
        addedge(u, v);
    }
    for (int i = 1; i <= n; i++)
        read(w[i]);
    for (int i = 1; i <= m; i++)
    {
        int u, v;
        read(u, v);
        link(u, v);
    }
    dfs1(1, 0);
    if (!rt)
        rt = 1;
    dfs2(rt, 0);
    dfs3(rt, 0);
    for (int i = 1; i <= n; i++)
        printf("%d ", ans[i]);
    printf("\n");
    return 0;
}