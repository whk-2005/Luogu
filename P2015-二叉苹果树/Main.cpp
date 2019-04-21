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

const int N = 110;

int n, q;
struct edge
{
    int to, nxt, w;
} e[N << 1];
int head[N], cnt;
int f[N][N];
int sz[N];

inline void addedge(int u, int v, int w)
{
    e[++cnt].to = v;
    e[cnt].nxt = head[u];
    e[cnt].w = w;
    head[u] = cnt;
}

inline void dfs(int u, int fa)
{
    for (int i = head[u]; i; i = e[i].nxt)
    {
        int v = e[i].to;
        if (v == fa)
            continue;
        dfs(v, u);
        sz[u] += sz[v] + 1;
        for (int j = min(sz[u], q); j; j--)
            for (int k = min(sz[v], j - 1); k >= 0; k--)
                f[u][j] = max(f[u][j], f[u][j - k - 1] + f[v][k] + e[i].w);
    }
}

int main()
{
    read(n, q);
    for (int i = 1; i < n; i++)
    {
        int u, v, w;
        read(u, v, w);
        addedge(u, v, w);
        addedge(v, u, w);
    }
    dfs(1, -1);
    printf("%d\n", f[1][q]);
    return 0;
}