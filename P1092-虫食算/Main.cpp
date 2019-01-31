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

typedef long long ll;

const int MAXN = 30;

int n;
int a[MAXN], b[MAXN], c[MAXN];
int num[MAXN], nxt[MAXN], cnt;
char s1[MAXN], s2[MAXN], s3[MAXN];
bool used[MAXN];

inline bool prune()
{
    if (num[a[0]] + num[b[0]] >= n)
        return 1;
    for (int i = n - 1; i >= 0; i--)
    {
        int A = num[a[i]], B = num[b[i]], C = num[c[i]];
        if (A == -1 || B == -1 || C == -1)
            continue;
        if ((A + B) % n != C && (A + B + 1) % n != C)
            return true;
    }
    return false;
}

inline bool check()
{
    for (int i = n - 1, x = 0; i >= 0; i--)
    {
        int A = num[a[i]], B = num[b[i]], C = num[c[i]];
        if ((A + B + x) % n != C)
            return 0;
        x = (A + B + x) / n;
    }
    return 1;
}

void dfs(int step)
{
    if (prune() == 1)
        return;
    if (step == n)
    {
        if (check() == true)
        {
            for (int i = 0; i < n; i++)
                printf("%d ", num[i]);
            printf("\n");
            exit(0);
        }
    }
    for (int i = n - 1; i >= 0; i--)
        if (used[i] == false)
        {
            num[nxt[step]] = i;
            used[i] = true;
            dfs(step + 1);
            num[nxt[step]] = -1;
            used[i] = false;
        }
    return;
}

inline void get_next(int x)
{
    if (used[x] == 0)
    {
        used[x] = 1;
        nxt[cnt++] = x;
    }
}

inline int char_to_num(char c)
{
    return c - 'A';
}

int main()
{
    scanf("%d", &n);
    scanf("%s%s%s", s1, s2, s3);
    for (int i = 0; i < n; i++)
    {
        a[i] = char_to_num(s1[i]);
        b[i] = char_to_num(s2[i]);
        c[i] = char_to_num(s3[i]);
        num[i] = -1;
    }
    for (int i = n - 1; i >= 0; i--)
    {
        get_next(a[i]);
        get_next(b[i]);
        get_next(c[i]);
    }
    for (int i = 0; i < n; i++)
        used[i] = 0;
    dfs(0);
    return 0;
}