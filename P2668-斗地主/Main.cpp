#include <bits/stdc++.h>

using namespace std;

const int MAXN = 25;
const int INF = 1061109567;

int t, n;
int card[MAXN];
int f[MAXN][MAXN][MAXN][MAXN][5];
int cnt[MAXN];
int num, ans;

inline int dfs2(int on, int tw, int th, int fo, int w)
{
	if (f[on][tw][th][fo][w] < INF)
		return f[on][tw][th][fo][w];
	f[on][tw][th][fo][w] = on + tw + th + fo + w;
	int &now = f[on][tw][th][fo][w];
	if (w == 2)
		now = min(now, dfs2(on, tw, th, fo, 0) + 1);
	if (fo)	
	{
		if (w == 2)
			now = min(now, dfs2(on, tw, th, fo - 1, 0) + 1);
		if (w && on)
			now = min(now, dfs2(on - 1, tw, th, fo - 1, w - 1) + 1);
		if (on >= 2)
			now = min(now, dfs2(on - 2, tw, th, fo - 1, w) + 1);
		if (tw >= 2)
			now = min(now, dfs2(on, tw - 2, th, fo - 1, w) + 1);
		if (tw)
			now = min(now, dfs2(on, tw - 1, th, fo - 1, w) + 1);
		now = min(now, dfs2(on + 1, tw, th + 1, fo - 1, w));
		now = min(now, dfs2(on, tw + 2, th, fo - 1, w));
		now = min(now, dfs2(on + 2, tw + 1, th, fo - 1, w));
	}
	if (th)
	{
		if (on)
			now = min(now, dfs2(on - 1, tw, th - 1, fo, w) + 1);
		if (tw)
			now = min(now, dfs2(on, tw - 1, th - 1, fo, w) + 1);
		if (w)
			now = min(now, dfs2(on, tw, th - 1, fo, w - 1) + 1);
		now = min(now, dfs2(on + 1, tw + 1, th - 1, fo, w));
		now = min(now, dfs2(on + 3, tw, th - 1, fo, w));
	}
	return f[on][tw][th][fo][w];
}

inline int get()
{
	memset(cnt, 0, sizeof(cnt));
	for(int i = 1; i <= 13; i++) 
		cnt[card[i]]++;
	return dfs2(cnt[1], cnt[2], cnt[3], cnt[4], card[14]);
}

inline void dfs1(int stp)
{
	ans = min(ans, stp + get());
	bool flag;
	for (int i = 1; i <= 11; i++)
	{
		for (int j = 2; j <= 12; j++)
		{
			if (i + j - 1 > 12)
				break;
			flag = 1;
			for (int k = 0; k <= j - 1; k++)
				if (card[i + k] < 3)
					flag = 0;
			if (!flag)
				break;
			for (int k = 0; k <= j - 1; k++)
				card[i + k] -= 3;
			dfs1(stp + 1);
			for (int k = 0; k <= j - 1; k++)
				card[i + k] += 3;
		}
	}
	for (int i = 1; i <= 10; i++)
	{
		for (int j = 3; j <= 12; j++)
		{
			if (i + j - 1 > 12)
				break;
			flag = 1;
			for (int k = 0; k <= j - 1; k++)
				if (card[i + k] < 2)
					flag = 0;
			if (!flag)
				break;
			for (int k = 0; k <= j - 1; k++)
				card[i + k] -= 2;
			dfs1(stp + 1);
			for (int k = 0; k <= j - 1; k++)
				card[i + k] += 2;
		}
	}
	for (int i = 1; i <= 8; i++)
	{
		for (int j = 5; j <= 12; j++)
		{
			if (i + j - 1 > 12)
				break;
			flag = 1;
			for (int k = 0; k <= j - 1; k++)
				if (!card[i + k])
					flag = 0;
			if (!flag)
				break;
			for (int k = 0; k <= j - 1; k++)
				card[i + k] -= 1;
			dfs1(stp + 1);
			for (int k = 0; k <= j - 1; k++)
				card[i + k] += 1;
		}
	}

}
int main()
{
	scanf("%d%d", &t, &n);
	memset(f, 63, sizeof(f));
	while (t--)
	{
		num = 0;
		ans = n;
		memset(card, 0, sizeof(card));
		for (int i = 1; i <= n; i++)
		{
			int typ, col;
			scanf("%d%d", &typ, &col);
			if (typ == 0)
				typ = 14;
			else if(typ == 1 || typ == 2)
				typ += 11;
			else if (typ >= 3 && typ <= 13)
				typ -= 2;
			card[typ]++;
		}
		dfs1(0);
		printf("%d\n", ans);
	}
	return 0;
}
