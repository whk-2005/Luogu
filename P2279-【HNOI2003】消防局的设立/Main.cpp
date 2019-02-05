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

const int MAXN = 1010;

int n;
int f[MAXN];
int a[MAXN], deep[MAXN], b[MAXN];
int u, v, w;
int ans;

inline bool cmp(int x, int y) { return deep[x] > deep[y]; }

int main()
{
    scanf("%d", &n);
    a[1] = 1, b[1] = b[0] = MAXN;
    for (int i = 2; i <= n; i++)
        scanf("%d", &f[i]), deep[i] = deep[f[i]] + 1, a[i] = i, b[i] = MAXN;
    sort(a + 1, a + n + 1, cmp);
    for (int i = 1; i <= n; i++)
    {
        v = a[i], w = f[v], u = f[f[v]];
        b[v] = min(b[v], min(b[w] + 1, b[u] + 2));
        if (b[v] > 2)
        {
            b[u] = 0;
            ans++;
            b[f[u]] = min(b[f[u]], 1);
            b[f[f[u]]] = min(b[f[f[u]]], 2);
        }
    }
    printf("%d\n", ans);
    return 0;
}