#include <iostream>
#include <string.h>
#include <stdio.h>

using namespace std;

int main()
{
    cout << "All simple elements <= N\n";
    cout << "Write N: ";
    int m = 0;
    cin >> m;
    int const n = m;
    bool b[n + 1];
    for (int i = 1; i <= n; i++)
    {
        b[i] = true;
    }

    for (int i = 2; i <= n; i++)
    {
        if (b[i])
        {
            for (int j = i + 1; j <= n; j++)
            {
                if (j % i == 0)
                {
                    b[j] = false;
                }
            }
        }
    }
    cout << "Result: " << endl;
    for (int i = 1; i <= n; i++)
    {
        if (b[i])
        {
            cout << i << " ";
        }
    }
    return 0;
}

