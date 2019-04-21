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

const int MAXN = 1e6 + 10;

struct edge
{
    int u, nxt;
} e[MAXN << 2];
int head[MAXN << 1], cnt;
int low[MAXN << 1], dfn[MAXN << 1], scc[MAXN << 1];
stack<int> sta;
bool vis[MAXN << 1];
int n, m;
int tim, tot;

inline void addedge(int u, int v)
{
    e[++cnt].u = v;
    e[cnt].nxt = head[u];
    head[u] = cnt;
}

inline void tarjan(int u)
{
    // cout << u << endl;
    low[u] = dfn[u] = ++tim;
    sta.push(u);
    vis[u] = 1;
    for (int i = head[u]; i; i = e[i].nxt)
    {
        int v = e[i].u;
        if (!dfn[v])
        {
            tarjan(v);
            low[u] = min(low[u], low[v]);
        }
        else if (vis[v])
            low[u] = min(low[u], dfn[v]);
    }
    if (low[u] == dfn[u])
    {
        int v;
        tot++;
        do
        {
            v = sta.top();
            sta.pop();
            vis[v] = 0;
            scc[v] = tot;
        } while (u != v);
    }
}

inline bool two_sat()
{
    for (int i = 1; i <= 2 * n; i++)
        if (!dfn[i])
            tarjan(i);
    for (int i = 1; i <= n; i++)
        if (scc[i] == scc[n + i])
            return 0;
    return 1;
}

int main()
{
    read(n, m);
    for (int i = 1; i <= m; i++)
    {
        int u, v, a, b, x, y;
        read(u, a, v, b);
        x = a ^ 1, y = b ^ 1;
        addedge(u + n * x, v + n * b);
        addedge(v + n * y, u + n * a);
    }
    if (two_sat())
    {
        printf("POSSIBLE\n");
        for (int i = 1; i <= n; i++)
            printf("%d ", scc[i] > scc[n + i]);
        printf("\n");
    }
    else
        printf("IMPOSSIBLE\n");
    return 0;
}