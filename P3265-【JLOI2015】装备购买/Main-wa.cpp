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

const int MAXN = 510;
const double EPS = 1e-4;

struct node
{
    int cost;
    double x[MAXN];
} a[MAXN];
int n, m;
int cnt, sum;
int p[MAXN];

inline bool cmp(node a, node b) { return a.cost < b.cost; }

int main()
{
    read(n), read(m);
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++)
            scanf("%lf", &a[i].x[j]);
    for (int i = 1; i <= n; i++)
        read(a[i].cost);
    sort(a + 1, a + n + 1, cmp);
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++)
            if (abs(a[i].x[j]) > EPS)
            {
                if (p[j])
                {
                    double tmp = a[i].x[j] / a[p[j]].x[j];
                    for (int k = j; k <= n; k++)
                        a[i].x[k] -= a[p[j]].x[k] * tmp;
                }
                else
                {
                    p[j] = i;
                    cnt++;
                    sum += a[i].cost;
                    break;
                }
            }
    printf("%d %d\n", cnt, sum);
    return 0;
}