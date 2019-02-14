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

const double PI = acos(-1.0);
const int MAXN = 1e7 + 10;

struct complex
{
    double x, y;
    complex(double xx = 0, double yy = 0) { x = xx, y = yy; }
} a[MAXN], b[MAXN];
complex operator+(complex a, complex b) { return complex(a.x + b.x, a.y + b.y); }
complex operator-(complex a, complex b) { return complex(a.x - b.x, a.y - b.y); }
complex operator*(complex a, complex b) { return complex(a.x * b.x - a.y * b.y, a.x * b.y + a.y * b.x); }

int n, m;
int l, r[MAXN];
int limit = 1;

void fft(complex A[], int typ)
{
    for (int i = 0; i < limit; i++)
        if (i < r[i])
            swap(A[i], A[r[i]]);
    for (int mid = 1; mid < limit; mid <<= 1)
    {
        complex W(cos(PI / mid), typ * sin(PI / mid));
        for (int i = mid << 1, j = 0; j < limit; j += i)
        {
            complex w(1, 0);
            for (int k = 0; k < mid; k++, w = w * W)
            {
                complex x = A[j + k], y = w * A[j + mid + k];
                A[j + k] = x + y;
                A[j + mid + k] = x - y;
            }
        }
    }
}

int main()
{
    read(n, m);
    for (int i = 0; i <= n; i++)
        read(a[i].x);
    for (int i = 0; i <= m; i++)
        read(b[i].x);
    while (limit <= n + m)
        limit <<= 1, l++;
    for (int i = 0; i < limit; i++)
        r[i] = (r[i >> 1] >> 1) | ((i & 1) << (l - 1));
    fft(a, 1);
    fft(b, 1);
    for (int i = 0; i <= limit; i++)
        a[i] = a[i] * b[i];
    fft(a, -1);
    for (int i = 0; i <= n + m; i++)
        printf("%d ", (int)(a[i].x / limit + 0.5));
    printf("\n");
    return 0;
}