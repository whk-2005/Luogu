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

const int MAXN = 1010;
const int MAXM = 10010;
const int MAXK = 100010;

int n, m, k;
int d[MAXN];
int l[MAXM], s[MAXM], e[MAXM];
int g[MAXN];
int ans;

struct node
{
    int t, s, e;
} a[MAXM];

inline void work(int k)
{
    while (k)
    {
        k--;
        g[n] = g[n - 1] = n;
        int maxx = -1, noww;
        for (int i = n - 2; i >= 1; i--)
            if (e[i + 1] <= l[i + 1])
                g[i] = i + 1;
            else
                g[i] = g[i + 1];
        for (int i = 1; i < n; i++)
        {
            int tmp = s[g[i]] - s[i];
            if (tmp > maxx && d[i] > 0)
            {
                maxx = tmp;
                noww = i;
            }
        }
        ans -= maxx;
        d[noww]--;
        for (int i = 2; i <= n; i++)
            e[i] = max(e[i - 1], l[i - 1]) + d[i - 1];
    }
    return;
}

int main()
{
    scanf("%d %d %d", &n, &m, &k);
    for (int i = 1; i < n; i++)
        scanf("%d", &d[i]);
    for (int i = 1; i <= m; i++)
    {
        scanf("%d %d %d", &a[i].t, &a[i].s, &a[i].e);
        l[a[i].s] = max(l[a[i].s], a[i].t);
        s[a[i].e]++;
    }
    e[1] = l[1];
    for (int i = 1; i <= n; i++)
        s[i] += s[i - 1];
    for (int i = 1; i <= n; i++)
        e[i] = max(e[i - 1], l[i - 1]) + d[i - 1];
    for (int i = 1; i <= m; i++)
        ans += e[a[i].e] - a[i].t;
    work(k);
    printf("%d\n", ans);
    return 0;
}