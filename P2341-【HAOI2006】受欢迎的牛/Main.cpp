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

const int MAXN = 1000010;

struct EDGE
{
    int next, to;
} edge[MAXN * 20];
int head[MAXN * 20];
int dfn[MAXN], low[MAXN];
int indgr[MAXN], id[MAXN], all[MAXN];
bool instack[MAXN];
int cnt, tot, gg;
int n, m;
stack<int> s;

inline void add(int x, int y)
{
    cnt++;
    edge[cnt].to = y;
    edge[cnt].next = head[x];
    head[x] = cnt;
}

void tarjan(int x)
{
    dfn[x] = low[x] = ++tot;
    s.push(x);
    instack[x] = 1;
    for (int i = head[x]; i; i = edge[i].next)
    {
        int u = edge[i].to;
        if (!dfn[u])
        {
            tarjan(u);
            low[x] = min(low[x], low[u]);
        }
        else if (instack[u])
            low[x] = min(low[x], dfn[u]);
    }
    int k;
    if (low[x] == dfn[x])
    {
        ++gg;
        do
        {
            k = s.top();
            s.pop();
            instack[k] = 0;
            id[k] = gg;
            all[gg]++;
        } while (x != k);
    }
}

int main()
{
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= m; i++)
    {
        int a, b;
        scanf("%d%d", &a, &b);
        add(a, b);
    }
    for (int i = 1; i <= n; i++)
        if (!dfn[i])
            tarjan(i);
    for (int w = 1; w <= n; w++)
    {
        for (int i = head[w]; i; i = edge[i].next)
        {
            int u = edge[i].to;
            if (id[w] != id[u])
            {
                indgr[id[w]]++;
            }
        }
    }
    int t = 0;
    for (int i = 1; i <= gg; i++)
        if (!indgr[i])
        {
            if (t)
            {
                puts("0");
                return 0;
            }
            t = i;
        }
    printf("%d\n", all[t]);
    return 0;
}