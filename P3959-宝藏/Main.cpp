#include <algorithm>
#include <bitset>
#include <cctype>
#include <cmath>
#include <cstdio>
#include <cstring>
#include <deque>
#include <iostream>
#include <list>
#include <queue>
#include <set>
#include <stack>
#include <string>
#include <vector>

#include <ctime>

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

const int INF = 2e9;

int n, m;
int map[20][20];
int dep[20], vis[20];
struct edge
{
    int u, v;
    friend bool operator<(edge a, edge b)
    {
        return dep[a.u] * map[a.u][a.v] > dep[b.u] * map[b.u][b.v];
    }
};

int bfs(int s)
{
    memset(dep, 0, sizeof(dep));
    memset(vis, 0, sizeof(vis));
    priority_queue<edge> heap;
    edge past[1010];
    int p = 0, cost = 0;
    edge e1, e2;
    dep[s] = 1;
    vis[s] = 1;
    for (int i = 1; i <= n; i++)
    {
        if (map[s][i] < INF)
        {
            e1.u = s;
            e1.v = i;
            heap.push(e1);
        }
    }
    for (int i = 1; i < n; i++)
    {
        e1 = heap.top();
        heap.pop();
        while (!heap.empty() && (vis[e1.v] || rand() % n < 1))
        {
            if (!vis[e1.v])
                past[p++] = e1;
            e1 = heap.top();
            heap.pop();
        }
        vis[e1.v] = 1;
        dep[e1.v] = dep[e1.u] + 1;
        if (p-- > 0)
            for (; p >= 0; p--)
                heap.push(past[p]);
        p = 0;
        for (int i = 1; i <= n; i++)
            if (map[e1.v][i] < INF && !vis[i])
            {
                e2.u = e1.v;
                e2.v = i;
                heap.push(e2);
            }
        cost += map[e1.u][e1.v] * dep[e1.u];
    }
    return cost;
}

int main()
{
    read(n), read(m);
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n; j++)
            map[i][j] = INF;
    for (int i = 1; i <= m; ++i)
    {
        int a, b, c;
        read(a), read(b), read(c);
        map[a][b] = map[b][a] = min(c, map[a][b]);
    }
    srand(time(0)); 
    int ans = INF;
    for (int i = 1; i <= 1000; i++)
        for (int j = 1; j <= n; j++)
            ans = min(ans, bfs(j));
    printf("%d\n", ans);
    return 0;
}