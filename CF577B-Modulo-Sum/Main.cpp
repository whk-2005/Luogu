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

const int MAXM = 1e3 + 10;

int n, m;
int a[MAXM * MAXM], f[MAXM][MAXM];
int c;

int main()
{
    read(n, m);
    for (int i = 1; i <= n; i++)
    {
        read(a[i]);
    }
    if (n > m)
        return printf("YES\n"), 0;
    for (int i = 1; i <= n && !c; i++)
    {
        a[i] %= m;
        f[i][a[i]] = 1;
        for (int j = 1; j <= m && !c; j++)
        {
            f[i][j] |= f[i - 1][j];
            f[i][(j + a[i]) % m] |= f[i - 1][j];
            if (f[i][0])
                c = 1;
        }
    }
    if (c)
        printf("YES\n");
    else
        printf("NO\n");
    return 0;
}