#include <cstdio>
#include <windows.h>
#include <iostream>

using namespace std;

int main()
{
    for (int i = 1; i <= 10000; i++)
    {
        cout << i << endl;
        system("make-data > data.in");
        system("Main < data.in > Main1.out");
        system("Main-wa < data.in > Main2.out");
        if (system("fc Main1.out Main2.out"))
            break;
    }
    return 0;
}