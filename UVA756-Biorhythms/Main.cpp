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

const int LCM = 21252;

int p, e, i, d;

int main()
{
    int time = 1;
    while (scanf("%d %d %d %d", &p, &e, &i, &d) == 4)
    {
        if (p == -1 && e == -1 && i == -1 && d == -1)
            break;
        int n = (5544 * p + 14421 * e + 1288 * i - d + 21252) % LCM;
        if (n == 0)
            n = 21252;
        printf("Case %d: the next triple peak occurs in %d days.\n", time++, n);
    }
    return 0;
}