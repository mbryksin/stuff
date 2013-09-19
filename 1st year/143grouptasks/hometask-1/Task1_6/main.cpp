#include <iostream>
#include <stdio.h>
#include <string.h>

using namespace std;

int main()
{
    cout << "Write S: ";
    int const g = 10000;
    char s[g]={};
    cin.getline(s,g);
    cout << "Write S1: ";
    char s1[g]={};
    cin.getline(s1,g);
    int m = strlen(s1);
    int n = strlen(s);
    int i = 0;
    int j = 0;
    int count = 0;
    bool f = true;
    while (i < n)
    {
        do
        {
            if (s[i] != s1[j])
            {
                f = false;
                j = 0;
            }
            else
            {
                f = true;
                j++;
            }
            if (i == n-1 && j < m)
            {
                f = false;
            }
            i++;
        } while (j < m && i < n);

        j = 0;
        if (f)
        {
            count++;
        }
    }
    cout << "S1 in string S = " << count << " times.";
}

