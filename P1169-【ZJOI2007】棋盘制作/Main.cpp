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

template <typename T>
inline void read(T &num)
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

const int MAXN = 2010;

int n, m;
int g[MAXN][MAXN], l[MAXN][MAXN], r[MAXN][MAXN], u[MAXN][MAXN];
int ans1, ans2;

int main()
{
    read(n), read(m);
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++)
        {
            read(g[i][j]);
            l[i][j] = r[i][j] = j;
            u[i][j] = 1;
        }
    for (int i = 1; i <= n; i++)
        for (int j = 2; j <= m; j++)
            if (g[i][j] != g[i][j - 1])
                l[i][j] = l[i][j - 1];
    for (int i = 1; i <= n; i++)
        for (int j = m - 1; j >= 1; j--)
            if (g[i][j] != g[i][j + 1])
                r[i][j] = r[i][j + 1];
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++)
        {
            if (i > 1 && g[i][j] != g[i - 1][j])
            {
                l[i][j] = max(l[i][j], l[i - 1][j]);
                r[i][j] = min(r[i][j], r[i - 1][j]);
                u[i][j] = u[i - 1][j] + 1;
            }
            int a = r[i][j] - l[i][j] + 1;
            int b = min(a, u[i][j]);
            ans1 = max(ans1, b * b);
            ans2 = max(ans2, a * u[i][j]);
        }
    printf("%d\n%d\n", ans1, ans2);
    return 0;
}