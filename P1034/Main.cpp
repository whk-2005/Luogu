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
typedef pair<int, int> pii;

struct mat
{
    int l, r, u, d;
    bool flag;
} p[10];
int n, m;
pii a[510];
int ans = 0x7fffffff;

bool in(mat a, int first, int second)
{
    if (first >= a.l && first <= a.r && second >= a.d && second <= a.u)
        return 1;
    return 0;
}

bool check(mat a, mat b)
{
    if (in(a, b.l, b.u))
        return 1;
    if (in(a, b.l, b.d))
        return 1;
    if (in(a, b.r, b.u))
        return 1;
    if (in(a, b.r, b.d))
        return 1;
    return 0;
}

void dfs(int num)
{
    int val = 0;
    for (int i = 1; i <= m; i++)
    {
        if (p[i].flag)
            for (int j = i + 1; j <= m; j++)
                if (p[i].flag && check(p[i], p[j]))
                    return;
        val += (p[i].r - p[i].l) * (p[i].u - p[i].d);
    }
    if (val > ans)
        return;
    if (num > n)
    {
        ans = val;
        return;
    }
    for (int i = 1; i <= m; i++)
    {
        mat tmp = p[i];
        if (p[i].flag == 0)
        {
            p[i].flag = 1;
            p[i].l = p[i].r = a[num].first;
            p[i].u = p[i].d = a[num].second;
            dfs(num + 1);
            p[i] = tmp;
            break;
        }
        else
        {
            p[i].r = max(p[i].r, a[num].first);
            p[i].l = min(p[i].l, a[num].first);
            p[i].u = max(p[i].u, a[num].second);
            p[i].d = min(p[i].d, a[num].second);
            dfs(num + 1);
            p[i] = tmp;
        }
    }
}

int main()
{
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; i++)
        scanf("%d%d", &a[i].first, &a[i].second);
    dfs(1);
    printf("%d\n", ans);
    return 0;
}