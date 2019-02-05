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

const int MAXN = 3e6 + 5;

ll inv[MAXN] = {0, 1};
ll n, p;

int main()
{
    scanf("%lld %lld", &n, &p);
    printf("1\n");
    for (int i = 2; i <= n; i++)
    {
        inv[i] = p - (p / i) * inv[p % i] % p;
        printf("%lld\n", inv[i]);
    }
    return 0;
}