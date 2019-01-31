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

typedef long long ll;

struct BigInt
{
    int num[2510], len; //num为数,为了避免乘法溢出,采用万进制. len为当前长度.
    bool flag;          //flag == 0表示正数,flag == 1表示负数.
    BigInt()
    {
        memset(num, 0, sizeof(num));
        len = 0;
        flag = 0;
    } //初始化
    template <typename T>
    BigInt(T n)
    {
        if (n < 0)
            flag = 1, n *= -1;
        else
            flag = 0;
        len = 0;
        while (n)
        {
            num[++len] = n % 10000;
            n /= 10000;
        }
    }
    void ad(int k)
    {
        if (k != 0 || len != 0)
            num[++len] = k;
    }
    void re()
    {
        reverse(num + 1, num + len + 1);
    }
    BigInt &operator=(const BigInt &b)
    {
        len = b.len;
        flag = b.flag;
        for (int i = 1; i <= len; i++)
            num[i] = b.num[i];
        return *this;
    } //operator =
};
//输入输出
istream &operator>>(istream &is, BigInt &a)
{
    char str[10010];
    char c;
    c = cin.get();
    if (c == 'm')
    {
        cout << "max" << endl;
        exit(0);
    }
    while ((c < '0' || c > '9') && c != '-')
        c = cin.get();
    if (c == '-')
        a.flag = 1;
    int i = 0;
    str[i] = cin.get();
    while (str[i] >= '0' && str[i] <= '9')
        str[++i] = cin.get();
    str[i] = '\0';
    int len = strlen(str);
    if (c != '-')
    {
        str[len] = str[len - 1];
        str[len + 1] = '\0';
        for (int i = len - 1; i >= 1; i--)
        {
            str[i] = str[i - 1];
        }
        str[0] = c;
        len++;
    }
    reverse(str, str + len);
    a.len = (len + 3) / 4;
    for (int i = 0, t = 0, w = 1; i < len; i++, w *= 10)
    {
        if (i % 4 == 0)
            w = 1, t++;
        a.num[t] += w * (str[i] - '0');
    }
    return is;
}
ostream &operator<<(ostream &os, BigInt a)
{
    if (a.flag)
        cout << '-';
    cout << a.num[a.len];
    for (int i = a.len - 1; i >= 1; i--)
    {
        if (a.num[i] <= 9)
            cout << "000";
        else if (a.num[i] <= 99)
            cout << "00";
        else if (a.num[i] <= 999)
            cout << "0";
        cout << a.num[i];
    }
    return os;
}
//逻辑判断符.
bool operator==(BigInt a, BigInt b)
{
    if (a.flag != b.flag)
        return 0;
    if (a.len != b.len)
        return 0;
    for (int i = 1; i <= a.len; i++)
        if (a.num[i] != b.num[i])
            return 0;
    return 1;
}
bool operator!=(BigInt a, BigInt b)
{
    return !(a == b);
}
bool operator<(BigInt a, BigInt b)
{
    if (a.flag != b.flag)
        return a.flag > b.flag;
    if (a.len != b.len)
    {
        if (a.flag == 0)
            return a.len < b.len;
        else
            return a.len > b.len;
    }
    for (int i = 1; i <= a.len; i++)
        if (a.num[i] != b.num[i])
        {
            if (a.flag == 0)
                return a.num[i] < b.num[i];
            else
                return a.num[i] > b.num[i];
        }
    return 0;
}
bool operator>(BigInt a, BigInt b)
{
    return b < a;
}
bool operator<=(BigInt a, BigInt b)
{
    return !(a > b);
}
bool operator>=(BigInt a, BigInt b)
{
    return !(a < b);
}
//为了处理负数,需要循环调用,特在此声明函数.
BigInt BigAbs(BigInt a)
{
    if (a.flag == 1)
        a.flag = 0;
    return a;
}
BigInt function_add(BigInt a, BigInt b); //加法
BigInt function_sub(BigInt a, BigInt b); //减法
BigInt function_mul(BigInt a, BigInt b); //乘法
BigInt function_div(BigInt a, BigInt b); //除法
BigInt function_add(BigInt a, BigInt b)
{
    BigInt ans;
    BigInt absa, absb;
    absa = BigAbs(a);
    absb = BigAbs(b);
    if (a.flag == 1 && b.flag == 0)
        return function_sub(b, absa);
    if (a.flag == 0 && b.flag == 1)
        return function_sub(a, absb);
    if (a.flag == 1 && b.flag == 1)
    {
        ans = function_add(absa, absb);
        ans.flag = 1;
        //cout << ans << endl;
        return ans;
    }
    ans.len = max(a.len, b.len);
    for (int i = 1; i <= ans.len; i++)
    {
        ans.num[i] += a.num[i] + b.num[i];
        ans.num[i + 1] += ans.num[i] / 10000;
        ans.num[i] %= 10000;
    }
    if (ans.num[ans.len + 1])
        ans.len++;
    if (ans.flag == 1 && ans.len == 1 && ans.num[1] == 0)
        ans.flag = 0;
    return ans;
}
BigInt function_sub(BigInt a, BigInt b)
{
    BigInt ans;
    BigInt absa, absb;
    absa = BigAbs(a);
    absb = BigAbs(b);
    if (a < b)
    {
        ans = function_sub(b, a);
        ans.flag = 1;
        return ans;
    }
    if (a.flag == 0 && b.flag == 1)
        return function_add(a, absb);
    if (a.flag == 1 && b.flag == 0)
    {
        ans = function_add(absa, b);
        ans.flag = 1;
        return ans;
    }
    if (a.flag == 1 && b.flag == 1)
    {
        ans = function_add(a, absb);
        ans.flag = 1;
        return ans;
    }
    ans = a;
    for (int i = 1; i <= ans.len; i++)
    {
        ans.num[i] -= b.num[i];
        if (ans.num[i] < 0)
        {
            ans.num[i] += 10000;
            ans.num[i + 1] -= 1;
        }
    }
    while (ans.len > 0 && ans.num[ans.len] == 0)
        ans.len--;
    return ans;
}
BigInt function_mul(BigInt a, BigInt b)
{
    BigInt ans;
    BigInt absa, absb;
    absa = BigAbs(a);
    absb = BigAbs(b);
    if (a.flag == 0 && b.flag == 1)
    {
        ans = function_mul(a, absb);
        ans.flag = 1;
        return ans;
    }
    if (a.flag == 1 && b.flag == 0)
    {
        ans = function_mul(absa, b);
        ans.flag = 1;
        return ans;
    }
    if (a.flag == 1 && b.flag == 1)
    {
        ans = function_mul(absa, absb);
        return ans;
    }
    ans.len = a.len + b.len - 1;
    for (int i = 1; i <= a.len; i++)
    {
        for (int j = 1; j <= b.len; j++)
        {
            ans.num[i + j - 1] += a.num[i] * b.num[j];
            ans.num[i + j] += ans.num[i + j - 1] / 10000;
            ans.num[i + j - 1] %= 10000;
        }
    }
    if (ans.num[ans.len + 1])
        ans.len++;
    return ans;
}
BigInt function_div(BigInt a, BigInt b)
{
    BigInt absa, absb;
    BigInt x, y;
    absa = BigAbs(a);
    absb = BigAbs(b);
    if ((a.flag == 0 && b.flag == 1) || (a.flag == 1 && b.flag == 0))
    {
        x = function_div(absa, absb);
        x.flag = 1;
        return x;
    }
    if (a.flag == 1 && b.flag == 1)
    {
        x = function_div(absa, absb);
        return x;
    }
    for (int i = a.len; i >= 1; i--)
    {
        y.ad(a.num[i]);
        y.re();
        while (y >= b)
        {
            y = function_sub(y, b);
            x.num[i]++;
        }
        y.re();
    }
    x.len = a.len;
    while (x.len > 0 && x.num[x.len] == 0)
        x.len--;
    return x;
}
//四则运算
BigInt operator+(BigInt a, BigInt b)
{
    return function_add(a, b);
}
BigInt operator+=(BigInt &a, BigInt &b)
{
    return a = a + b;
}
BigInt operator-(BigInt a, BigInt b)
{
    return function_sub(a, b);
}
BigInt operator-=(BigInt &a, BigInt &b)
{
    return a = a - b;
}
BigInt operator*(BigInt a, BigInt b)
{
    return function_mul(a, b);
}
BigInt operator*=(BigInt &a, BigInt &b)
{
    return a = a * b;
}
BigInt operator/(BigInt a, BigInt b)
{
    return function_div(a, b);
}
BigInt operator/=(BigInt &a, BigInt &b)
{
    return a = a / b;
}
BigInt operator%(BigInt a, BigInt b)
{
    BigInt temp = a / b;
    BigInt ans = temp * b;
    ans = a - ans;
    return ans;
}
BigInt operator%=(BigInt &a, BigInt &b)
{
    return a = a % b;
}

BigInt gcd(BigInt a, BigInt b)
{
    for (; b != 0;)
    {
        a %= b;
        swap(a, b);
    }
    return a;
}

BigInt a, b;

int main()
{
    cin >> a >> b;
    cout << gcd(a, b) << endl;
    return 0;
}