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

struct Matrix
{
    long long a[5][5];
    long long mod = 1e8;

    Matrix() { memset(a, 0, sizeof a); }

    Matrix operator*(const Matrix &b) const
    {
        Matrix res;
        for (int i = 1; i <= 2; i++)
            for (int j = 1; j <= 2; j++)
                for (int k = 1; k <= 2; k++)
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

ll n, m;

int main()
{
    scanf("%lld%lld", &n, &m);
    n = __gcd(n, m);
    base.a[1][1] = base.a[1][2] = base.a[2][1] = 1;
    ans.a[1][1] = ans.a[1][2] = 1;
    if (n <= 2)
        printf("1\n");
    else
        qpow(n - 2), printf("%lld\n", ans.a[1][1]);
    return 0;
}