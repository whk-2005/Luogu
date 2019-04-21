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
    char c = getchar();
    if (c == '-')
        w = -1;
    while (c < '0' || c > '9')
    {
        c = getchar();
        if (c == '-')
            w = -1;
    }
    while ((c >= '0' && c <= '9'))
        num = num * 10 + c - '0', c = getchar();
    num = num * w;
}

template <typename T, typename... Args>
inline void read(T &num, Args &... args) { read(num), read(args...); }

vector<int> v;
int n, minn;
int k;
int ans;
char c;

int main()
{
    ios::sync_with_stdio(0);
    cin >> n >> minn;
    v.reserve(1000010);
    while(n--)
    {
        cin >> c >> k;
        if (c == 'I')
        {
            if (k < minn)
                continue;
            v.insert(lower_bound(v.begin(), v.end(), k), k);
        }
        if (c == 'A')
            for (int i = 0; i < v.size(); i++)
                v[i] += k;
        if (c == 'S')
            for (int i = 0; i < v.size(); i++)
            {
                v[i] -= k;
                if (v[i] < minn)
                    v.erase(lower_bound(v.begin(), v.end(), v[i])), i--, ans++;
            }
        if (c == 'F')
        {
            if (k > v.size())
                cout << -1 << endl;
            else
                cout << v[v.size() - k] << endl;
        }
    }
    cout << ans << endl;
    return 0;
}