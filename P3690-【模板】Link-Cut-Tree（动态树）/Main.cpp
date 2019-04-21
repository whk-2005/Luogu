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

const int N = 300010;

int n, m, opt, x, y, xx, yy;
int val[N];
struct Link_Cut_Tree
{
    int top, c[N][2], fa[N], xr[N], q[N], rev[N];

#define lc(x) c[x][0]
#define rc(x) c[x][1]

    inline void pushup(int x)
    {
        xr[x] = xr[lc(x)] ^ xr[rc(x)] ^ val[x];
    }

    inline void pushdown(int x)
    {
        if (rev[x])
        {
            rev[lc(x)] ^= 1;
            rev[rc(x)] ^= 1;
            rev[x] ^= 1;
            swap(lc(x), rc(x));
        }
    }

    inline bool isroot(int x) { return lc(fa[x]) != x && rc(fa[x]) != x; }

    inline void rotate(int x)
    {
        int y = fa[x], z = fa[y], l, r;
        if (lc(y) == x)
            l = 0;
        else
            l = 1;
        r = l ^ 1;
        if (!isroot(y))
        {
            if (lc(z) == y)
                lc(z) = x;
            else
                rc(z) = x;
        }
        fa[x] = z;
        fa[y] = x;
        fa[c[x][r]] = y;
        c[y][l] = c[x][r];
        c[x][r] = y;
        pushup(y);
        pushup(x);
    }

    inline void splay(int x)
    {
        top = 1;
        q[top] = x;
        for (int i = x; !isroot(i); i = fa[i])
            q[++top] = fa[i];
        for (int i = top; i; i--)
            pushdown(q[i]);
        while (!isroot(x))
        {
            int y = fa[x], z = fa[y];
            if (!isroot(y))
            {
                if ((lc(y) == x) ^ (lc(z) == y))
                    rotate(x);
                else
                    rotate(y);
            }
            rotate(x);
        }
    }

    inline void access(int x)
    {
        for (int i = 0; x; i = x, x = fa[x])
            splay(x), rc(x) = i, pushup(x);
    }

    inline void makeroot(int x)
    {
        access(x);
        splay(x);
        rev[x] ^= 1;
    }

    inline int find(int x)
    {
        access(x);
        splay(x);
        while (lc(x))
            x = lc(x);
        return x;
    }

    inline void split(int x, int y)
    {
        makeroot(x);
        access(y);
        splay(y);
    }

    inline void cut(int x, int y)
    {
        split(x, y);
        if (lc(y) == x && rc(x) == 0)
            lc(y) = 0, fa[x] = 0;
    }

    inline void link(int x, int y)
    {
        makeroot(x);
        fa[x] = y;
    }
} T;

int main()
{
    read(n, m);
    for (int i = 1; i <= n; i++)
        read(val[i]), T.xr[i] = val[i];
    while (m--)
    {
        read(opt, x, y);
        if (opt == 0)
        {
            T.split(x, y);
            printf("%d\n", T.xr[y]);
        }
        if (opt == 1)
        {
            xx = T.find(x);
            yy = T.find(y);
            if (xx != yy)
                T.link(x, y);
        }
        if (opt == 2)
        {
            xx = T.find(x);
            yy = T.find(y);
            if (xx == yy)
                T.cut(x, y);
        }
        if (opt == 3)
        {
            T.access(x);
            T.splay(x);
            val[x] = y;
            T.pushup(x);
        }
    }
    return 0;
}