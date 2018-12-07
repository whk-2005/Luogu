#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
const int MAXN = 500000;
struct node
{
    ll val;
    ll l, r;
} tree[MAXN * 4 + 10];
ll arr[MAXN + 10];
int n, m;
int f, x, y;

void build(int root, int l, int r)
{
    tree[root] = node{0, l, r};
    if (l == r)
    {
        tree[root].val = arr[l];
        return;
    }
    int m = (l + r) >> 1;
    build(root << 1, l, m);
    build(root << 1 | 1, m + 1, r);
    tree[root].val = tree[root << 1].val + tree[root << 1 | 1].val;
}

void add(int root, int pos, int val)
{
    if (tree[root].l == tree[root].r)
    {
        tree[root].val += val;
        return;
    }
    int m = (tree[root].l + tree[root].r) >> 1;
    if (pos < m)
        add(root << 1, pos, val);
    else
        add(root << 1 | 1, pos, val);
    tree[root].val = tree[root << 1].val + tree[root << 1 | 1].val;
}

ll query(int root, int l, int r)
{
    if (tree[root].l >= l && tree[root].r <= r)
        return tree[root].val;
    if (tree[root].l > r || tree[root].r < l)
        return 0;
    return query(root << 1, l, r) + query(root << 1 | 1, l, r);
}

void print(int root, int l, int r)
{
    if (l == r)
    {
        printf("%lld ", tree[root]);
        return;
    }
    int m = (l + r) >> 1;
    print(root << 1, l, m);
    print(root << 1 | 1, m + 1, r);
}

int main(int argc, char const *argv[])
{
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; i++)
        scanf("%lld", &arr[i]);
    build(1, 1, n);
    while (m--)
    {
        scanf("%d%d%d", &f, &x, &y);
        if (f == 1)
            add(1, x - 1, y);
        if (f == 2)
            printf("%lld\n", query(1, x, y));
        // print(1, 1, n);
        // printf("\n");
    }
    return 0;
}