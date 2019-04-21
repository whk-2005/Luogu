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
#include <unordered_map>

#include <climits>

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

const int MAXN = 5000000;

ll mu[MAXN + 10];
ll ph[MAXN + 10];
unordered_map<int, ll> summu;
unordered_map<int, ll> sumph;
int v[MAXN + 10];
int p[MAXN + 10];
int cnt;

inline ll getsph(int n)
{
    if (n <= MAXN)
        return ph[n];
    if (sumph[n])
        return sumph[n];
    ll ans = 0;
    for (int l = 2, r; r < INT_MAX && l <= n; l = r + 1)
    {
        r = n / (n / l);
        ans += (ll)(r - l + 1) * getsph(n / l);
    }
    return sumph[n] = (unsigned long long)n * (n + 1ll) / 2ll - ans;
}

inline ll getsmu(int n)
{
    if (n <= MAXN)
        return mu[n];
    if (summu[n])
        return summu[n];
    ll ans = 0;
    for (int l = 2, r; r < INT_MAX && l <= n; l = r + 1)
    {
        r = n / (n / l);
        ans += (ll)(r - l + 1) * getsmu(n / l);
    }
    return summu[n] = 1ll - ans;
}

int t, n;

int main()
{
    v[1] = mu[1] = ph[1] = 1;
    for (int i = 2; i <= MAXN; i++)
    {
        if (!v[i])
            p[++cnt] = i, mu[i] = -1, ph[i] = i - 1;
        for (int j = 1; j <= cnt && i * p[j] <= MAXN; j++)
        {
            v[i * p[j]] = 1;
            if (i % p[j] == 0)
            {
                mu[i * p[j]] = 0;
                ph[i * p[j]] = ph[i] * p[j];
                break;
            }
            mu[i * p[j]] = -mu[i];
            ph[i * p[j]] = ph[i] * ph[p[j]];
        }
    }
    for (int i = 2; i <= MAXN; i++)
        mu[i] += mu[i - 1], ph[i] += ph[i - 1];
    read(t);
    while (t--)
    {
        read(n);
        printf("%lld %lld\n", getsph(n), getsmu(n));
    }
    return 0;
}