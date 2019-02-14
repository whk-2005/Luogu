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

const int MOD = 1e9;

int m, n;
int field[20][20];
int F[20];
int maxsize;
bool st[4100];
int f[20][4100];
int ans;

int main()
{
    read(m), read(n);
    for (int i = 1; i <= m; i++)
        for (int j = 1; j <= n; j++)
            read(field[i][j]);
    for (int i = 1; i <= m; i++)
        for (int j = 1; j <= n; j++)
            F[i] = (F[i] << 1) + field[i][j];
    maxsize = 1 << n;
    for (int i = 0; i < maxsize; i++)
        st[i] = ((i & (i << 1)) == 0) && ((i & (i >> 1)) == 0);
    f[0][0] = 1;
    for (int i = 1; i <= m; i++)
        for (int j = 0; j < maxsize; j++)
            if (st[j] && ((j & F[i]) == j))
                for (int k = 0; k < maxsize; k++)
                    if ((k & j) == 0)
                        f[i][j] = (f[i][j] + f[i - 1][k]) % MOD;
    for (int i = 0; i < maxsize; i++)
        ans += f[m][i], ans %= MOD;
    printf("%d\n", ans);
    return 0;
}
