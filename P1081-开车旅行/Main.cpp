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

inline void read(int &num)
{
    num = 0;
    int w = 1;
    char ch = getchar();
    if (ch == '-')
        w = -1;
    while (ch < '0' || ch > '9')
    {
        ch = getchar();
        if (ch == '-')
            w = -1;
    }
    while ((ch >= '0' && ch <= '9'))
        num = num * 10 + ch - '0', ch = getchar();
    num = num * w;
}

const int MAXN = 100010;
const double INF = 1e15;

int n, q, t, idx;
int h[MAXN];
int f[MAXN][20][5];
int dp1[MAXN][20][3], dp2[MAXN][20][3];
double ans = INF;

struct Node
{
    int idx, data;
    friend bool operator<(Node a, Node b)
    {
        return a.data < b.data;
    }
};

multiset<Node> s;

inline void calc(int S, int &a, int &b, int x)
{
    a = 0, b = 0;
    int now = S;
    for (int k = 18; ~k; k--)
    {
        if (f[now][k][0] && a + b + dp1[now][k][0] + dp2[now][k][0] <= x)
        {
            a += dp1[now][k][0];
            b += dp2[now][k][0];
            now = f[now][k][0];
        }
    }
}

signed main()
{
    read(n);
    for (int i = 1; i <= n; i++)
        read(h[i]);
    Node a;
    h[0] = 2e9, h[n + 1] = -2e9;
    a.idx = 0, a.data = 2e9;
    s.insert(a), s.insert(a);
    a.idx = n + 1, a.data = -2e9;
    s.insert(a), s.insert(a);
    for (int i = n; i; i--)
    {
        int goa, gob;
        int pre, nxt;
        int preh, nxth;
        Node aa;
        aa.idx = i, aa.data = h[i];
        s.insert(aa);
        multiset<Node>::iterator it = s.lower_bound(aa);
        it++;
        nxt = (*it).idx, nxth = (*it).data;
        it--, it--;
        pre = (*it).idx, preh = (*it).data;
        it++;
        if (abs(nxth - h[i]) >= abs(preh - h[i]))
        {
            gob = pre;
            it--, it--;
            if (abs(nxth - h[i]) >= abs((*it).data - h[i]))
                goa = (*it).idx;
            else
                goa = nxt;
        }
        else
        {
            gob = nxt;
            it++, it++;
            if (abs(preh - h[i]) > abs((*it).data - h[i]))
                goa = (*it).idx;
            else
                goa = pre;
        }
        f[i][0][0] = goa;
        f[i][0][1] = gob;
        dp1[i][0][0] = abs(h[i] - h[goa]);
        dp1[i][1][0] = dp1[i][0][0];
        dp2[i][0][1] = abs(h[i] - h[gob]);
        dp2[i][1][1] = dp2[i][0][1];
    }
    for (int i = 1; i <= n; i++)
    {
        f[i][1][0] = f[f[i][0][0]][0][1];
        dp1[i][1][0] = dp1[i][0][0];
        dp2[i][1][0] = abs(h[f[i][1][0]] - h[f[i][0][0]]);
        f[i][1][1] = f[f[i][0][1]][0][0];
        dp2[i][1][1] = dp2[i][0][1];
        dp1[i][1][1] = abs(h[f[i][1][1]] - h[f[i][0][1]]);
    }
    for (int k = 2; k <= 18; k++)
    {
        for (int i = 1; i <= n; i++)
        {
            f[i][k][1] = f[f[i][k - 1][1]][k - 1][1];
            dp2[i][k][1] = dp2[f[i][k - 1][1]][k - 1][1] + dp2[i][k - 1][1];
            dp1[i][k][1] = dp1[i][k - 1][1] + dp1[f[i][k - 1][1]][k - 1][1];
            f[i][k][0] = f[f[i][k - 1][0]][k - 1][0];
            dp1[i][k][0] = dp1[i][k - 1][0] + dp1[f[i][k - 1][0]][k - 1][0];
            dp2[i][k][0] = dp2[i][k - 1][0] + dp2[f[i][k - 1][0]][k - 1][0];
        }
    }
    read(q);
    for (int i = 1; i <= n; i++)
    {
        int la, lb;
        calc(i, la, lb, q);
        if (!lb)
        {
            if (ans > INF)
                ans = INF, idx = i;
            else if (ans == INF && h[idx] < h[i])
                idx = i;
        }
        else
        {
            double now = (double)la / (double)lb;
            if (now < ans)
                ans = now, idx = i;
            else if (now == ans && h[idx] < h[i])
                idx = i;
        }
    }
    printf("%d\n", idx);
    read(t);
    while (t--)
    {
        int a, b;
        int la, lb;
        read(a), read(b);
        calc(a, la, lb, b);
        printf("%d %d\n", la, lb);
    }
    return 0;
}