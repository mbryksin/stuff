#include <QtCore/QCoreApplication>
#include <iostream>
#include <string.h>
#include <stdio.h>
using namespace std;

int main()
{
    cout << "Write palindrome:\n";
    int const m = 1000;
    char str[m]={};
    char s[m]={};
    cin.getline(str, m);
    int j = 0;
    for (int i = 0; str[i]; i++)
    {
        if (str[i] != ' ')
        {
            s[j++] = str[i];
        }
    }

    for (j = 0; s[j]; j++)
    {
        s[j] = tolower(s[j]);
    }

    int n = strlen(s);
    for (j = 0; j <= n / 2; j++)
    {
        if (s[j] != s[n - j - 1])
        {
            cout << "False";
            return 0;
        }
    }
    cout << "True";
}
