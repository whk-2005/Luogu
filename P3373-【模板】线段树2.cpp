#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const int MAXN = 100000;
struct node
{
    ll val;
    ll l, r;
    ll lazy1, lazy2; //乘法，加法
    ll len;
} tree[800010];
int n, m, p;
int val[MAXN + 10];
int mode, x, y, k;

void build(int root, int l, int r)
{
    tree[root].l = l;
    tree[root].r = r;
    tree[root].lazy1 = 1;
    tree[root].lazy2 = 0;
    if (l == r)
    {
        tree[root].val = val[l] % p;
        return;
    }
    int mid = (l + r) >> 1;
    build(root << 1, l, mid);
    build(root << 1 | 1, mid + 1, r);
    tree[root].val = (tree[root << 1].val + tree[root << 1 | 1].val) % p;
}

void pushdown(int root)
{
    tree[root << 1].lazy2 = (tree[root].lazy2 + tree[root << 1].lazy2 * tree[root].lazy1) % p;
    tree[root << 1 | 1].lazy2 = (tree[root].lazy2 + tree[root << 1 | 1].lazy2 * tree[root].lazy1) % p;
    tree[root << 1].lazy1 = (tree[root << 1].lazy1 * tree[root].lazy1) % p;
    tree[root << 1 | 1].lazy1 = (tree[root << 1 | 1].lazy1 * tree[root].lazy1) % p;
    tree[root << 1].val = (tree[root << 1].val * tree[root].lazy1 + (tree[root << 1].r - tree[root << 1].l + 1) * tree[root].lazy2) % p;
    tree[root << 1 | 1].val = (tree[root << 1 | 1].val * tree[root].lazy1 + (tree[root << 1 | 1].r - tree[root << 1 | 1].l + 1) * tree[root].lazy2) % p;
    tree[root].lazy1 = 1;
    tree[root].lazy2 = 0;
}

ll query(int root, int l, int r)
{
    pushdown(root);
    if (tree[root].l >= l && tree[root].r <= r)
        return tree[root].val % p;
    if (tree[root].r < l || tree[root].l > r)
        return 0;
    return (query(root << 1, l, r) + query(root << 1 | 1, l, r)) % p;
}

void update(int root, int l, int r, int addval, int typ)
{
    pushdown(root);
    if (typ == 1 && tree[root].l >= l && tree[root].r <= r)
    {
        tree[root].lazy1 = (tree[root].lazy1 * addval) % p;
        tree[root].lazy2 = (tree[root].lazy2 * addval) % p;
        tree[root].val = (tree[root].val * tree[root].lazy1) % p;
        return;
    }
    if (typ == 2 && tree[root].l >= l && tree[root].r <= r)
    {
        tree[root].lazy2 = (tree[root].lazy2 + addval) % p;
        tree[root].val = (tree[root].val + tree[root].lazy2 * (tree[root].r - tree[root].l + 1)) % p;
        return;
    }
    if (tree[root].r < l || tree[root].l > r)
        return;
    update(root << 1, l, r, addval, typ);
    update(root << 1 | 1, l, r, addval, typ);
    tree[root].val = (tree[root << 1].val + tree[root << 1 | 1].val) % p;
}

int main(int argc, char const *argv[])
{
    scanf("%d%d%d", &n, &m, &p);
    for (int i = 1; i <= n; i++)
        scanf("%d", &val[i]);
    build(1, 1, n);
    while (m--)
    {
        scanf("%d", &mode);
        if (mode == 1)
        {
            scanf("%d%d%d", &x, &y, &k);
            update(1, x, y, k, 1);
        }
        if (mode == 2)
        {
            scanf("%d%d%d", &x, &y, &k);
            update(1, x, y, k, 2);
        }
        if (mode == 3)
        {
            scanf("%d%d", &x, &y);
            printf("%lld\n", query(1, x, y));
        }
    }
    return 0;
}
