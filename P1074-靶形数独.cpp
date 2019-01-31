#include <algorithm>
#include <cctype>
#include <cmath>
#include <cstdio>
#include <cstring>
#include <deque>
#include <iostream>
#include <queue>
#include <set>
#include <stack>
#include <string>
#include <vector>

using namespace std;

typedef long long ll;

struct node
{
    int line, sum;
} s[10];
int map[10][10];
bool line[10][10], nine[10][10], list[10][10];
int score[6] = {0, 6, 7, 8, 9, 10};
int ans = -1;

inline int which(int r, int c)
{
    if (r <= 3 && c <= 3)
        return 1;
    if (r <= 3 && c <= 6)
        return 2;
    if (r <= 3)
        return 3;
    if (r <= 6 && c <= 3)
        return 4;
    if (r <= 6 && c <= 6)
        return 5;
    if (r <= 6)
        return 6;
    if (r <= 9 && c <= 3)
        return 7;
    if (r <= 9 && c <= 6)
        return 8;
    if (r <= 9)
        return 9;
}

inline void print()
{
    int sum = 0;
    for (int i = 1; i <= 9; i++)
        for (int j = 1; j <= 9; j++)
            sum += map[i][j] * score[min(min(i, 10 - i), min(j, 10 - j))];
    ans = max(ans, sum);
}

void dfs(int h, int x, int y)
{
    if (h == 10)
    {
        print();
        return;
    }
    if (y == 10)
    {
        dfs(h + 1, s[h + 1].line, 1);
        return;
    }
    if (!map[x][y])
    {
        for (int i = 1; i <= 9; i++)
            if (line[x][i] == 0 && list[y][i] == 0 && nine[which(x, y)][i] == 0)
            {
                line[x][i] = 1, list[y][i] = 1, nine[which(x, y)][i] = 1;
                map[x][y] = i;
                dfs(h, x, y + 1);
                map[x][y] = 0;
                line[x][i] = 0, list[y][i] = 0, nine[which(x, y)][i] = 0;
            }
    }
    else
        dfs(h, x, y + 1);
}

bool cmp(node x, node y) { return x.sum < y.sum; }

int main()
{
    for (int i = 1; i <= 9; i++)
    {
        int k = 0;
        for (int j = 1; j <= 9; j++)
        {
            scanf("%d", &map[i][j]);
            if (!map[i][j])
                k++;
            line[i][map[i][j]] = 1;
            nine[which(i, j)][map[i][j]] = 1;
            list[j][map[i][j]] = 1;
        }
        s[i].line = i;
        s[i].sum = k;
    }
    sort(s + 1, s + 10, cmp);
    dfs(1, s[1].line, 1);
    printf("%d", ans);
    return 0;
}