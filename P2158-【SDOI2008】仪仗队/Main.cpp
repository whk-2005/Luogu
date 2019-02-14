#include <bits/stdc++.h>
using namespace std;
long long n, ans;
long long f[40010];
int main() {
    cin >> n;
    if(n == 1) {
        cout << 0;
        return 0;
    }
    for(int i = 1; i <= n; i++)
        f[i] = i;
    for(int i = 2; i <= n; i++)
        if(f[i] == i) {
            for(int j = i; j <= n; j += i)
                f[j] = f[j] / i * (i - 1);
        }
    for(int i = 2; i < n; i++)
        ans += f[i] * 2;
    cout << ans + 3;
    return 0;
}