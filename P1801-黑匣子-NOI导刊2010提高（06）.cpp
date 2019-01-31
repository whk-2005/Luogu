#include <iostream>
#include <vector>
#include <cstdio>

using namespace std;

const int MAXM = 200010;
vector<int> arr;
int n, m;
int a[MAXM], u[MAXM], k = 1;

int main()
{
    arr.clear();
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; i++)
        scanf("%d", &a[i]);
    for (int i = 1; i <= m; i++)
        scanf("%d", &u[i]);
    sort(u + 1, u + m + 1);
    for (int i = 1; i <= n; i++)
    {
        arr.insert(lower_bound(arr.begin(), arr.end(), a[i]), a[i]);
        while (u[k] == i)
            printf("%d\n", arr[k - 1]), k++;
        if (k > m)
            break;
    }
    return 0;
}