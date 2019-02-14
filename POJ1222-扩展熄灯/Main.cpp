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

inline int read(int &num)
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
    return num;
}

int Map[40][40];
int ans[40];

inline void gauss()
{
    int i, j, k, r;
    for (k = 0; k < 30; k++)
    {
        i = k;
        while (i < 30 && Map[i][k] == 0)
            i++;
        if (i > k)
        {
            for (r = 0; r <= 30; r++)
                swap(Map[i][r], Map[k][r]);
        }
        for (i = 0; i < 30; i++)
        {
            if (i != k && Map[i][k])
            {
                for (j = 0; j <= 30; j++)
                    Map[i][j] ^= Map[k][j];
            }
        }
    }
    for (i = 0; i < 30; i++)
        if (Map[i][30])
        {
            for (j = 0; j < 30 && !Map[i][j]; j++)
                ;
            if (j == 30)
                return;
            else
                ans[j] = Map[i][30];
        }
}

int t;

int main()
{
    read(t);
    for (int k = 1; k <= t; k++)
    {
        memset(Map, 0, sizeof(Map));
        for (int i = 0; i < 30; i++)
        {
            read(Map[i][30]);
            ans[i] = 0;
        }
        for (int i = 0; i < 30; i++)
        {
            int kn = i / 6;
            int km = i % 6;
            for (int j = 0; j < 30; j++)
            {
                int kx = j / 6;
                int ky = j % 6;
                if (abs(kx - kn) + abs(ky - km) <= 1)
                    Map[i][j] = 1;
                else
                    Map[i][j] = 0;
            }
        }
        gauss();
        printf("PUZZLE #%d\n", k);
        for (int i = 0; i < 30; i++)
        {
            printf("%d", ans[i]);
            if ((i + 1) % 6 == 0)
                printf("\n");
            else
                printf(" ");
        }
    }
    return 0;
}