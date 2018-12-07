#include <cstdio>
#include <cstring>
#include <iostream>

using namespace std;

const int MAXN = 30;

int n, m, x;
int a[MAXN][MAXN], b[MAXN][MAXN];
int now[MAXN];
int ans = -1;

void dfs(int cur, int step)
{
    if (cur > n)
    {
        int flag = 1;
        for (int i = 1; i <= n; ++i)
            if (now[i] == 0)
                flag = 0;
        if (flag)
        {
            if (ans == -1 || step < ans)
                ans = step;
        }
        return;
    }
    dfs(cur + 1, step);
    for (int i = 1; i <= n; ++i)
        now[i] ^= b[cur][i];
    dfs(cur + 1, step + 1);
    for (int i = 1; i <= n; ++i)
        now[i] ^= b[cur][i];
}

int main()
{
    scanf("%d", &n);
    for (int i = 1; i <= n; ++i)
    {
        scanf("%d", &m);
        for (int j = 1; j <= m; ++j)
        {
            scanf("%d", &x);
            a[i][x] = 1;
        }
    }
    for (int i = 1; i <= n; ++i)
    {
        b[i][i] ^= 1;
        for (int j = 1; j <= n; ++j)
        {
            if (a[i][j] && i != j)
            {
                b[i][j] ^= 1;
                for (int k = 1; k <= n; ++k)
                    if (a[j][k] && k != j)
                        b[i][k] ^= 1;
            }
        }
    }
    dfs(1, 0);
    if (ans == -1)
        puts("Change an alarm clock，please!");
    else
        printf("%d\n", ans);
    return 0;
}