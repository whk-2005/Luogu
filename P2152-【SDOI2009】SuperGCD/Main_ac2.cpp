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

const int base = 1e4;

int a[10010], b[10010], c[10010], s[10010], f[10010];
int s0, T;

void Print(int a[])
{
    cout << a[a[0]];
    for (int i = a[0] - 1; i > 0; i--)
        for (int j = base / 10; j > 0; j /= 10)
            cout << a[i] / j % 10;
    cout << endl;
}

void Init(int a[])
{
    string s;
    cin >> s;
    int len = s.length(), i, j;
    for (i = 0; i < len; i++)
    {
        j = (len - i + 3) / 4;
        a[j] = a[j] * 10 + s[i] - '0';
    }
    a[0] = (len + 3) / 4;
}

int Comp(int a[], int b[])
{
    if (a[0] > b[0])
        return 1;
    if (a[0] < b[0])
        return -1;
    for (int i = a[0]; i >= 1; i--)
        if (a[i] > b[i])
            return 1;
        else if (a[i] < b[i])
            return -1;
    return 0;
}

void Div(int a[], int k)
{ 
    int i, t = 0;
    for (i = a[0]; i >= 1; i--)
    {
        t = t * base + a[i];
        a[i] = t / k;
        t %= k;
    }
    while (a[a[0]] == 0 && a[0] > 0)
        a[0]--;
}

void Minus(int a[], int b[])
{ 
    for (int i = 1; i <= a[0]; i++)
    {
        a[i] -= b[i];
        if (a[i] < 0)
        {
            a[i + 1]--;
            a[i] += base;
        }
    }
    while (a[a[0]] == 0 && a[0] > 0)
        a[0]--;
}

void MulHigh(int a[], int b[])
{
    memset(c, 0, sizeof(c));
    for (int i = 1; i <= a[0]; i++)
        for (int j = 1; j <= b[0]; j++)
        {
            c[i + j - 1] += a[i] * b[j];
            c[i + j] += c[i + j - 1] / base;
            c[i + j - 1] %= base;
        }
    c[0] = a[0] + b[0];
    while (c[c[0]] == 0 && c[0] > 0)
        c[0]--;
    for (int i = 0; i <= c[0]; i++)
        a[i] = c[i];
}

void MulLow(int a[], int k)
{
    for (int i = 1; i <= a[0]; i++)
        a[i] *= k;
    for (int i = 1; i <= a[0]; i++)
    {
        a[i + 1] += a[i] / base;
        a[i] %= base;
    }
    while (a[a[0] + 1] > 0)
    {
        a[0]++;
        a[a[0] + 1] = a[a[0]] / base;
        a[a[0]] %= base;
    }
}

void Gcd(int a[], int b[], int t)
{
    if (Comp(a, b) == 0)
    {
        T = t;
        return;
    }
    if (Comp(a, b) < 0)
    {
        Gcd(b, a, t);
        return;
    }
    int ta, tb;
    if (a[1] % 2 == 0)
    {
        Div(a, 2);
        ta = 1;
    }
    else
        ta = 0;
    if (b[1] % 2 == 0)
    {
        Div(b, 2);
        tb = 1;
    }
    else
        tb = 0;
    if (ta && tb)
        Gcd(a, b, t + 1);
    else if (!ta && !tb)
    {
        Minus(a, b);
        Gcd(a, b, t);
    }
    else
        Gcd(a, b, t);
}

int main()
{
    Init(a);
    Init(b);
    Gcd(a, b, 0);
    if (T == 0)
        Print(a);
    else
    {
        f[0] = f[1] = 1;
        for (int i = 1; i <= T; i++)
            MulLow(f, 2);
        MulHigh(f, a); 
        Print(f);  
    }
    return 0;
}