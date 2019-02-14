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

const int MAXN = 200010;

int MOD;
int a[MAXN], b[MAXN];

struct Segment_Tree
{
    struct Node
    {
        int val;
        int len;
        int lazy;
        int l, r;
    } tree[MAXN];

    inline void build(int root, int l, int r)
    {
        int mid;
        tree[root].lazy = 0;
        tree[root].l = l;
        tree[root].r = r;
        tree[root].len = r - l + 1;
        if (l == r)
            tree[root].val = a[l];
        else
        {
            mid = (l + r) / 2;
            build(root * 2, l, mid);
            build(root * 2 + 1, mid + 1, r);
            tree[root].val = (tree[root * 2].val + tree[root * 2 + 1].val) % MOD;
        }
    }

    inline void pushdown(int root)
    {
        if (tree[root].lazy)
        {
            tree[root * 2].lazy += tree[root].lazy;
            tree[root * 2 + 1].lazy += tree[root].lazy;
            tree[root * 2].val += tree[root * 2].len * tree[root].lazy;
            tree[root * 2 + 1].val += tree[root * 2 + 1].len * tree[root].lazy;
            tree[root].lazy = 0;
        }
    }

    inline void add(int root, int id, int addval)
    {
        int mid;
        if (tree[root].l == tree[root].r)
        {
            tree[root].val += addval;
            return;
        }
        else
        {
            mid = (tree[root].l + tree[root].r) / 2;
            if (id <= mid)
                add(root * 2, id, addval);
            else
                add(root * 2 + 1, id, addval);
            tree[root].val = (tree[root * 2].val + tree[root * 2 + 1].val) % MOD;
        }
    }

    int query(int root, int l, int r)
    {
        int mid;
        if (tree[root].l >= l && tree[root].r <= r)
            return tree[root].val;
        if (tree[root].l > r || tree[root].r < l)
            return 0;
        if (tree[root].lazy)
            pushdown(root);
        return (query(root * 2, l, r) + query(root * 2 + 1, l, r)) % MOD;
    }

    inline void update(int root, int l, int r, int addval)
    {
        int mid;
        if (tree[root].l >= l && tree[root].r <= r)
        {
            tree[root].lazy += addval;
            tree[root].val += tree[root].len * addval;
            return;
        }
        if (tree[root].l > r || tree[root].r < l)
            return;
        if (tree[root].lazy)
            pushdown(root);
        update(root * 2, l, r, addval);
        update(root * 2 + 1, l, r, addval);
        tree[root].val = (tree[root * 2].val + tree[root * 2 + 1].val) % MOD;
    }
} st;

struct Adjacency_Table
{
    int head[MAXN];
    int tot;
    struct Edge
    {
        int u, v, nxt;
    } edge[MAXN];

    inline void add(int u, int v)
    {
        edge[++tot].u = u;
        edge[tot].v = v;
        edge[tot].nxt = head[u];
        head[u] = tot;
    }
} at;

struct Tree_Chain_Split
{
    int deep[MAXN], fa[MAXN], son[MAXN];
    int tot[MAXN], top[MAXN], idx[MAXN];
    int cnt;

    inline int dfs1(int now, int f, int dep)
    {
        deep[now] = dep;
        fa[now] = f;
        tot[now] = 1;
        int maxc = -1;
        for (int i = at.head[now]; i; i = at.edge[i].nxt)
        {
            if (at.edge[i].v == f)
                continue;
            tot[now] += dfs1(at.edge[i].v, now, dep + 1);
            if (tot[at.edge[i].v] > maxc)
                maxc = tot[at.edge[i].v], son[now] = at.edge[i].v;
        }
        return tot[now];
    }

    inline void dfs2(int now, int topf)
    {
        idx[now] = ++cnt;
        a[cnt] = b[now];
        top[now] = topf;
        if (!son[now])
            return;
        dfs2(son[now], topf);
        for (int i = at.head[now]; i; i = at.edge[i].nxt)
            if (!idx[at.edge[i].v])
                dfs2(at.edge[i].v, at.edge[i].v);
    }

    inline void add(int x, int y, int val)
    {
        while (top[x] != top[y])
        {
            if (deep[top[x]] < deep[top[y]])
                swap(x, y);
            st.update(1, idx[top[x]], idx[x], val);
            x = fa[top[x]];
        }
        if (deep[x] > deep[y])
            swap(x, y);
        st.update(1, idx[x], idx[y], val);
    }

    inline int sum(int x, int y)
    {
        int ans = 0;
        while (top[x] != top[y])
        {
            if (deep[top[x]] < deep[top[y]])
                swap(x, y);
            ans = (ans + st.query(1, idx[top[x]], idx[x])) % MOD;
            x = fa[top[x]];
        }
        if (deep[x] > deep[y])
            swap(x, y);
        ans = (ans + st.query(1, idx[x], idx[y])) % MOD;
        return ans;
    }
} tcs;

int n, m, root;

int main()
{
    read(n), read(m), read(root), read(MOD);
    for (int i = 1; i <= n; i++)
        read(b[i]);
    for (int i = 1; i <= n - 1; i++)
    {
        int x, y;
        read(x), read(y);
        at.add(x, y), at.add(y, x);
    }
    tcs.dfs1(root, 0, 1);
    tcs.dfs2(root, root);
    st.build(1, 1, n);
    while (m--)
    {
        int opt, x, y, z;
        read(opt);
        if (opt == 1)
        {
            read(x), read(y), read(z);
            z %= MOD;
            tcs.add(x, y, z);
        }
        if (opt == 2)
        {
            read(x), read(y);
            printf("%d\n", tcs.sum(x, y));
        }
        if (opt == 3)
        {
            read(x), read(z);
            z %= MOD;
            st.update(1, tcs.idx[x], tcs.idx[x] + tcs.tot[x] - 1, z);
        }
        if (opt == 4)
        {
            read(x);
            printf("%d\n", st.query(1, tcs.idx[x], tcs.idx[x] + tcs.tot[x] - 1));
        }
    }
    return 0;
}