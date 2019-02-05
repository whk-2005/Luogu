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

ll n, k, ans;

int main()
{
    scanf("%lld%lld", &n, &k);
    for (ll l = 1, r, t; l <= n; l = r + 1)
    {
        r = (t = k / l) ? min(k / t, n) : n;
        ans -= t * (r - l + 1) * (l + r) >> 1;
    }
    printf("%lld", ans + n * k);
    return 0;
}