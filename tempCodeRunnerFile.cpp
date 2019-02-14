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
#include <windows.h>
#include <time.h>

#define qdo 262 
#define qre 294
#define qmi 330
#define qfa 349
#define qso 392
#define qla 440
#define qsi 494
#define doo 523
#define re 578
#define mi 659
#define fa 698
#define so 784
#define la 880
#define si 988
#define do1 1046
#define re1 1175
#define mi1 1318
#define fa1 1480
#define so1 1568
#define la1 1760
#define si1 1976
#define sqdo 277
#define sqre 311
#define sqfa 370
#define sqso 415
#define sqla 466
#define sdo 554
#define sre 622
#define sfa 740
#define sso 831
#define sla 932
#define sdo1 1046
#define sre1 1245
#define sfa1 1480
#define sso1 1661
#define sla1 1865

using namespace std;

typedef long long ll;

inline void read(int &num)
{
    num = 0;
    int w = 1;
    char ch = getchar();
    if (ch == '-')
        w = -1;
    while (ch < '0' || ch > '9')
    {
        ch = getchar();
        if (ch == '-')
            w = -1;
    }
    while ((ch >= '0' && ch <= '9'))
        num = num * 10 + ch - '0', ch = getchar();
    num = num * w;
}



int main()
{
    Beep(mi, 750);
    Beep(re, 250);
    Beep(doo, 500);
    Beep(re, 500);
    Beep(mi, 500);
    Beep(mi, 500);
    Beep(mi, 1000);
    Beep(re, 500);
    Beep(re, 500);
    Beep(re, 1000);
    Beep(mi, 500);
    Beep(so, 500);
    Beep(so, 1000);
    Beep(mi, 750);
    Beep(re, 250);
    Beep(doo, 500);
    Beep(re, 500);
    Beep(mi, 500);
    Beep(mi, 500);
    Beep(mi, 500);
    Beep(re, 500);
    Beep(re, 500);
    Beep(mi, 500);
    Beep(re, 500);
    Beep(doo, 2000);
    return 0;
}