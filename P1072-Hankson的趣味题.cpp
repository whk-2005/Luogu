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

int n;
int a0, a1, b0, b1;

int main()
{
    scanf("%d", &n);
    while (n--)
    {
        scanf("%d%d%d%d", &a0, &a1, &b0, &b1);
        int p = a0 / a1;
        int q = b1 / b0;
        int ans = 0;
        for (int i = 1; i * i <= b1; i++)
        {
            if (b1 % i == 0)
            {
                if (i % a1 == 0 && __gcd(i / a1, p) == 1 && __gcd(q, b1 / i) == 1)
                    ans++;
                int j = b1 / i;
                if (i == j)
                    continue;
                if (j % a1 == 0 && __gcd(j / a1, p) == 1 && __gcd(q, b1 / j) == 1)
                    ans++;
            }
        }
        printf("%d\n", ans);
    }
    return 0;
}