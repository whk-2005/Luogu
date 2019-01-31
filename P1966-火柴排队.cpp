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

const int MAXN = 1e5 + 10;
const int MOD = 99999997;
int n;
int a[MAXN], b[MAXN];
int c[MAXN], d[MAXN];
int q[MAXN];
int ans;

struct Fenwick_Tree
{
    int tree[MAXN];

    Fenwick_Tree() { memset(tree, 0, sizeof(tree)); }

    inline int lowbit(int x) { return x & (-x); }

    inline void add(int id, int val)
    {
        while (id <= n)
        {
            tree[id] += val;
            id += lowbit(id);
        }
    }

    inline int query(int id)
    {
        int sum = 0;
        while (id >= 1)
        {
            sum += tree[id];
            id -= lowbit(id);
        }
        return sum;
    }
} Tree;

inline bool cmp1(int i, int j) { return a[i] < a[j]; }
inline bool cmp2(int i, int j) { return b[i] < b[j]; }

int main()
{
    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
        scanf("%d", &a[i]), c[i] = i;
    for (int i = 1; i <= n; i++)
        scanf("%d", &b[i]), d[i] = i;
    sort(c + 1, c + n + 1, cmp1);
    sort(d + 1, d + n + 1, cmp2);
    for (int i = 1; i <= n; i++)
        q[c[i]] = d[i];
    for (int i = n; i >= 1; i--)
    {
        ans += Tree.query(q[i] - 1);
        Tree.add(q[i], 1);
        if (ans >= MOD)
            ans -= MOD;
    }
    printf("%d\n", ans);
    return 0;
}