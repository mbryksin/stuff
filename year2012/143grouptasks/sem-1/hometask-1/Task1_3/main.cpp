#include <iostream>
#include <string.h>
#include <stdio.h>
using namespace std;

void rotate(int f, int g, int h, int x[])
{
    int k = 0;
    for (int i = f; i < g; i++)
    {
        k = x[i];
        x[i] = x[h - i];
        x[h - i] = k;
    }
}

int main()
{
    cout << "X[m + n]\n";
    cout << "Write M: ";
    int k = 0;
    cin >> k;
    int const m = k;
    cout << "Write N: ";
    cin >> k;
    int const n = k;
    cout << "Write X:" << endl;
    int x[m + n];
    for (int i = 0; i < m + n; i++)
    {
        cin >> x[i];
    }
    rotate(0, m / 2, m - 1, x);
    rotate(m, (m + m + n)/ 2, m - 1 + m + n, x);
    rotate(0, (m + n)/ 2, m + n - 1, x);
    for (int i = 0; i < n + m; i++)
    {
        cout << x[i] << " ";
    }
}
