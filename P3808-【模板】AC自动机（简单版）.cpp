#include <bits/stdc++.h>

using namespace std;

const int N = 500010;
int n;
char s[1000010];
int ans;

struct Aho_Corasick_Automaton
{
    queue<int> q;
    int c[N][26], val[N], fail[N];
    int cnt;

    void insert(char *s)
    {
        int len = strlen(s);
        int now = 0;
        for (int i = 0; i < len; i++)
        {
            int val1 = s[i] - 'a';
            if (!c[now][val1])
                c[now][val1] = ++cnt;
            now = c[now][val1];
        }
        val[now]++;
    }

    void build()
    {
        for (int i = 0; i < 26; i++)
            if (c[0][i])
            {
                fail[c[0][i]] = 0;
                q.push(c[0][i]);
            }
        while (!q.empty())
        {
            int pre = q.front();
            q.pop();
            for (int i = 0; i < 26; i++)
                if (c[pre][i])
                {
                    fail[c[pre][i]] = c[fail[pre]][i];
                    q.push(c[pre][i]);
                }
                else
                    c[pre][i] = c[fail[pre]][i];
        }
    }

    int find(char *s)
    {
        int len = strlen(s);
        int now = 0, ans = 0;
        for (int i = 0; i < len; i++)
        {
            now = c[now][s[i] - 'a'];
            for (int j = now; j && ~val[j]; j = fail[j])
            {
                ans += val[j];
                val[j] = -1;
            }
        }
        return ans;
    }
} AC;

int main()
{
    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
    {
        scanf("%s", s);
        AC.insert(s);
    }
    AC.build();
    scanf("%s", s);
    ans = AC.find(s);
    printf("%d\n", ans);
    return 0;
}