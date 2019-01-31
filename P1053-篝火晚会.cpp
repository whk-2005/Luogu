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

const int MAXN = 50010;
int n;
int a[MAXN], b[MAXN];
int x[MAXN], y[MAXN];
int ans;

int main()
{
    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
        scanf("%d%d", &a[i], &b[i]);
    x[1] = 1;
    x[2] = a[1];
    for (int i = 1; i <= n; i++)
    {
        if (b[a[i]] != i && a[a[i]] != i || a[b[i]] != i && b[b[i]] != i)
            return printf("-1\n"), 0;
        if (a[x[i]] == x[i - 1])
            x[i + 1] = b[x[i]];
        else
            x[i + 1] = a[x[i]];
    }
    ans = 0x7fffffff;
    for (int i = 1; i <= n; i++)
    {
        y[(i - x[i] + n) % n]++;
        ans = min(ans, n - y[(i - x[i] + n) % n]);
    }
    memset(x, 0, sizeof(x));
    memset(y, 0, sizeof(y));
    x[0] = 1;
    x[1] = b[1];
    for (int i = 1; i <= n; i++)
    {
        if (b[x[i]] == x[i - 1])
            x[i + 1] = a[x[i]];
        else
            x[i + 1] = b[x[i]];
    }
    for (int i = 1; i <= n; i++)
    {
        y[(i - x[i] + n) % n]++;
        ans = min(ans, n - y[(i - x[i] + n) % n]);
    }
    printf("%d\n", ans);
    return 0;
}