#include <cstdio>
#include <iostream>

using namespace std;

int x[10005], xl = 1;
int y[10005], yl = 1;
char str[10005];
int base = 1e8;
bool xy = 0;
int two;

void print(int x)
{
    if (x > 9)
        print(x / 10);
    putchar(x % 10 + '0');
    return;
}

void read(bool flag)
{
    int ws = 0;
    char ch = getchar();
    while (ch < '0' || ch > '9')
        ch = getchar();
    while (ch >= '0' && ch <= '9')
        str[++ws] = ch, ch = getchar();
    if (flag)
    {
        for (int i = ws, j = 1; i >= 1; i--, j *= 10)
        {
            if (j == base)
                j = 1, xl++;
            x[xl] += (str[i] - '0') * j;
        }
    }
    else
    {
        for (int i = ws, j = 1; i >= 1; i--, j *= 10)
        {
            if (j == base)
                j = 1, yl++;
            y[yl] += (str[i] - '0') * j;
        }
    }
    return;
}

void putzero(int x)
{
    while (x * 10 < base)
    {
        putchar('0');
        x *= 10;
    }
    return;
}

void putout()
{
    if (xy)
    {
        print(y[yl]);
        for (int i = yl - 1; i >= 1; i--)
        {
            putzero(y[i]);
            print(y[i]);
        }
    }
    else
    {
        print(x[xl]);
        for (int i = xl - 1; i >= 1; i--)
        {
            putzero(x[i]);
            print(x[i]);
        }
    }
    putchar('\n');
    return;
}

bool comp()
{
    if (xl != yl)
    {
        if (xl < yl)
            return 1;
        else
            return 0;
    }
    for (int i = xl; i >= 1; i--)
        if (x[i] != y[i])
        {
            if (x[i] < y[i])
                return 1;
            else
                return 0;
        }
    return 0;
}

bool cmp()
{
    if (xy)
    {
        for (int i = 1; i <= xl; i++)
            if (y[yl - i + 1] != x[xl - i + 1])
            {
                if (y[yl - i + 1] < x[xl - i + 1])
                    return 1;
                else
                    return 0;
            }
    }
    else
    {
        for (int i = 1; i <= yl; i++)
            if (x[xl - i + 1] != y[yl - i + 1])
            {
                if (x[xl - i + 1] < y[yl - i + 1])
                    return 1;
                else
                    return 0;
            }
    }
    return 0;
}

void sub()
{
    bool up = 0;
    if (xy)
    {
        for (int i = 1; i <= xl || up; i++)
        {
            y[i] -= x[i] + up;
            if (y[i] < 0)
                y[i] += base, up = 1;
            else
                up = 0;
        }
        while (!y[yl] && yl)
            yl--;
    }
    else
    {
        for (int i = 1; i <= yl || up; i++)
        {
            x[i] -= y[i] + up;
            if (x[i] < 0)
                x[i] += base, up = 1;
            else
                up = 0;
        }
        while (!x[xl] && xl)
            xl--;
    }
    return;
}

void mod()
{
    if (xy)
    {
        bool down = 0;
        while (yl >= xl)
        {
            if (cmp())
                down = 1;
            if (yl - down < xl)
                break;
            bool can = 1;
            while (can)
            {
                bool up = 0;
                for (int i = 1; i <= xl || up; i++)
                {
                    y[yl - down - xl + i] -= x[i] + up;
                    if (y[yl - down - xl + i] < 0)
                        y[yl - down - xl + i] += base, up = 1;
                    else
                        up = 0;
                    if (y[yl - down - xl + i] < x[i])
                        can = 0;
                    else if (y[yl - down - xl + i] > x[i])
                        can = 1;
                }
                if (y[yl - down + 1])
                    can = 1;
            }
            while (yl && !y[yl])
                yl--;
            down = 0;
        }
    }
    else
    {
        bool down = 0;
        while (xl >= yl)
        {
            if (cmp())
                down = 1;
            if (xl - down < yl)
                break;
            bool can = 1;
            while (can)
            {
                bool up = 0;
                for (int i = 1; i <= yl || up; i++)
                {
                    x[xl - down - yl + i] -= y[i] + up;
                    if (x[xl - down - yl + i] < 0)
                        x[xl - down - yl + i] += base, up = 1;
                    else
                        up = 0;
                    if (x[xl - down - yl + i] < y[i])
                        can = 0;
                    else if (x[xl - down - yl + i] > y[i])
                        can = 1;
                }
                if (x[xl - down + 1])
                    can = 1;
            }
            while (xl && !x[xl])
                xl--;
            down = 0;
        }
    }
    xy = !xy;
    return;
}

void mul()
{
    bool up = 0;
    if (xy)
    {
        for (int i = 1; i <= yl || up; i++)
        {
            y[i] = y[i] << 1 | up;
            if (y[i] >= base)
                y[i] -= base, up = 1;
            else
                up = 0;
        }
        while (y[yl + 1])
            yl++;
    }
    else
    {
        for (int i = 1; i <= xl || up; i++)
        {
            x[i] = x[i] << 1 | up;
            if (x[i] >= base)
                x[i] -= base, up = 1;
            else
                up = 0;
        }
        while (x[xl + 1])
            xl++;
    }
    return;
}

void xdiv()
{
    bool down = 0;
    for (int i = xl; i >= 1; i--)
    {
        x[i] += (down ? base : 0);
        down = x[i] & 1;
        x[i] >>= 1;
    }
    if (!x[xl])
        xl--;
    return;
}

void ydiv()
{
    bool down = 0;
    for (int i = yl; i >= 1; i--)
    {
        y[i] += (down ? base : 0);
        down = y[i] & 1;
        y[i] >>= 1;
    }
    if (!y[yl])
        yl--;
    return;
}

int main()
{
    read(1);
    read(0);
    while (!(x[1] & 1) && !(y[1] & 1))
        xdiv(), ydiv(), two++;
    while (xl && yl)
    {
        while (!(x[1] & 1))
            xdiv();
        while (!(y[1] & 1))
            ydiv();
        xy = comp();
        sub(); //mod();
    }
    xy = !xl;
    while (two--)
        mul();
    putout();
    return 0;
}
