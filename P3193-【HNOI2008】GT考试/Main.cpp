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

const int N = 25, INF = 0x7fffffff;

int n, m, p;
struct Matrix
{
    int x[N][N];
    int *operator[](int a) { return x[a]; }
    Matrix(int a = 0)
    {
        for (int i = 0; i < N; i++)
            for (int j = 0; j < N; j++)
                if (i == j)
                    x[i][j] = a;
                else
                    x[i][j] = 0;
    }
};

Matrix operator*(Matrix a, Matrix b)
{
    Matrix c;
    for (int i = 0; i < m; i++)
        for (int j = 0; j < m; j++)
            for (int k = 0; k < m; k++)
                c[i][j] = (c[i][j] + a[i][k] * b[k][j]) % p;
    return c;
}

inline Matrix qpow(Matrix a, int b)
{
    Matrix r(1);
    for (; b; b >>= 1, a = a * a)
        if (b & 1)
            r = r * a;
    return r;
}

char s[100];
Matrix f, a;
int nxt[100];

inline void kmp()
{
    int j = 0;
    for (int i = 2; i <= m; i++)
    {
        while (j && s[i] != s[j + 1])
            j = nxt[j];
        if (s[j + 1] == s[i])
            j++;
        nxt[i] = j;
    }
    for (int i = 0; i < m; i++)
        for (int j = 0; j < 10; j++)
        {
            int x = i;
            while (x && s[x + 1] - '0' != j)
                x = nxt[x];
            if (j == s[x + 1] - '0')
                a[i][x + 1]++;
            else
                a[i][0]++;
        }
}
int main()
{
    read(n), read(m), read(p);
    scanf("%s", s + 1);
    kmp();
    f = qpow(a, n);
    int ans = 0;
    for (int i = 0; i < m; i++)
        ans += f[0][i], ans %= p;
    printf("%d\n", ans);
    return 0;
}