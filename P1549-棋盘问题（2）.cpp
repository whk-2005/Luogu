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

int n;
bool prime[210];
int a[20][20];
bool vis[110];

inline void select_prime()
{
    for (int i = 2; i <= 200; i++)
        prime[i] = 1;
    for (int i = 4; i <= 200; i += 2)
        prime[i] = 0;
    for (int i = 3; i <= 200; i += 2)
    {
        if (prime[i] == 1)
        {
            for (int j = 2 * i; j <= 200; j += i)
                prime[j] = 0;
        }
    }
}

void dfs(int x, int y)
{
    if (x == n + 1 && y == 1)
    {
        for (int i = 1; i <= n; i++)
        {
            for (int j = 1; j <= n; j++)
                printf("%d ", a[i][j]);
            printf("\n");
        }
        exit(0);
    }
    if (x == 1 || y == 1)
    {
        for (int i = 2; i <= n * n; i++)
        {
            if (!vis[i])
                if ((x == 1 && y != 1 && prime[i + a[x][y - 1]]) || (x != 1 && y == 1 && prime[i + a[x - 1][y]]) || (x != 1 && y != 1 && prime[i + a[x - 1][y]] && prime[i + a[x][y - 1]]))
                {
                    a[x][y] = i;
                    vis[i] = 1;
                    if (y == n)
                        dfs(x + 1, 1);
                    else
                        dfs(x, y + 1);
                    vis[i] = 0;
                    a[x][y] = 0;
                }
        }
    }
    else
    {
        for (int i = n * n; i >= 2; i--)
        {
            if (!vis[i])
                if ((x == 1 && y != 1 && prime[i + a[x][y - 1]]) || (x != 1 && y == 1 && prime[i + a[x - 1][y]]) || (x != 1 && y != 1 && prime[i + a[x - 1][y]] && prime[i + a[x][y - 1]]))
                {
                    a[x][y] = i;
                    vis[i] = 1;
                    if (y == n)
                        dfs(x + 1, 1);
                    else
                        dfs(x, y + 1);
                    vis[i] = 0;
                    a[x][y] = 0;
                }
        }
    }
}

int main()
{
    scanf("%d", &n);
    if (n == 1 || n == 3 || n == 9)
        return printf("NO\n"), 0;
    select_prime();
    // for (int i = 1; i <= 200; i++)
    //     if (prime[i] == 1)
    //         printf("%d ", i);
    // printf("\n");
    a[1][1] = 1;
    dfs(1, 2);
    return 0;
}