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
void read(T &num)
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

template <typename T, typename... Args>
void read(T &num, Args &... args) { read(num), read(args...); }

const int N = 1010;
const int INF = 1e9;

int n;
int a[N], b[N];
int dp[N][6 * N];
int s;
int min1, min2;

int main()
{
    read(n);
    for (int i = 1; i <= n; ++i)
        read(a[i], b[i]), s += a[i] + b[i];
    for (int i = 1; i <= n; ++i)
        for (int j = 0; j <= 6 * n; ++j)
            dp[i][j] = INF;
    dp[1][b[1]] = 1;
    dp[1][a[1]] = 0;
    for (int i = 2; i <= n; ++i)
        for (int j = 0; j <= 6 * n; ++j)
        {
            if (j - a[i] >= 0)
                dp[i][j] = min(dp[i][j], dp[i - 1][j - a[i]]);
            if (j - b[i] >= 0)
                dp[i][j] = min(dp[i][j], dp[i - 1][j - b[i]] + 1);
        }
    min1 = min2 = INF;
    for (int i = 0; i <= s; ++i)
        if (dp[n][i] != INF)
        {
            if (abs(2 * i - s) < min1)
                min1 = abs(2 * i - s), min2 = dp[n][i];
            else if (abs(2 * i - s) == min1)
                min2 = min(min2, dp[n][i]);
        }
    printf("%d\n", min2);
    return 0;
}