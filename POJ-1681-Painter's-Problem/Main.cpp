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

const double EPS = 1e-6;

int n;
int Map[100][100];
int cop[100][100];
int line[100];
int cnt, minn;
char s[100];

inline void draw(int x, int y)
{
    Map[x][y] = !Map[x][y];
    Map[x - 1][y] = !Map[x - 1][y];
    Map[x + 1][y] = !Map[x + 1][y];
    Map[x][y - 1] = !Map[x][y - 1];
    Map[x][y + 1] = !Map[x][y + 1];
    cnt++;
}

inline int work()
{
    for (int i = 2; i <= n; i++)
        for (int j = 1; j <= n; j++)
            if (Map[i - 1][j] == 0)
                draw(i, j);
    for (int i = 1; i <= n; i++)
        if (Map[n][i] != 1)
            return 0;
    minn = min(cnt, minn);
    return 1;
}

inline void getline(int k)
{
    for (int i = n; i >= 1; i--, k /= 2)
        line[i] = k & 1;
}

int t;

int main()
{
    read(t);
    while (t--)
    {
        read(n);
        minn = n * n + 1;
        for (int i = 1; i <= n; i++)
        {
            scanf("%s", s + 1);
            for (int j = 1; j <= n; j++)
                if (s[j] == 'w')
                    cop[i][j] = 0;
                else
                    cop[i][j] = 1;
        }
        // for (int i = 1; i <= n; i++)
        //     for (int j = 1; j <= n; j++)
        //         printf("%d%c", cop[i][j], j != n ? ' ' : '\n');
        int poww = pow(2, n);
        for (int i = 0; i < poww; i++)
        {
            cnt = 0;
            memcpy(Map, cop, sizeof(cop));
            getline(i);
            for (int j = 1; j <= n; j++)
                if (line[j] == 1)
                    draw(1, j);
            work();
        }
        if (minn != n * n + 1)
            printf("%d\n", minn);
        else
            printf("inf\n");
    }
    return 0;
}