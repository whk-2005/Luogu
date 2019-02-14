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

const int MAXM = 7e6 + 10;

int n, m, q, u, v, t;
double p;
priority_queue<int> ans;
int cut1[MAXM], cut2[MAXM];
int now[MAXM];
int t0, t1, t2;
int h0, h1, h2;
int top, s;

bool cmp(int a, int b) { return a > b; }

int main()
{
    read(n), read(m), read(q), read(u), read(v), read(t);
    for (t0 = 1; t0 <= n; t0++)
        read(now[t0]);
    p = (double)u / v;
    t0--;
    t1 = t2 = 0;
    h0 = h1 = h2 = 1;
    sort(now + 1, now + t0 + 1, cmp);
    for (int i = 1; i <= m; i++)
    {
        if (h0 > t0)
        {
            if (cut1[h1] > cut2[h2])
                top = cut1[h1++];
            else
                top = cut2[h2++];
        }
        else if (now[h0] >= cut1[h1] && now[h0] >= cut2[h2])
            top = now[h0++];
        else if (cut1[h1] >= cut2[h2] && now[h0] <= cut1[h1])
            top = cut1[h1++];
        else
            top = cut2[h2++];
        top += s;
        int a1 = floor(p * top), a2 = top - a1;
        s += q;
        a1 -= s, a2 -= s;
        cut1[++t1] = a1, cut2[++t2] = a2;
        if (i % t == 0)
            printf("%d ", top);
    }
    printf("\n");
    // cout << h0 << h1 << h2 << endl;
    // cout << t0 << t1 << t2 << endl;
    for (int i = h0; i <= t0; i++)
        ans.push(now[i]);
    for (int i = h1; i <= t1; i++)
        ans.push(cut1[i]);
    for (int i = h2; i <= t2; i++)
        ans.push(cut2[i]);
    for (int i = 1; ans.size(); i++)
    {
        if (i % t == 0)
            printf("%d ", ans.top() + s);
        ans.pop();
    }
    printf("\n");
    return 0;
}