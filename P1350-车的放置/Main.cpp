#include <bits/stdc++.h>

using namespace std;

const int MAXN = 2e3 + 10;
const int MOD = 100003;

int f[MAXN][MAXN], v[MAXN];
int a, b, c, d, m;
int ans;

int main()
{
	scanf("%d%d%d%d%d", &a, &b, &c, &d, &m);
	for (int i = 1; i <= c; i++)
		v[i] = d, f[i][0] = 1;
	for (int i = 1; i <= a; i++)
		v[c + i] = b + d, f[c + i][0] = 1;
	f[0][0] = 1;
	for (int i = 1; i <= a + c; i++)
		for (int j = 1; j <= m; j++)
			f[i][j] = (f[i - 1][j] + f[i - 1][j - 1] * (v[i] - j + 1)) % MOD;
	printf("%d\n", f[a + c][m]);
	return 0;
}
