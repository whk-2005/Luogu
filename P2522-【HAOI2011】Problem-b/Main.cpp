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

template <typename n>
inline void read(n &num)
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

template <typename n, typename... Args>
inline void read(n &num, Args &... args) { read(num), read(args...); }

const int MAXN = 5e4 + 10;

int n, a, b, c, d, k;
ll p[MAXN], mu[MAXN], sum[MAXN];
ll ans;
int l, r;

inline void get_mu()
{
    bitset<MAXN> bist;
    mu[1] = sum[1] = 1;
    for (int i = 2; i <= MAXN - 5; ++i)
    {
        if (!bist[i])
            p[++p[0]] = i, mu[i] = -1;
        sum[i] = sum[i - 1] + mu[i];
        for (int j = 1; j <= p[0] && i * p[j] <= MAXN - 5; ++j)
        {
            bist[i * p[j]] = 1;
            if (i % p[j])
                mu[i * p[j]] = -mu[i];
            else
            {
                mu[i * p[j]] = 0;
                break;
            }
        }
    }
}

int main()
{
    get_mu();
    read(n);
    while (n--)
    {
        read(a, b, c, d, k);
        a = (a - 1) / k;
        b /= k;
        c = (c - 1) / k;
        d /= k;
        ans = 0;
        if (a > c)
            swap(a, c), swap(b, d);
        l = 1;
        for (; l <= a; l = r + 1)
        {
            int ra = a / (a / l);
            int rb = b / (b / l);
            int rc = c / (c / l);
            int rd = d / (d / l);
            r = min(ra, min(rb, min(rc, rd)));
            ans += (sum[r] - sum[l - 1]) * (b / l - a / l) * (d / l - c / l);
        }
        for (; l <= min(b, c); l = r + 1)
        {
            int rb = b / (b / l);
            int rc = c / (c / l);
            int rd = d / (d / l);
            r = min(rb, min(rc, rd));
            ans += (sum[r] - sum[l - 1]) * (b / l) * (d / l - c / l);
        }
        for (; l <= min(b, d); l = r + 1)
        {
            int rb = b / (b / l);
            int rd = d / (d / l);
            r = min(rb, rd);
            ans += (sum[r] - sum[l - 1]) * (b / l) * (d / l);
        }
        printf("%lld\n", ans);
    }
    return 0;
}