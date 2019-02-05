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

const int MAXN = 1e6;

int n;
bool is_prime[MAXN];
int pri[2 * MAXN], prinum;

inline int getpri(int n)
{
    memset(is_prime, 1, sizeof(is_prime));
    is_prime[1] = 0;
    for (int i = 2; i <= n; i++)
    {
        if (is_prime[i] == true)
            pri[++prinum] = i;
        for (int j = 1; j <= prinum; j++)
        {
            if (i * pri[j] > n)
                break;
            is_prime[i * pri[j]] = 0;
            if (i % pri[j] == 0)
                break;
        }
    }
}

int main()
{
    getpri(1000000);
    scanf("%d", &n);
    for (int j = 4; j <= n; j += 2)
    {
        for (int i = 1; i <= prinum; i++)
            if (is_prime[j - pri[i]])
            {
                printf("%d = %d + %d\n", j, pri[i], j - pri[i]);
                break;
            }
    }
    return 0;
}