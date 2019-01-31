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

int n, m;
int diff[1000011], need[1000011];
int r[1000011], t[1000011], s[1000011], d[1000011];
bool check(int x)
{
    memset(diff, 0, sizeof(diff));
    for (int i = 1; i <= x; i++)
    {
        diff[s[i]] += d[i];
        diff[t[i] + 1] -= d[i];
    }
    for (int i = 1; i <= n; i++)
    {
        need[i] = need[i - 1] + diff[i];
        if (need[i] > r[i])
            return 0;
    }
    return 1;
}

int main()
{
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; i++)
        scanf("%d", &r[i]);
    for (int i = 1; i <= m; i++)
        scanf("%d%d%d", &d[i], &s[i], &t[i]);
    if (check(m))
    {
        printf("0\n");
        return 0;
    }
    int left = 1, right = m;
    while (left < right)
    {
        int mid = (left + right) / 2;
        if (check(mid))
            left = mid + 1;
        else
            right = mid;
    }
    printf("-1\n%d\n", left);
    return 0;
}