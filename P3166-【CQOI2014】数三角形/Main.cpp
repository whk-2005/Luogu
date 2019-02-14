#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

ll n, m, ans;

int main()
{
	scanf("%lld%lld", &n, &m);
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= m; j++)
			ans += (n - i + 1) * (m - j + 1) * (6 * i * j - 2 * __gcd(i, j));
	printf("%lld\n", ans);
	return 0;
}
