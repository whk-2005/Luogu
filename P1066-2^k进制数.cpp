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

const int M = 100000000;
int k, w, b, c;

struct BNUM
{
    int w[60];
    int len;
    BNUM()
    {
        memset(w, 0, sizeof w);
        len = 0;
    }
    void set(int q)
    {
        w[0] = q;
        len = 1;
    }
    void print()
    {
        printf("%d", w[len - 1]);
        for (int i = len - 2; i >= 0; i--)
            printf("%08d", w[i]);
        printf("\n");
    }
} f[510][510], ans;

BNUM operator+(const BNUM &a, const BNUM &b)
{
    BNUM ans;
    int la = max(a.len, b.len);
    for (int i = 0; i < la; i++)
        ans.w[i] = a.w[i] + b.w[i];
    ans.len = la;
    for (int i = 0; i < ans.len; i++)
    {
        ans.w[i + 1] += ans.w[i] / M;
        ans.w[i] %= M;
        if (ans.w[ans.len] > 0)
            ans.len++;
    }
    return ans;
}
int main()
{
    scanf("%d%d", &k, &w);
    if (k == 1)
    {
        printf("0\n");
        return 0;
    }
    b = 1 << k;
    c = 1;
    for (int i = 0; i < b; i++)
        f[1][i].set(1);
    for (int i = b - c; i >= 0; i--)
        f[c][i] = f[c][i] + f[c][i + 1];
    ++c;
    w -= k;
    for (int i = 0; i <= b - c; i++)
        f[c][i] = f[c - 1][i + 1];
    while (w > k && b > c)
    {
        for (int i = b - c - 1; i >= 0; i--)
            f[c][i] = f[c][i] + f[c][i + 1];
        ans = ans + f[c][1];
        ++c;
        w -= k;
        for (int i = 0; i <= b - c; i++)
            f[c][i] = f[c - 1][i + 1];
    }
    if (b > c)
    {
        int la = min(b - c, (1 << w) - 1);
        for (int i = la - 1; i >= 0; i--)
            f[c][i] = f[c][i] + f[c][i + 1];
        ans = ans + f[c][1];
    }
    ans.print();
    system("pause");
    return 0;
}