#include <algorithm>
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

const int mod = 1e9 + 7;

struct Matrix
{
    long long a[5][5];

    Matrix() { memset(a, 0, sizeof a); }

    Matrix operator*(const Matrix &b) const
    {
        Matrix res;
        for (int i = 1; i <= 3; ++i)
            for (int j = 1; j <= 3; ++j)
                for (int k = 1; k <= 3; ++k)
                    res.a[i][j] = (res.a[i][j] + a[i][k] * b.a[k][j]) % mod;
        return res;
    }
} ans, base;

inline void qpow(long long b)
{
    while (b)
    {
        if (b & 1)
            ans = ans * base;
        base = base * base;
        b >>= 1;
    }
}

int t, n;

int main()
{
    scanf("%d", &t);
    while (t--)
    {
        scanf("%d", &n);
        if (n <= 3)
        {
            printf("1\n");
            continue;
        }
        memset(ans.a, 0, sizeof(ans.a));
        memset(base.a, 0, sizeof(base.a));
        for (int i = 1; i <= 3; i++)
            ans.a[i][i] = 1;
        base.a[1][1] = base.a[1][3] = base.a[2][1] = base.a[3][2] = 1;
        qpow(n - 1);
        printf("%lld\n", ans.a[1][1]);
    }
    return 0;
}