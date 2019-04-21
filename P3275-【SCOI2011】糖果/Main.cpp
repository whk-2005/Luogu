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

const int N = 100010;
const int M = 300010;

struct edge
{
    int to, nxt, w;
    edge() {}
    edge(int _to, int _nxt, int _w) : to(_to), nxt(_nxt), w(_w) {}
} e[M];
int head[N], cnt;
int dis[N];
bool vis[N];
int n, m;
ll ans;

void addedge(int u, int v, int w)
{
    e[++cnt] = edge(v, head[u], w);
    head[u] = cnt;
}

bool spfa(int p)
{
    vis[p] = 1;
    for (int u = head[p]; ~u; u = e[u].nxt)
        if (dis[e[u].to] > dis[p] + e[u].w)
        {
            dis[e[u].to] = dis[p] + e[u].w;
            if (vis[e[u].to] || !spfa(e[u].to))
                return 0;
        }
    vis[p] = 0;
    return 1;
}

int main()
{
    read(n, m);
    memset(head, -1, sizeof(head));
    memset(dis, 0x3f, sizeof(dis));
    dis[0] = 0;
    for (int i = n; i >= 1; --i)
        addedge(0, i, -1);
    for (int i = 1; i <= m; ++i)
    {
        int x, a, b;
        read(x, a, b);
        switch (x)
        {
        case 1:
            addedge(a, b, 0);
            addedge(b, a, 0);
            break;
        case 2:
            if (a == b)
                return printf("-1\n"), 0;
            addedge(a, b, -1);
            break;
        case 3:
            addedge(b, a, 0);
            break;
        case 4:
            if (a == b)
                return printf("-1\n"), 0;
            addedge(b, a, -1);
            break;
        case 5:
            addedge(a, b, 0);
            break;
        }
    }
    if (spfa(0))
    {
        for (int i = 1; i <= n; ++i)
            ans -= dis[i];
        printf("%lld\n", ans);
    }
    else
        printf("-1\n");
    return 0;
}