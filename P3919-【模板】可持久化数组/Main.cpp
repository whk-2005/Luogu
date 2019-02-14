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

const int MAXN = 1e6 + 10;

int n, m;
int a[MAXN];
int r[MAXN << 4];

struct Segment_Tree
{
    int lc[MAXN << 4], rc[MAXN << 4];
    int val[MAXN << 4];
    int cnt;

    inline void build(int &rt, int l, int r)
    {
        rt = ++cnt;
        if (l == r)
        {
            val[rt] = a[l];
            return;
        }
        int mid = (l + r) >> 1;
        build(lc[rt], l, mid);
        build(rc[rt], mid + 1, r);
    }

    inline void insert(int &rt, int pre, int l, int r, int q, int v)
    {
        rt = ++cnt;
        lc[rt] = lc[pre];
        rc[rt] = rc[pre];
        val[rt] = val[pre];
        if (l == r)
        {
            val[rt] = v;
            return;
        }
        int mid = (l + r) >> 1;
        if (q <= mid)
            insert(lc[rt], lc[pre], l, mid, q, v);
        else
            insert(rc[rt], rc[pre], mid + 1, r, q, v);
    }

    inline int query(int rt, int l, int r, int q)
    {
        if (l == r)
            return val[rt];
        int mid = (l + r) >> 1;
        if (q <= mid)
            return query(lc[rt], l, mid, q);
        else
            return query(rc[rt], mid + 1, r, q);
    }
} T;

int main()
{
    read(n), read(m);
    for (int i = 1; i <= n; i++)
        read(a[i]);
    T.build(r[0], 1, n);
    for (int i = 1; i <= m; i++)
    {
        int pre, opt, x, v;
        read(pre), read(opt);
        if (opt == 1)
        {
            read(x), read(v);
            T.insert(r[i], r[pre], 1, n, x, v);
        }
        if (opt == 2)
        {
            read(x);
            printf("%d\n", T.query(r[pre], 1, n, x));
            r[i] = r[pre];
        }
    }
    return 0;
}