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

const int N = 10010;
const int M = 400010;

int n, m;
map<string, int> cou; // couple

struct node
{
    int v, to;
} e[M];
int tot, h[N];
bool ins[N];
int s[N], top;
int cnt, belong[N];
int dfn[N], low[N], dep;
string g, b;

void addedge(int u, int v)
{
    e[++tot].v = v;
    e[tot].to = h[u];
    h[u] = tot;
}

void tarjan(int u)
{
    dfn[u] = low[u] = ++dep;
    s[++top] = u;
    ins[u] = 1;
    for (int i = h[u]; i; i = e[i].to)
    {
        int v = e[i].v;
        if (!dfn[v])
        {
            tarjan(v);
            low[u] = min(low[u], low[v]);
        }
        else if (ins[v])
            low[u] = min(low[u], dfn[v]);
    }
    if (low[u] == dfn[u])
    {
        ++cnt;
        do
        {
            belong[s[top]] = cnt;
            ins[s[top]] = 0;
        } while (s[top--] != u);
    }
}

int main()
{
    cin >> n;
    for (int i = 1; i <= n; ++i)
    {
        cin >> g >> b;
        cou[g] = i;
        cou[b] = i + n;
        addedge(i, i + n);
    }
    cin >> m;
    for (int i = 1; i <= m; ++i)
    {
        cin >> g >> b;
        addedge(cou[b], cou[g]);
    }
    for (int i = 1; i <= n * 2; ++i)
        if (!dfn[i])
            tarjan(i);
    for (int i = 1; i <= n; ++i)
    {
        if (belong[i] == belong[i + n])
            cout << "Unsafe" << endl;
        else
            cout << "Safe" << endl;
    }
    return 0;
}