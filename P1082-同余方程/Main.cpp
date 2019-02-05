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

void exgcd(ll a, ll b, ll &d, ll &x, ll &y)
{
    if (!b)
        x = 1, y = 0, d = a;
    else
    {
        exgcd(b, a % b, d, y, x);
        y -= (a / b) * x;
    }
}

int main()
{
    ll a, b, d, x, y;
    cin >> a >> b;
    exgcd(a, b, d, x, y);
    cout << (b + x) % b << endl;
    return 0;
}