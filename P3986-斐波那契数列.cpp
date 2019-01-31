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

long long p, q, a1, a2, n, m;

struct Matrix
{
    long long a[3][3];
    Matrix() { memset(a, 0, sizeof a); }
    Matrix operator*(const Matrix &b) const
    {
        Matrix res;
        for (int i = 1; i <= 2; ++i)
            for (int j = 1; j <= 2; ++j)
                for (int k = 1; k <= 2; ++k)
                    res.a[i][j] = (res.a[i][j] + a[i][k] * b.a[k][j]) % m;
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

int main()
{
    scanf("%lld%lld%lld%lld%lld%lld", &p, &q, &a1, &a2, &n, &m);
    if (n == 1)
        return printf("%lld\n", a1), 0;
    if (n == 2)
        return printf("%lld\n", a2), 0;
    base.a[1][1] = p, base.a[2][1] = q, base.a[1][2] = 1;
    ans.a[1][1] = a2, ans.a[1][2] = a1;
    qpow(n - 2);
    printf("%lld\n", ans.a[1][1] % m);
    return 0;
}