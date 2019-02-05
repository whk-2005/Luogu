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

struct node
{
    int len, a[4010]; 
    node() {}
    node(int n)
    {
        char st[10010];
        scanf("%s", st);
        int length = strlen(st);
        for (int i = 0; i < length; i++)
        {
            int j = (length - i + 5) / 6;
            a[j] = a[j] * 10 + st[i] - '0';
        }
        len = (length + 5) / 6;
    }
};

int cmp(node &a, node &b)
{
    if (a.len != b.len)
        return a.len - b.len;
    for (int i = a.len; i >= 1; i--) 
        if (a.a[i] != b.a[i])
            return a.a[i] - b.a[i];
    return 0;
}

node sub(node &a, node &b)
{
    node no;
    no.len = a.len;
    int carry = 0, i;
    for (i = 1; i <= no.len; i++)
    {
        no.a[i] = a.a[i] - b.a[i] - carry;
        carry = no.a[i] < 0;
        no.a[i] += 1000000 * carry;
    }
    for (i = no.len; no.a[i] == 0 && i > 1; i--)
        ;
    no.len = i;
    return no;
}

node gcd(node x, node y)
{
    while (cmp(x, y)) 
        cmp(x, y) > 0 ? x = sub(x, y) : y = sub(y, x);
    return x;
}

node a(1), b(1);
node now;

int main()
{
    now = gcd(a, b); 
    printf("%d", now.a[now.len]);
    for (int i = now.len - 1; i >= 1; i--)
        printf("%04d", now.a[i]);
    return 0;
}