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
void read(T &num)
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
void read(T &num, Args &... args) { read(num), read(args...); }

const int N = 50010;
const int INF = 0x3f3f3f3f;

int n, m;
int to[N], nxt[N], w[N], dis[N];
int cnt, h[N], tot[N];
bool vis[N];
int f, a, b, c;

void add(int u, int v, int c)
{
    to[++cnt] = v;
    nxt[cnt] = h[u];
    h[u] = cnt;
    w[cnt] = c;
}

bool spfa(int u)
{
    vis[u] = 1;
    for (int i = h[u]; i; i = nxt[i])
        if (dis[to[i]] < dis[u] + w[i])
        {
            dis[to[i]] = dis[u] + w[i];
            if (vis[to[i]])
                return 0;
            if (!spfa(to[i]))
                return 0;
        }
    vis[u] = 0;
    return 1;
}

int main()
{
    read(n, m);
    while (m--)
    {
        read(f, a, b);
        if (f == 1)
            read(c), add(b, a, c);
        else if (f == 2)
            read(c), add(a, b, -c);
        else if (f == 3)
            add(a, b, 0), add(b, a, 0);
    }
    for (int i = 1; i <= n; i++)
        add(0, i, 0), dis[i] = -INF;
    if (!spfa(0))
        puts("No");
    else
        puts("Yes");
    return 0;
}