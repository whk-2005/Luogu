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

const int MAXN = 20;

int n;
int c[MAXN], p[MAXN], l[MAXN];
int maxx;

int exgcd(int a, int b, int &x, int &y)
{
    if (b == 0)
    {
        x = 1;
        y = 0;
        return a;
    }
    int d = exgcd(b, a % b, y, x);
    y -= a / b * x;
    return d;
}

int main()
{
    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
    {
        scanf("%d %d %d", &c[i], &p[i], &l[i]);
        maxx = max(maxx, c[i]);
    }
    for (int ans = maxx;; ans++)
    {
        bool flag = 0;
        for (int i = 1; i <= n; i++)
        {
            for (int j = i + 1; j <= n; j++)
            {
                int x, y;
                int lo = p[i] - p[j];
                lo = (lo % ans + ans) % ans;
                int g = exgcd(lo, ans, x, y);
                if ((c[j] - c[i]) % g)
                    continue;
                x *= (c[j] - c[i]) / g;
                int mod = ans / g;
                x = (x % mod + mod) % mod;
                if (x <= min(l[i], l[j]))
                {
                    flag = 1;
                    break;
                }
            }
            if (flag)
                break;
        }
        if (flag)
            continue;
        printf("%d\n", ans);
        break;
    }
    return 0;
}