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

int t, k, n, m;
int c[2010][2010], s[2010][2010];

inline void build()
{
    c[1][1] = 1;
    for (int i = 0; i <= 2000; i++)
        c[i][0] = 1;
    for (int i = 2; i <= 2000; i++)
        for (int j = 1; j <= i; j++)
            c[i][j] = (c[i - 1][j] + c[i - 1][j - 1]) % k;
    for (int i = 2; i <= 2000; i++)
    {
        for (int j = 1; j <= i; j++)
        {
            s[i][j] = s[i - 1][j] + s[i][j - 1] - s[i - 1][j - 1];
            if (c[i][j] == 0)
                s[i][j] += 1;
        }
        s[i][i + 1] = s[i][i];
    }
}

int main()
{
    read(t), read(k);
    build();
    // for (int i = 1; i <= 10; i++)
    // {
    //     for (int j = 1; j <= i; j++)
    //         printf("%d ", c[i][j]);
    //     printf("\n");
    // }
    while (t--)
    {
        read(n), read(m);
        if (m > n)
            m = n;
        printf("%d\n", s[n][m]);
    }
    return 0;
}