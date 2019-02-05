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

const int MAXN = 1e6 + 10;

int n;
int a[MAXN * 10], b[MAXN * 10];
int ans[MAXN * 10];
int maxx;

int main()
{
    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
        scanf("%d", &a[i]), b[a[i]]++, maxx = max(maxx, a[i]);
    for (int i = 1; i <= maxx; i++)
    {
        if (b[i] == 0)
            continue;
        for (int j = i; j <= maxx; j += i)
        {
            ans[j] += b[i];
        }
    }
    for (int i = 1; i <= n; i++)
        printf("%d\n", ans[a[i]] - 1);
    return 0;
}