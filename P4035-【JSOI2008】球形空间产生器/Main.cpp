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

const int MAXN = 20;
double a[MAXN][MAXN], b[MAXN][MAXN];
double ans[MAXN];
int n, flag = 1;

inline void Solve(int x)
{
    if (x == n)
    {
        ans[x] = b[x][n + 1] / b[x][x];
        return;
    }
    for (int i = x + 1; i <= n; i++)
    {
        double tmp = abs(b[x][x]) / abs(b[i][x]);
        if (b[x][x] * b[i][x] > 0)
            for (int j = x; j <= n + 1; j++)
                b[i][j] *= tmp, b[i][j] = b[i][j] - b[x][j];
        else
            for (int j = x; j <= n + 1; j++)
                b[i][j] *= tmp, b[i][j] = b[i][j] + b[x][j];
    }
    Solve(x + 1);
    for (int i = n; i >= x + 1; i--)
        b[x][n + 1] -= (ans[i] * b[x][i]);
    ans[x] = b[x][n + 1] / b[x][x];
    return;
}

int main()
{
    read(n);
    for (int i = 1; i <= n + 1; i++)
        for (int j = 1; j <= n; j++)
            scanf("%lf", &a[i][j]);
    for (int i = 2; i <= n + 1; i++)
        for (int j = 1; j <= n; j++)
        {
            b[i - 1][j] = 2 * (a[i][j] - a[i - 1][j]);
            b[i - 1][n + 1] += (a[i][j] * a[i][j] - a[i - 1][j] * a[i - 1][j]);
        }
    Solve(1);
    for (int i = 1; i <= n; i++)
        printf("%.3lf ", ans[i]);
    return 0;
}