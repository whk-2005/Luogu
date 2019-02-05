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

const int MAXN = 5010;

int n, m;
int head[MAXN], cnt;
int ans[MAXN], k[MAXN];
int x, y, deep;
bool vis[MAXN];
vector<int> vec[MAXN];
struct EDGE
{
    int u, v, next;
} e[MAXN * 2];

inline void add(int u, int v)
{
    e[cnt].u = u;
    e[cnt].v = v;
    e[cnt].next = head[u];
    head[u] = cnt++;
}

void dfs1(int u, int f)
{
    if (vis[u])
        return;
    vis[u] = 1;
    k[++deep] = u;
    for (int i = 0; i < vec[u].size(); i++)
    {
        int v = vec[u][i];
        if (v == f)
            continue;
        if ((v == y && u == x) || (v == x && u == y))
            continue;
        dfs1(v, u);
    }
}

inline bool check()
{
    for (int i = 1; i <= n; i++)
    {
        if (k[i] == ans[i])
            continue;
        if (k[i] > ans[i])
            return 0;
        else
            return 1;
    }
}

inline void change()
{
    for (int i = 1; i <= n; i++)
        ans[i] = k[i];
}

void dfs2(int u, int f)
{
    if (vis[u])
        return;
    vis[u] = 1;
    ans[++deep] = u;
    for (int i = 0; i < vec[u].size(); i++)
    {
        int v = vec[u][i];
        if (v == f)
            continue;
        dfs2(v, u);
    }
}

int main()
{
    scanf("%d %d", &n, &m);
    for (int i = 1; i <= m; i++)
    {
        int u, v;
        scanf("%d %d", &u, &v);
        vec[u].push_back(v);
        vec[v].push_back(u);
        add(u, v);
        add(v, u);
    }
    for (int i = 1; i <= n; i++)
        sort(vec[i].begin(), vec[i].end());
    if (n == m)
    {
        for (int i = 0; i < cnt; i += 2)
        {
            deep = 0;
            x = e[i].u, y = e[i].v;
            memset(vis, 0, sizeof(vis));
            dfs1(1, -1);
            if (deep < n)
                continue;
            if (ans[1] == 0)
                change();
            else if(check())
                change();
        }
        for (int i = 1; i <= n; i++)
            printf("%d ", ans[i]);
        printf("\n");
        return 0;
    }
    dfs2(1, -1);
    for (int i = 1; i <= n; i++)
        printf("%d ", ans[i]);
    printf("\n");
    return 0;
}