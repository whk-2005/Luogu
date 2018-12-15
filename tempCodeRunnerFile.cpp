#include <iostream>
#include <string>

using namespace std;

int main()
{
    system("chcp");
    cout << "是否更改" << endl;
    string in;
    cin >> in;
    if (in == "no")
        return 0;
    else
    {
        string s;
        if (in == "gbk")
            s = "chcp 936";
        if (in == "utf8")
            s = "chcp 65001";
        system(s.c_str());
    }
    return 0;
}