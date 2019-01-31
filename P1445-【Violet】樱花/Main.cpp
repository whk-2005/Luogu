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

const int MOD = 1e9 + 7;

int n, cnt;
ll ans = 1;
int prime[1000005], m[1000005], num[1000005];
bool vis[1000005];

void getpri()
{
    for (int i = 2; i <= n; i++)
    {
        if (!vis[i])
            prime[++cnt] = i, m[i] = cnt;
        for (int j = 1; prime[j] * i <= n && j <= cnt; j++)
        {
            vis[prime[j] * i] = 1;
            m[prime[j] * i] = j;
            if (i % prime[j] == 0)
                break;
        }
    }
}

void cal(int x)
{
    while (x != 1)
    {
        num[m[x]]++;
        x /= prime[m[x]];
    }
}

int main()
{
    scanf("%d", &n);
    getpri();
    for (int i = 1; i <= n; i++)
        cal(i);
    for (int i = 1; i <= cnt; i++)
        ans = ans * (num[i] * 2 + 1) % MOD;
    printf("%lld\n", ans);
    return 0;
}