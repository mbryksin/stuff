#include <iostream>

using namespace std;

int rigth (int j, int i)
{
    int checker = 1;
    for (int h = 2; h <= j; h++)
    {
        if (j % h == 0 && i % h == 0)
        {
            checker = 0;
        }
    }
    return checker;
}

int main()
{
    /*Fractions*/
    cout << "Write N:" << endl;
    int n = 0;
    cin >> n;
    int count = 0;
    for (int i = 2; i <= n; i++)
    {
        for (int j = 1; j < i; j++)
        {

            if ((i % j != 0 || j == 1) && (rigth(j, i) == 1))
            {
                count++;
                cout << j << "/" << i << " ";
            }
        }
    }
    cout << endl;
    cout << "count: "<< count << endl;
    return 0;
}

