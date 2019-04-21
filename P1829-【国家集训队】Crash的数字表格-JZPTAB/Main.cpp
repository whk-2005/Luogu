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

const int MOD = 20101009;
const int N = 1e7 + 10;

int n, m;
bool vis[N];
int cnt, prime[N], mu[N];
ll sum[N];
ll ans;
ll inv2 = (MOD + 1ll) / 2ll;
ll summ;

void get_mu(int n)
{
    mu[1ll] = 1ll;
    for (int i = 2; i <= n; i++)
    {
        if (!vis[i])
        {
            prime[++cnt] = i;
            mu[i] = -1ll;
        }
        for(int j = 1ll; j <= cnt && prime[j] * i <= n; j++)
        {
            vis[i * prime[j]] = 1ll;
            if(i % prime[j] == 0)
                break;
            else 
                mu[i * prime[j]] = -mu[i];
        }
    }
    for(int i = 1ll;i <= n;i++)
        sum[i] = (sum[i - 1ll] + 1ll * mu[i] * i % MOD * i % MOD) % MOD;
}

int main()
{
    read(n, m);
    get_mu(min(n, m));
    for (int d = 1ll; d <= min(n, m); d++)
    {
        summ = 0;
        int maxx = n / d, maxy = m / d, minn = min(maxx, maxy);
        for (int l = 1ll, r; l <= minn; l = r + 1ll)
        {
            r = min(maxx / (maxx / l), maxy / (maxy / l));
            (summ += (sum[r] - sum[l - 1ll]) % MOD * (((1ll + maxx / l) % MOD * 1ll * (maxx / l) % MOD * inv2 % MOD) % MOD) % MOD *   (((1ll + maxy / l) % MOD * 1ll * (maxy / l) % MOD * inv2 % MOD) % MOD) % MOD) %= MOD;
        }
        (ans += summ * 1ll * d) %= MOD;
    }
    printf("%lld\n", (ans % MOD + MOD) % MOD);
    return 0;
}