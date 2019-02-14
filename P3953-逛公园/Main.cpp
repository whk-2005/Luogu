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

const int N = 1e5 + 10;

int t, n, m, k, p;
int f[N][60];
int arr[N], dis[N], head1[N], head2[N];
bool in[N][60];
struct edge
{
    int nxt, to, w;
} e[N << 2];
int cnt;

namespace zkw_Segment_Tree
{
int tr[N << 2], sgt;
inline void Set(int n)
{
    sgt = 1;
    while (sgt <= n)
        sgt <<= 1;
    --sgt;
    tr[0] = N - 1;
}
inline void clr()
{
    for (int i = 1; i <= (sgt << 1) + 1; i++)
        tr[i] = 0;
}

inline int cmp(const int &a, const int &b) { return dis[a] < dis[b] ? a : b; }

inline void mdy(int x, int w)
{
    for (int i = x + sgt; dis[tr[i]] > w; i >>= 1)
        tr[i] = x;
    dis[x] = w;
}
inline void del(int x)
{
    tr[x += sgt] = 0;
    x >>= 1;
    while (x)
        tr[x] = cmp(tr[x << 1], tr[x << 1 | 1]), x >>= 1;
}
} // namespace zkw_Segment_Tree

using namespace zkw_Segment_Tree;

inline void addedge(int u, int v, int w, int *headi)
{
    e[++cnt] = (edge){headi[u], v, w};
    headi[u] = cnt;
}

inline void dij()
{
    memset(dis, 9, 4 * (n + 1));
    clr();
    mdy(n, 0);
    for (int i = 1; i <= n; i++)
    {
        int u = tr[1];
        del(u);
        for (int i = head2[u], v; i; i = e[i].nxt)
            if (dis[v = e[i].to] > dis[u] + e[i].w)
                mdy(v, dis[u] + e[i].w);
    }
}

inline void mod(int &a) { a >= p ? a -= p : 0; }

inline int dfs(int u, int k)
{
    if (in[u][k])
        return -1;
    if (f[u][k])
        return f[u][k];
    in[u][k] = 1;
    u == n ? f[u][k] = 1 : 0;
    for (int i = head1[u], v, w, tp; i; i = e[i].nxt)
        if ((tp = dis[v = e[i].to] - dis[u] + e[i].w) <= k)
        {
            if ((w = dfs(v, k - tp)) == -1)
                return f[u][k] = -1;
            mod(f[u][k] += w);
        }
    return in[u][k] = 0, f[u][k];
}

int main()
{
    read(t);
    while (t--)
    {
        memset(f, 0, sizeof(f));
        memset(in, 0, sizeof(in));
        memset(head1, 0, sizeof(head1));
        memset(head2, 0, sizeof(head2));
        read(n, m, k, p);
        Set(n);
        cnt = 0;
        int u, v, w;
        while (m--)
            read(u, v, w), addedge(u, v, w, head1), addedge(v, u, w, head2);
        dij();
        printf("%d\n", dfs(1, k));
    }
    return 0;
}