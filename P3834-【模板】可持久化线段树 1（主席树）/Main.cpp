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

const int N = 200010;

int n, q, m;
int cnt;
int a[N], b[N], t[N];
int sum[N << 5], tl[N << 5], tr[N << 5];
int x, y, z;

#define mid ((l + r) >> 1)

inline int build(int l, int r)
{
    int rt = ++cnt;
    sum[rt] = 0;
    if (l < r)
    {
        tl[rt] = build(l, mid);
        tr[rt] = build(mid + 1, r);
    }
    return rt;
}

inline int update(int pre, int l, int r, int x)
{
    int rt = ++cnt;
    tl[rt] = tl[pre]; 
    tr[rt] = tr[pre]; 
    sum[rt] = sum[pre] + 1;
    if (l < r)
    {
        if (x <= mid) 
            tl[rt] = update(tl[pre], l, mid, x);
        else 
            tr[rt] = update(tr[pre], mid + 1, r, x);
    }
    return rt;
}

inline int query(int u, int v, int l, int r, int k)
{
    if (l >= r) 
        return l;
    int x = sum[tl[v]] - sum[tl[u]];
    if (x >= k) 
        return query(tl[u], tl[v], l, mid, k);
    else 
        return query(tr[u], tr[v], mid + 1, r, k - x);
}

int main()
{
    read(n), read(q);
    for (int i = 1; i <= n; i++)
    {
        read(a[i]);
        b[i] = a[i];
    }
    sort(b + 1, b + n + 1);
    m = unique(b + 1, b + n + 1) - b - 1;
    t[0] = build(1, m);
    for (int i = 1; i <= n; i++)
    {
        int tmp = lower_bound(b + 1, b + m + 1, a[i]) - b;
        t[i] = update(t[i - 1], 1, m, tmp);
    }
    while (q--)
    {
        read(x), read(y), read(z);
        int tmp = query(t[x - 1], t[y], 1, m, z);
        printf("%d\n", b[tmp]);
    }
    return 0;
}