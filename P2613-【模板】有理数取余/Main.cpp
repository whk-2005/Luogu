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

const ll MOD = 19260817;

char a[10010], b[10010];
int lena, lenb;
int n, m;

ll mul(ll s, int k)
{
    ll ans = 1;
    while (k)
    {
        if (k & 1)
            ans = ans * s % MOD;
        k >>= 1;
        s = s * s % MOD;
    }
    return ans;
}

int main()
{
    scanf("%s%s", a + 1, b + 1);
    lena = strlen(a + 1);
    lenb = strlen(b + 1);
    for (int i = 1; i <= lena; i++)
        n = (n * 10 + a[i] - '0') % MOD;
    for (int i = 1; i <= lenb; i++)
        m = (m * 10 + b[i] - '0') % MOD;
    if (m == 0)
        printf("Angry!\n");
    else
        printf("%lld\n", n * mul(m, MOD - 2) % MOD);
    return 0;
}