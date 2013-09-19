#include <iostream>
using namespace std;

int main()
{
    int const n = 28;
    int const m = 9;
    int a[n];
    for (int i = 0; i < n - 1; i++)
    {
        a[i] = 0;
    }

    for (int i = 0; i <= m; i++)
    {
        for (int j = 0; j <= m; j++)
        {
            for (int k = 0; k <= m; k++)
            {
                a[i + j + k]++;
            }
        }
    }

    int r = 0;
    for (int i = 0; i < n - 1; i++)
    {
        r = r + a[i] * a[i];
    }
    cout << "Lucky tikets: " << r;
}
