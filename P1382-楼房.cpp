#include <bits/stdc++.h>

using namespace std;

struct line
{
    int x, y, k;
    bool operator <(const line a) const
    {
        if (x != a.x)
            return x < a.x;
        if (k != a.k)
            return k < a.k;
        if (k == 1)
            return y > a.y;
        if (k == 2)
            return y < a.y;
    }
} l[200010];
struct node
{
    int xa, ya;
} ans[400010];
struct building
{
    int h, x, y;
} a[100010];
int n;
int cnt, num;
multiset<int> s;

int main()
{
    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
    {
        scanf("%d%d%d", &a[i].h, &a[i].x, &a[i].y);
        l[++cnt].y = a[i].h, l[cnt].x = a[i].x, l[cnt].k = 1;
        l[++cnt].y = a[i].h, l[cnt].x = a[i].y, l[cnt].k = 2;
    }
    sort(l + 1, l + cnt + 1);
    s.insert(0);
    for (int i = 1; i <= cnt; i++)
    {
        int maxx = *s.rbegin();
        if (l[i].k == 1)
        {
            if (l[i].y <= maxx)
                s.insert(l[i].y);
            else
            {
                ans[++num].xa = l[i].x, ans[num].ya = maxx;
                ans[++num].xa = l[i].x, ans[num].ya = l[i].y;
                s.insert(l[i].y);
            }
        }
        if (l[i].k == 2)
        {
            if (l[i].y == maxx && s.count(maxx) == 1)
            {
                s.erase(maxx);
                ans[++num].xa = l[i].x, ans[num].ya = maxx;
                ans[++num].xa = l[i].x, ans[num].ya = *s.rbegin();
            }
            else
                s.erase(s.find(l[i].y));
        }
    }
    printf("%d\n", num);
    for (int i = 1; i <= num; i++)
        printf("%d %d\n", ans[i].xa, ans[i].ya);
    return 0;
}