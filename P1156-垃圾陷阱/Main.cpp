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

int d, g;
struct Rubbish
{
    int t, f, h;
    bool operator<(const Rubbish &r) const
    {
        return t < r.t;
    }
} a[110];
int f[110];

int main()
{
    scanf("%d%d", &d, &g);
    for (int i = 1; i <= g; i++)
        scanf("%d%d%d", &a[i].t, &a[i].f, &a[i].h);
    sort(a + 1, a + g + 1);
    memset(f, -1, sizeof(f));
    f[0] = 10;
    for (int i = 1; i <= g; i++)
        for (int j = d; j >= 0; j--)
            if (f[j] >= a[i].t)
            {
                if (j + a[i].h >= d)
                {
                    printf("%d\n", a[i].t);
                    return 0;
                }
                f[j + a[i].h] = max(f[j + a[i].h], f[j]);
                f[j] += a[i].f;
            }
    printf("%d\n", f[0]);
    return 0;
}