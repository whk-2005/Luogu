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

int n;
int p[20] = {0, 2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47};
ll maxn = -1, ans = -1;
void compute(ll m, int f, int t, int pr)
{
    if (t > maxn || (t == maxn && m < ans))
        ans = m, maxn = t;
    int j = 0, nn;
    ll i = m;
    while (j < pr)
    {
        j++;
        if (n / i < p[f])
            break;
        nn = t * (j + 1);
        i = i * p[f];
        if (i <= n)
            compute(i, f + 1, nn, j);
    }
}
int main()
{
    scanf("%d", &n);
    compute(1, 1, 1, 30);
    printf("%lld\n", ans);
}