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

inline void read(int &num)
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

const double EPS = 1e-8;

int t, n, m;
int lowbit[1 << 20];
int line[20][20], dp[1 << 20];
double x[20], y[20];

inline void f(double &x, double &y, double a1, double b1, double c1, double a2, double b2, double c2)
{
    y = (a1 * c2 - a2 * c1) / (a1 * b2 - a2 * b1);
    x = (c1 - y * b1) / a1;
}

int main()
{
    for (int i = 0; i < (1 << 18); i++)
    {
        int j = 1;
        for (; j <= 18 && i & (1 << (j - 1)); j++)
            ;
        lowbit[i] = j;
    }
    read(t);
    while (t--)
    {
        memset(line, 0, sizeof(line));
        memset(dp, 0x3f, sizeof(dp));
        dp[0] = 0;
        read(n), read(m);
        for (int i = 1; i <= n; i++)
            scanf("%lf%lf", &x[i], &y[i]);
        for (int i = 1; i <= n; i++)
            for (int j = 1; j <= n; j++)
            {
                // cout << i << ' ' << j << endl;
                if (fabs(x[i] - x[j]) < EPS)
                    continue;
                double a, b;
                f(a, b, x[i] * x[i], x[i], y[i], x[j] * x[j], x[j], y[j]);
                // cout << x[i] << y[i] << x[j] << y[j] << endl;
                if (a > -EPS)
                    continue;
                for (int k = 1; k <= n; k++)
                    if (fabs(a * x[k] * x[k] + b * x[k] - y[k]) < EPS)
                        line[i][j] |= (1 << (k - 1));
            }
        for (int i = 0; i < (1 << n); i++)
        {
            int j = lowbit[i];
            dp[i | 1 << (j - 1)] = min(dp[i | 1 << (j - 1)], dp[i] + 1);
            for (int k = 1; k <= n; k++)
                dp[i | line[j][k]] = min(dp[i | line[j][k]], dp[i] + 1);
        }
        // for (int i = 0; i < (1 << n); i++)
        //     printf("%d ", dp[i]);
        // printf("\n");
        printf("%d\n", dp[(1 << n) - 1]);
    }
    return 0;
}