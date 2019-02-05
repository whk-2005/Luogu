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

template <typename T>
inline void read(T &num)
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

template<typename T>
void DEBUG(T a[], int num) 
{
    for (int i = 1; i <= num; i++)
        cout << a[i] << ' ';
    cout << endl;
}

const int MAXN = 1e7;

int n;
bool isprime[MAXN + 10];
int prinum, prime[(int)1e6];
int f[MAXN];
ll s[MAXN];
ll ans;

int main()
{
    read(n);
    memset(isprime, 1, sizeof(isprime));
    isprime[1] = 0;
    f[1] = 1;
    for (int i = 1; i <= (int)1e7; i++)
    {
        if (isprime[i] == 1)
        {
            f[i] = i - 1;
            prime[++prinum] = i;
        }
        for (int j = 1; j <= prinum && i * prime[j] <= (int)1e7; j++)
        {
            isprime[i * prime[j]] = 0;
            if (__gcd(prime[j], i) == 1)
                f[prime[j] * i] = f[prime[j]] * f[i];
            else
                f[prime[j] * i] = prime[j] * f[i];
            if (i % prime[j] == 0)
                break;
        }
    }
    // DEBUG(f, 10);
    s[0] = 0;
    for (int i = 1; i <= (int)1e7; i++)
        s[i] = 2 * f[i] + s[i - 1];
    // DEBUG(s, 10);
    ans = 0;
    for (int i = 1; i <= prinum; i++)
    {
        if (prime[i] > n)
            break;
        ans += s[n / prime[i]] - 1;
    }
    printf("%lld\n", ans);
    return 0;
}