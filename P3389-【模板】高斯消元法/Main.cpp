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

const double EPS = 1e-7;

int n;
double in[110][110];
double ans[110];

int main()
{
    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n + 1; j++)
            scanf("%lf", &in[i][j]);
    // for (int i = 1; i <= n; i++)
    // {
    //     for (int j = 1; j <= n + 1; j++)
    //         printf("%.2lf ", in[i][j]);
    //     printf("\n");
    // }
    for (int i = 1; i <= n; i++)
    {
        int t = i;
        for (int j = i + 1; j <= n; j++)
            if (fabs(in[t][i]) < fabs(in[j][i]))
                t = j;
        if (fabs(in[t][i]) < EPS)
        {
            printf("No Solution\n");
            return 0;
        }
        if (i != t)
            swap(in[i], in[t]);
        double tmp = in[i][i];
        for (int j = i; j <= n + 1; j++)
            in[i][j] /= tmp;
        for (int j = i + 1; j <= n; j++)
        {
            tmp = in[j][i];
            for (int k = i; k <= n + 1; k++)
                in[j][k] -= in[i][k] * tmp;
        }
    }
    ans[n] = in[n][n + 1];
    for (int i = n - 1; i >= 1; i--)
    {
        ans[i] = in[i][n + 1];
        for (int j = i + 1; j <= n; j++)
            ans[i] -= (in[i][j] * ans[j]);
    }
    for (int i = 1; i <= n; i++)
        printf("%.2lf\n", ans[i]);
    return 0;
}