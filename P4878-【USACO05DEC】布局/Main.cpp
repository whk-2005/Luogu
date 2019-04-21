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

const int N = 1010;
const int M = 40010;

int n, ml, md;
int a, b, c;
struct edge
{
    int to, nxt, w;
    edge() {}
    edge(int _to, int _nxt, int _w) : to(_to), nxt(_nxt), w(_w) {}
} e[M];
int head[N], cnt;
int dis[N], in[N], vis[N];
queue<int> q;

#define DEBUG(x) cout << #x << ": " << x << endl

void addedge(int u, int v, int w)
{
    e[++cnt] = edge(v, head[u], w);
    head[u] = cnt;
}

void spfa(int s)
{
    memset(dis, 0x3f, sizeof(dis));
    memset(in, 0, sizeof(in));
    memset(vis, 0, sizeof(vis));
    dis[s] = 0;
    q.push(s);
    in[s] = 1;
    while (!q.empty())
    {
        int u = q.front();
        // DEBUG(u);
        q.pop();
        in[u] = 0;
        for (int i = head[u]; ~i; i = e[i].nxt)
        {
            int v = e[i].to;
            if (dis[u] + e[i].w < dis[v])
            {
                dis[v] = dis[u] + e[i].w;
                vis[v] = vis[u] + 1;
                if (vis[v] >= n)
                {
                    printf("-1\n");
                    exit(0);
                }
                if (!in[v])
                {
                    in[v] = 1;
                    q.push(v);
                }
            }
        }
    }
}

int main()
{
    memset(head, -1, sizeof(head));
    read(n, ml, md);
    for (int i = 1; i <= n; ++i)
        addedge(0, i, 0);
    for (int i = 1; i <= ml; ++i)
        read(a, b, c), addedge(a, b, c);
    for (int i = 1; i <= md; ++i)
        read(a, b, c), addedge(b, a, -c);
    // for (int i = 0; i <= n; i++)
    // {
    //     for (int j = head[i]; ~j; j = e[j].nxt)
    //         DEBUG(i), DEBUG(e[i].to);
    // }
    spfa(0);
    spfa(1);
    if (dis[n] == 0x3f3f3f3f)
        printf("-2\n");
    else
        printf("%d\n", dis[n]);
    // for (int i = 1; i <= n; ++i)
    //     DEBUG(dis[i]);
    return 0;
}