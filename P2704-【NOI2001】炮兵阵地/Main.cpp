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

int n, m;
int dp[(1 << 10)][(1 << 10)][3];
int a[110], sum[(1 << 10)];
char x;
int ans;

inline int Sum(int x)
{
    int tot = 0;
    while (x)
    {
        if (x & 1)
            tot++;
        x >>= 1;
    }
    return tot;
}

int main()
{
    ios::sync_with_stdio(0);
    cin >> n >> m;
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
        {
            cin >> x;
            a[i] <<= 1;
            a[i] += (x == 'H' ? 1 : 0);
        }
    for (int i = 0; i < (1 << m); i++)
        sum[i] = Sum(i);
    for (int j = 0; j < (1 << m); j++)
        if (!(j & a[0] || (j & (j << 1)) || (j & (j << 2))))
            dp[0][j][0] = sum[j];
    for (int i = 0; i < (1 << m); i++)
        for (int j = 0; j < (1 << m); j++)
            if (!(i & j || i & a[0] || j & a[1] || (i & (i << 1)) || (i & (i << 2)) || (j & (j << 1)) || (j & (j << 2))))
                dp[i][j][1] = sum[j] + sum[i];
    for (int l = 2; l < n; l++)
        for (int i = 0; i < (1 << m); i++)
        {
            if (i & a[l - 1] || (i & (i << 1)) || (i & (i << 2)))
                continue;
            for (int j = 0; j < (1 << m); j++)
            {
                if (j & a[l] || i & j || (j & (j << 1)) || (j & (j << 2)))
                    continue;
                for (int k = 0; k < (1 << m); k++)
                {
                    if (k & i || k & j || k & a[l - 2] || (k & (k << 1)) || (k & (k << 2)))
                        continue;
                    dp[i][j][l % 3] = max(dp[i][j][l % 3], dp[k][i][(l - 1) % 3] + sum[j]);
                }
            }
        }
    for (int i = 0; i < (1 << m); i++)
        for (int j = 0; j < (1 << m); j++)
            ans = max(ans, dp[i][j][(n - 1) % 3]);
    cout << ans << endl;
    return 0;
}