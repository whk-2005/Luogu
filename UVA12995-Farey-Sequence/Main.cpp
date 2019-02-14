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

inline void read(int &num)
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

const int MAXN = 1000010;

int prime[MAXN], phi[MAXN];
ll ans[MAXN];
bool f[MAXN];
int n, p;

int main()
{
    for (int i = 2; i < MAXN; i++)
    {
        if (!f[i])
            phi[prime[++p] = i] = i - 1;
        ans[i] = ans[i - 1] + phi[i];
        for (int j = 1, k; j <= p && (k = i * prime[j]) < MAXN; j++)
        {
            f[k] = 1;
            if (i % prime[j])
                phi[k] = phi[i] * (prime[j] - 1);
            else
            {
                phi[k] = phi[i] * prime[j];
                break;
            }
        }
    }
    while (read(n), n)
        printf("%lld\n", ans[n]);
    return 0;
}