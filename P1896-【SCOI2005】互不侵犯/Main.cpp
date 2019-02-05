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

int n, m;
ll f[10][2000][100];
int sit[2000], gs[2000];
int cnt;
ll ans;

void dfs(int a, int b, int c)
{
    if (c >= n)
    {
        sit[++cnt] = a;
        gs[cnt] = b;
        return;
    }
    dfs(a, b, c + 1);
    dfs(a + (1 << c), b + 1, c + 2);
}

int main()
{
    scanf("%d%d", &n, &m);
    dfs(0, 0, 0);
    for (int i = 1; i <= cnt; i++)
        f[1][i][gs[i]] = 1;
    for (int i = 2; i <= n; i++)
        for (int j = 1; j <= cnt; j++)
            for (int k = 1; k <= cnt; k++)
            {
                if (sit[j] & sit[k])
                    continue;
                if ((sit[j] << 1) & sit[k])
                    continue;
                if (sit[j] & (sit[k] << 1))
                    continue;
                for (int l = m; l >= gs[j]; l--)
                    f[i][j][l] += f[i - 1][k][l - gs[j]];
            }
    for (int i = 1; i <= cnt; i++)
        ans += f[n][i][m];
    printf("%lld\n", ans);
    return 0;
}