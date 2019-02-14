// 在写之前声明一下，我可能有生之年写不完了...

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

int n, m, l, r;

struct Splay
{
    const int MAX = 200000;

    struct node
    {
#define lc ch[0]
#define rc ch[1]
#define fa father
        int father, ch[2];
        int val, size, mark;
        node() {}
        node(int x, int f)
        {
            lc = rc = 0;
            size = 1;
            val = x;
            fa = f;
        }
    } t[200010];
    // Splay... 我可以把用户名从 hello_world2005 改成 bye_world2019 了

    int root, tot;

    inline void pushup(int x) { t[x].size = t[t[x].lc].size + t[t[x].rc].size + 1; }

    inline void pushdown(int x)
    {
        if (t[x].mark)
        {
            t[t[x].lc].mark ^= 1;
            t[t[x].rc].mark ^= 1;
            t[x].mark = 0;
            swap(t[x].lc, t[x].rc);
        }
    }

    inline void rotate(int x)
    {
        int y = t[x].fa;
        int z = t[y].fa;
        int k = t[y].rc == x;
        t[z].ch[t[z].rc == y] = x;
        t[x].fa = z;
        t[y].ch[k] = t[x].ch[k ^ 1];
        t[t[x].ch[k ^ 1]].fa = y;
        t[x].ch[k ^ 1] = y;
        t[y].fa = x;
        pushup(y);
        pushup(x);
    }

    inline void splay(int x, int g)
    {
        while (t[x].fa != g)
        {
            int y = t[x].fa;
            int z = t[y].fa;
            if (z != g)
                (t[z].rc == y) ^ (t[y].rc == x) ? rotate(x) : rotate(y);
            rotate(x);
        }
        if (g == 0)
            root = x;
    }

    inline void insert(int x)
    {
        int u = root, ff = 0;
        while (u)
        {
            ff = u;
            u = t[u].ch[x > t[u].val];
        }
        u = ++tot;
        if (ff)
            t[ff].ch[x > t[ff].val] = u;
        t[u] = node(x, ff);
        splay(u, 0);
    }

    inline int rank(int k)
    {
        int u = root;
        while (1)
        {
            pushdown(u);
            if (t[t[u].lc].size >= k)
                u = t[u].lc;
            else if (t[t[u].lc].size + 1 == k)
                return u;
            else
                k -= t[t[u].lc].size + 1, u = t[u].rc;
        }
    }
} T;

inline void print(int u)
{
    T.pushdown(u);
    if (T.t[u].lc)
        print(T.t[u].lc);
    if (T.t[u].val > 1 && T.t[u].val < n + 2)
        printf("%d ", T.t[u].val - 1);
    if (T.t[u].rc)
        print(T.t[u].rc);
}

inline void work(int l, int r)
{
    l = T.rank(l);
    r = T.rank(r + 2);
    T.splay(l, 0);
    T.splay(r, l);
    T.t[T.t[T.t[T.root].rc].lc].mark ^= 1;
}

int main()
{
    read(n), read(m);
    for (int i = 1; i <= n + 2; i++)
        T.insert(i);
    while (m--)
    {
        read(l), read(r);
        work(l, r);
    }
    print(T.root);
    printf("\n");
    return 0;
}