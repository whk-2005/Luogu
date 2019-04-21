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
inline int read(T &num, Args &... args) { read(num), read(args...); }

const int MAXN = 800;

int n;
int a[MAXN][MAXN];
int f[MAXN];
struct node
{
    int x, y;
    node() {}
    node(int a, int b) { x = a, y = b; }
    bool operator<(const node a) const
    {
        if (x != a.x)
            return x > a.x;
        return y > a.y;
    }
};

int main()
{
    while (scanf("%d", &n) == 1)
    {
        memset(a, 0, sizeof(a));
        memset(f, 0, sizeof(f));
        for (int i = 1; i <= n; i++)
        {
            for (int j = 1; j <= n; j++)
                read(a[i][j]);
            sort(a[i] + 1, a[i] + n + 1);
        }
        for (int i = 1; i <= n; i++)
            f[i] = a[1][i];
        for (int line = 2; line <= n; line++)
        {
            priority_queue<node> pq;
            for (int i = 1; i <= n; i++)
                pq.push(node(f[i] + a[line][1], 1));
            for (int i = 1; i <= n; i++)
            {
                node u = pq.top();
                pq.pop();
                f[i] = u.x;
                int y = u.y;
                if (y + 1 <= n)
                {
                    node v = node(f[i] - a[line][y] + a[line][y + 1], y + 1);
                    pq.push(v);
                }
            }
        }
        for (int i = 1; i <= n; i++)
            printf("%d%c", f[i], i != n ? ' ' : '\n');
    }
    return 0;
}