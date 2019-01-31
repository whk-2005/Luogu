#include <algorithm>
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

long long f[210][210] = {1}, sum[210][210];
int n, m, ki;
char a[1010], b[1010];

int main()
{
    scanf("%d%d%d%s%s", &n, &m, &ki, a, b);
    for (int i = 1; i <= n; i++)
        for (int j = m; j >= 1; j--)
            for (int k = ki; k >= 1; k--)
                f[j][k] = (f[j][k] + (sum[j][k] = a[i - 1] == b[j - 1] ? sum[j - 1][k] + f[j - 1][k - 1] : 0)) % 1000000007;
    printf("%lld\n", f[m][ki]);
    return 0;
}