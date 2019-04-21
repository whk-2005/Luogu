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

const int MAXN = 1000010;

int n, m;

#define lson (tr[x].ch[0])
#define rson (tr[x].ch[1])

struct Splaytree
{
    int w;
    int c, lc, rc;
    int tag, rev;
    int fa, ch[2];
} tr[MAXN];
int stk[MAXN], top;

inline bool isroot(int x) { return tr[tr[x].fa].ch[0] != x && tr[tr[x].fa].ch[1] != x; }

inline void pushdown(int x)
{
    if (tr[x].rev)
    {
        swap(lson, rson);
        swap(tr[lson].lc, tr[lson].rc);
        swap(tr[rson].lc, tr[rson].rc);
        tr[lson].rev ^= 1, tr[rson].rev ^= 1;
        tr[x].rev = 0;
    }
    if (tr[x].tag)
    {
        tr[x].lc = tr[x].rc = tr[x].c = tr[x].tag;
        tr[lson].tag = tr[rson].tag = tr[x].tag;
        tr[x].w = tr[x].tag = 0;
    }
}

inline void pushup(int x)
{
    pushdown(lson);
    pushdown(rson);
    tr[x].w = tr[lson].w + tr[rson].w;
    if (lson)
    {
        tr[x].lc = tr[lson].lc;
        if (tr[x].c != tr[lson].rc)
            tr[x].w++;
    }
    else
        tr[x].lc = tr[x].c;
    if (rson)
    {
        tr[x].rc = tr[rson].rc;
        if (tr[x].c != tr[rson].lc)
            tr[x].w++;
    }
    else
        tr[x].rc = tr[x].c;
}

inline void rotate(int x)
{
    int y = tr[x].fa, z = tr[y].fa;
    int k = tr[y].ch[1] == x;
    if (!isroot(y))
        tr[z].ch[tr[z].ch[1] == y] = x;
    tr[x].fa = z;
    tr[y].ch[k] = tr[x].ch[k ^ 1], tr[tr[x].ch[k ^ 1]].fa = y;
    tr[x].ch[k ^ 1] = y, tr[y].fa = x;
    pushup(y);
}

inline void splay(int x)
{
    stk[top = 1] = x;
    for (int i = x; !isroot(i); i = tr[i].fa)
        stk[++top] = tr[i].fa;
    while (top)
        pushdown(stk[top--]);
    while (!isroot(x))
    {
        int y = tr[x].fa, z = tr[y].fa;
        if (!isroot(y))
            (tr[y].ch[0] == x) ^ (tr[z].ch[0] == y) ? rotate(x) : rotate(y);
        rotate(x);
    }
    pushup(x);
}

inline void access(int x)
{
    for (int y = 0; x; y = x, x = tr[x].fa)
        splay(x), rson = y, pushup(x);
}

inline void makeroot(int x)
{
    access(x);
    splay(x);
    tr[x].rev ^= 1;
}

inline int findroot(int x)
{
    access(x);
    splay(x);
    while (lson)
        x = lson;
    return x;
}

inline void split(int x, int y)
{
    makeroot(x);
    access(y);
    splay(y);
}

inline void link(int x, int y)
{
    makeroot(x);
    tr[x].fa = y;
}

int main()
{
    read(n, m);
    for (int i = 1; i <= n; i++)
        read(tr[i].c), tr[i].lc = tr[i].rc = tr[i].c;
    for (int u, v, i = 1; i < n; i++)
        read(u, v), link(u, v);
    while (m--)
    {
        int a, b, c;
        char ch;
        ch = getchar();
        while (ch != 'C' && ch != 'Q')
            ch = getchar();
        if (ch == 'C')
        {
            read(a, b, c);
            split(a, b);
            tr[b].tag = c;
        }
        if (ch == 'Q')
        {
            read(a, b);
            split(a, b);
            printf("%d\n", tr[b].w + 1);
        }
    }
    return 0;
}