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

const int MAXN = 1e5 + 10;

int n, a[MAXN];
bool b[MAXN];

inline void getpri()
{
    for (int i = 2; i <= n + 1; i++)
    {
        if (!b[i])
        {
            printf("%d ", 1);
            for (int j = i * 2; j <= n + 1; j += i)
                b[j] = 1;
        }
        else
            printf("%d ", 2);
    }
}

int main()
{
    scanf("%d", &n);
    if (n - 1 == 0)
        return printf("1\n1"), 0;
    if (n - 2 == 0)
        return printf("1\n1 1"), 0;
    printf("2\n");
    getpri();
    return 0;
}