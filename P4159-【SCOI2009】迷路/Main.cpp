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

const int MAXN = 150;
const int MOD = 2009;

int n, t;
int tn;
char s[20];

struct Matrix
{
    int x[MAXN][MAXN];

    Matrix () { memset(x, 0, sizeof(x)); }

    int *operator[](int a) { return x[a]; }

    Matrix operator*(Matrix a)
    {
        Matrix ans;
        for (int i = 1; i <= n; i++)
            for (int j = 1; j <= n; j++)
                for (int k = 1; k <= n; k++)
                    ans[i][j] = (ans[i][j] + x[i][k] * a[k][j] % MOD) % MOD;
        return ans;
    }
} a;

inline Matrix qpow(Matrix a, int b)
{
    Matrix ans;
    for (int i = 1; i <= n; i++)
        ans[i][i] = 1;
    while (b)
    {
        if (b & 1)
            ans = ans * a;
        a = a * a;
        b >>= 1;
    }
    return ans;
}

int main()
{
    scanf("%d%d", &n, &t);
    tn = n;
    n *= 9;
    for (int i = 1; i <= tn; i++)
        for (int j = 1; j <= 8; j++)
            a[9 * (i - 1) + j][9 * (i - 1) + j + 1] = 1;
    for (int i = 1; i <= tn; i++)
    {
        scanf("%s", s + 1);
        for (int j = 1; j <= tn; j++)
        {
            if (s[j] > '0')
                a[9 * (i - 1) + s[j] - '0'][9 * (j - 1) + 1] = 1;
        }
    }
    a = qpow(a, t);
    printf("%d\n", a[1][tn * 9 - 8]);
    return 0;
}