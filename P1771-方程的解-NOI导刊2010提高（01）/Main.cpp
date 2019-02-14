#include <bits/stdc++.h>

using namespace std;

int a, b;
int ans;
int c[800] = {1, 1};

inline int qpow(int b,int p,int k)
{
    int ans = 1;
    while(p)
    {
        if(p & 1)
			ans = ans * b % k;
        b = b * b % k;
		p>>=1;
    }
    return ans;
}

inline void print(int p[])
{
    printf("%d", p[p[0]]);
	for(int i = p[0] - 1; i >= 1;i--)
		printf("%04d", p[i]);
	return;
}

inline void comb(int n, int m)
{
    for(int k = 1;k <= m; k++)
    {
        for(int i = 1;i <= c[0]; i++)
			c[i] *= n - k + 1;
        for(int i = 1;i <= c[0];i++)
			c[i + 1] += c[i] / 10000, c[i] %= 10000;
        while(c[c[0] + 1])
			c[0]++;
        for(int i = c[0], y = 0; i >= 1;i--)
			y = y * 10000 + c[i], c[i] = y / k, y %= k;
        while(!c[c[0]])
			c[0]--;
    }
}

int main()
{
    scanf("%d%d", &b, &a);
    a %= 1000;
	a = qpow(a, a, 1000) - 1;
	b--;
    comb(a, b);
    print(c);
    return 0;
}
