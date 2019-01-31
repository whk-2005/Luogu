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

#define int long long

const int maxn = 200010;

int n, m, s;
int r = 0, l = 214748364, mid;
int ans = 999999999999999, sum;
int w[maxn], v[maxn], _r[maxn], _l[maxn];
int pv[maxn], pn[maxn];

inline bool check(int x)
{
    memset(pv, 0, sizeof(pv));
    memset(pn, 0, sizeof(pn));
    for (int i = 1; i <= n; i++)
        if (w[i] >= x)
        {
            pv[i] = pv[i - 1] + v[i];
            pn[i] = pn[i - 1] + 1;
        }
        else
        {
            pv[i] = pv[i - 1];
            pn[i] = pn[i - 1];
        }
    int y = 0;
    for (int i = 1; i <= m; i++)
        y += (pn[_r[i]] - pn[_l[i] - 1]) * (pv[_r[i]] - pv[_l[i] - 1]);
    sum = abs(y - s);
    if (y > s)
        return 1;
    return 0;
}

signed main()
{
    scanf("%lld%lld%lld", &n, &m, &s);
    for (int i = 1; i <= n; i++)
        scanf("%lld%lld", &w[i], &v[i]), r = max(r, w[i]), l = min(l, w[i]);
    for (int i = 1; i <= m; i++)
        scanf("%lld%lld", &_l[i], &_r[i]);
    l -= 1, r += 1;
    while (l <= r)
    {
        mid = (l + r) >> 1;
        if (check(mid))
            l = mid + 1;
        else
            r = mid - 1;
        ans = min(ans, sum);
    }
    ans = min(ans, sum);
    printf("%lld", ans);
    return 0;
}