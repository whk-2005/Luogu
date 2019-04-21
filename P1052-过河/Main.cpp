// かわいい
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
#include <climits>

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

const int N = 10010;

int main()
{
    int l, s, t, m;
    int a[N];
    int f[N], far[N], flag[N];
    memset(a, 0, sizeof(a));
    memset(f, 0, sizeof(f));
    memset(far, 0, sizeof(far));
    memset(flag, 0, sizeof(flag));
    read(l, s, t, m);
    for (int i = 1; i <= m; i++)
        read(a[i]);
    if (s == t)
    {
        int cnt = 0;
        for (int i = 1; i <= m; i++)
            cnt += ((a[i] % s) == 0);
        printf("%d\n", cnt);
        return 0;
    }
    sort(a + 1, a + m + 1);
    a[0] = f[0] = 0;
    far[m + 1] = min(l - a[m], 100);
    l = 0;
    for (int i = 1; i <= m; i++)
        far[i] = min(a[i] - a[i - 1], 90), l += far[i], flag[l] = 1;
    l += far[m + 1];
    for (int i = 1; i <= l + 9; i++)
    {
        f[i] = INT_MAX - 1;
        for (int j = s; j <= t; j++)
            if (i >= j)
                f[i] = min(f[i], f[i - j] + flag[i]);
    }
    int minn = INT_MAX - 1;
    for (int i = l; i <= l + 9; i++)
        minn = min(minn, f[i]);
    printf("%d", minn);
    return 0;
}