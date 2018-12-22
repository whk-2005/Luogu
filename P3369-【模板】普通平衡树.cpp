#include <bits/stdc++.h>

using namespace std;

vector<int> v;
int n, opt, x;

int main()
{
    v.reserve(100010);
    scanf("%d", &n);
    while (n--)
    {
        scanf("%d%d", &opt, &x);
        if (opt == 1)
            v.insert(lower_bound(v.begin(), v.end(), x), x);
        if (opt == 2)
            v.erase(lower_bound(v.begin(), v.end(), x));
        if (opt == 3)
            printf("%d\n", lower_bound(v.begin(), v.end(), x) - v.begin() + 1);
        if (opt == 4)
            printf("%d\n", v[x - 1]);
        if (opt == 5)
            printf("%d\n", v[lower_bound(v.begin(), v.end(), x) - v.begin() - 1]);
        if (opt == 6)
            printf("%d\n", v[upper_bound(v.begin(), v.end(), x) - v.begin()]);
    }
    return 0;
}