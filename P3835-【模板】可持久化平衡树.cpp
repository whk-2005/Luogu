#include <algorithm>
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

class FHQ_Treap
{
  public:
    struct node
    {
        int l, r;
        int size, rnd, v;
    } t[500010 * 50];
    int cnt, rt[500010];

    inline void update(int k)
    {
        t[k].size = t[t[k].l].size + t[t[k].r].size + 1;
    }

    inline void newnode(int &k, int x)
    {
        t[k = ++cnt].v = x;
        t[k].size = 1;
        t[k].rnd = rand();
    }

    inline int merge(int a, int b)
    {
        if (!a || !b)
            return a + b;
        if (t[a].rnd > t[b].rnd)
        {
            int p = ++cnt;
            t[p] = t[a];
            t[p].r = merge(t[p].r, b);
            update(p);
            return p;
        }
        else
        {
            int p = ++cnt;
            t[p] = t[b];
            t[p].l = merge(a, t[p].l);
            update(p);
            return p;
        }
    }

    inline void split(int now, int k, int &x, int &y)
    {
        if (!now)
            x = y = 0;
        else
        {
            if (t[now].v <= k)
            {
                x = ++cnt;
                t[x] = t[now];
                split(t[x].r, k, t[x].r, y);
                update(x);
            }
            else
            {
                y = ++cnt;
                t[y] = t[now];
                split(t[y].l, k, x, t[y].l);
                update(y);
            }
        }
    }

    inline void pop(int &root, int w)
    {
        int x = 0, y = 0, z = 0;
        split(root, w, x, z);
        split(x, w - 1, x, y);
        y = merge(t[y].l, t[y].r);
        root = merge(merge(x, y), z);
    }

    inline void push(int &root, int w)
    {
        int x = 0, y = 0, z = 0;
        split(root, w, x, y);
        newnode(z, w);
        root = merge(merge(x, z), y);
    }

    inline int rank(int k, int w)
    {
        if (w == t[t[k].l].size + 1)
            return t[k].v;
        else if (w <= t[t[k].l].size)
            return rank(t[k].l, w);
        else
            return rank(t[k].r, w - t[t[k].l].size - 1);
    }

    inline int atrank(int &root, int w)
    {
        int x, y;
        split(root, w - 1, x, y);
        int ans = t[x].size + 1;
        root = merge(x, y);
        return ans;
    }

    inline int pre(int &root, int w)
    {
        int x, y, k, ans;
        split(root, w - 1, x, y);
        if (!x)
            return -2147483647;
        k = t[x].size;
        ans = rank(x, k);
        root = merge(x, y);
        return ans;
    }

    inline int nxt(int &root, int w)
    {
        int x, y, ans;
        split(root, w, x, y);
        if (!y)
            return 2147483647;
        else
            ans = rank(y, 1);
        root = merge(x, y);
        return ans;
    }
} Tree;
int n, v, o, x;

int main()
{
    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
    {
        scanf("%d%d%d", &v, &o, &x);
        Tree.rt[i] = Tree.rt[v];
        if (o == 1)
            Tree.push(Tree.rt[i], x);
        if (o == 2)
            Tree.pop(Tree.rt[i], x);
        if (o == 3)
            printf("%d\n", Tree.rank(Tree.rt[i], x));
        if (o == 4)
            printf("%d\n", Tree.atrank(Tree.rt[i], x));
        if (o == 5)
            printf("%d\n", Tree.pre(Tree.rt[i], x));
        if (o == 6)
            printf("%d\n", Tree.nxt(Tree.rt[i], x));
    }
    return 0;
}