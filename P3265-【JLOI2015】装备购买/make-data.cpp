#include <iostream>
#include <time.h>

using namespace std;

int n, m;

int main()
{
    srand(time(0));
    for (int i = 1; i <= 20; i++)
        rand();
    n = rand() % 500 + 1;
    m = rand() % 500 + 1;
    while (n >= m)
        m = rand() % 500 + 1;
    cout << n << ' ' << m << endl;
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= m; j++)
            cout << rand() % m + 1 << ' ';
        cout << endl;
    }
    for (int i = 1; i <= n; i++)
        cout << rand() % 1000 + 1 << ' ';
    cout << endl;
    return 0;
}