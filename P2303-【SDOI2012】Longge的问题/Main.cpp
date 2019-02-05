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

ll n, ans;

inline ll euler(ll x)
{
    ll ans = x;
    for (ll i = 2; i * i <= x; i++)
        if (x % i == 0)
        {
            ans = ans - ans / i;
            while (x % i == 0)
                x /= i;
        }
    if (x >= 2)
        ans = ans - ans / x;
    return ans;
}
int main()
{
    scanf("%lld", &n);
    for (ll i = 1; i * i <= n; i++)
        if (n % i == 0)
            ans += i * euler(n / i) + n / i * euler(i);
    ll sqr = sqrt(n);
    if (sqr * sqr == n)
        ans -= sqr * euler(sqr);
    printf("%lld\n", ans);
    return 0;
}