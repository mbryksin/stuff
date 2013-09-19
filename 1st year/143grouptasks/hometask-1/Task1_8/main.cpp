#include <iostream>
#include <string.h>
#include <stdio.h>
using namespace std;

int iteration (int m)
{
    int result = 1;
    for (int i = 0; i < m; i++)
    {
        result *= i+1;
    }
    return(result);
}

int recoursion (int m)
{
    if (m == 0 || m == 1)
    {
        return (1);
    }
    else
    {
        return(m * recoursion(m-1));
    }
}

int main()
{
    cout << "n!\n";
    cout << "Write n: ";
    int n = 0;
    cin >> n;
    cout << "Iteration method. Result = " << iteration(n) << endl;
    cout << "Recoursion method. Result = " << recoursion(n) << endl;
}

