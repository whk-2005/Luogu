#include <algorithm>
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

const int MAXN = 100010;
const int MAXM = 200010;
int n, m, s;
struct edge
{
    int to, dis, next;
} e[MAXM];
int head[MAXN], dis[MAXN], cnt;
bool vis[MAXN];
struct node
{
    int dis, pos;
    bool operator<(const node &x) const
    {
        return x.dis < dis;
    }
};
priority_queue<node> q;

inline void add_edge(int u, int v, int d)
{
    e[++cnt].dis = d;
    e[cnt].to = v;
    e[cnt].next = head[u];
    head[u] = cnt;
}

inline void dijkstra()
{
    dis[s] = 0;
    q.push((node){0, s});
    while (!q.empty())
    {
        node pre = q.top();
        q.pop();
        int p = pre.pos, d = pre.dis;
        if (vis[p])
            continue;
        vis[p] = 1;
        for (int i = head[p]; i; i = e[i].next)
        {
            int t = e[i].to;
            if (dis[t] > dis[p] + e[i].dis)
            {
                dis[t] = dis[p] + e[i].dis;
                if (!vis[t])
                    q.push((node){dis[t], t});
            }
        }
    }
}

inline void numset(int *st, int *en, int val)
{
    for (int *i = st; i != en; i++)
        *i = val;
}

int main()
{
    scanf("%d%d%d", &n, &m, &s);
    numset(dis + 1, dis + n + 1, 0x7fffffff);
    for (int i = 1; i <= m; i++)
    {
        int u, v, d;
        scanf("%d%d%d", &u, &v, &d);
        add_edge(u, v, d);
    }
    dijkstra();
    for (int i = 1; i <= n; i++)
        printf("%d ", dis[i]);
    printf("\n");
    return 0;
}