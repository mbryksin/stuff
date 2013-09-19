#include <iostream>

using namespace std;

int iteration(int n)
{
    cout << "Iteration method:\n";
    int const m = 10000;
    int a[m]={};
    a[0] = 1;
    a[1] = 1;
    for (int i = 2; i <= n; i++)
    {
        a[i] = a[i - 1] + a[i - 2];
    }
    return a[n];
}

int recursion(int n)
{
    if (n == 1 || n == 0)
    {
        return 1;
    }
    else
    {
        return recursion(n - 1) + recursion(n - 2);
    }
}

int main()
{
    cout << "Write number of Fibonachi (since 0):\n";
    int n = 0;
    cin >> n;
    cout << iteration(n) << endl;
    cout << "Recursion method:\n";
    cout << recursion(n) << endl;
    cout << "\n";
    return 0;
}

