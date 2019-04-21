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

template <typename T, typename... Args>
inline void read(T &num, Args &... args) { read(num), read(args...); }

int money[1010][1010];

int main()
{
    int n, m, p;
    int pay[1010];
    int dp[1010];
    memset(dp, -0x3f, sizeof(dp));
    dp[0] = 0;
    read(n, m, p);
    for (int i = 1; i <= n; ++i)
        for (int j = 1; j <= m; ++j)
            read(money[i][j]);
    for (int i = 1; i <= n; ++i)
        read(pay[i]);
    for (int i = 1; i <= m; ++i)
        for (int j = 1; j <= n; ++j)
        {
            int tmp1 = j - 1;
            if (!tmp1)
                tmp1 = n;
            int tmp2 = money[tmp1][i];
            for (int k = 1; k <= p; ++k)
            {
                if (i - k < 0)
                    break;
                dp[i] = max(dp[i], dp[i - k] + tmp2 - pay[tmp1]);
                --tmp1;
                if (!tmp1)
                    tmp1 = n;
                tmp2 += money[tmp1][i - k];
            }
        }
    printf("%d\n", dp[m]);
    return 0;
}