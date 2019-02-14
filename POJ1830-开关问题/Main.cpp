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

inline int read(int &num)
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
    return num;
}

int t, n;
int a[100][100];
int s[100], e[100];
int ans;

inline int gauss()
{
    int i, j, k, l;
    for (i = 0, j = 0; i < n && j < n; i++, j++)
    {
        int row = i;
        for (k = i + 1; k < n; k++)
            if (a[k][j] > a[row][j])
                row = k;
        if (row != i)
            for (k = j; k <= n; k++)
                swap(a[i][k], a[row][k]);
        if (a[i][j] == 0)
        {
            i--;
            continue;
        }
        for (k = i + 1; k < n; k++)
        {
            if (a[k][j] == 0)
                continue;
            for (int l = j; l <= n; l++)
                a[k][l] = (a[k][l] - a[i][l] + 2) & 1;
        }
    }
    for (j = i; j < n; j++)
        if (a[j][n] != 0)
            return -1;
    if (i == n)
        return 1;
    return pow(2.0, n - i);
}

int main()
{
    read(t);
    while (t--)
    {
        memset(a, 0, sizeof(a));
        read(n);
        for (int i = 0; i < n; i++)
            read(s[i]);
        for (int i = 0; i < n; i++)
        {
            read(e[i]);
            a[i][n] = (e[i] - s[i] + 2) & 1;
            a[i][i] = 1;
        }
        for (int u = read(u), v = read(v); u != 0 && v != 0; u = read(u), v = read(v))
            a[v - 1][u - 1] = 1;
        if ((ans = gauss()) < 0)
            printf("Oh,it's impossible~!!\n");
        else
            printf("%d\n", ans);
    }
    return 0;
}