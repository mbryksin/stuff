#include <QtCore/QCoreApplication>
#include <iostream>
#include <string.h>
using namespace std;

int main()
{
    cout << "Write '(' or ')':\n";
    int const m = 1000;
    char str[m];
    cin.getline(str, m);
    int k = 0;
    bool f = true;
    for (int i = 0; str[i] && (f); i++)
    {
        if (str[i] == '(')
        {
            k++;
        }
        else
        {
            if (str[i] == ')')
            {
                k--;
            }
        }
        if (k < 0)
        {
            f = false;
        }
    }

    if (f && k == 0)
    {
        cout << "True";
    }
    else
    {
        cout << "False";
    }
}
