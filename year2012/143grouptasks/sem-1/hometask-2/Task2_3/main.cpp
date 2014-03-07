#include <iostream>

using namespace std;

void printVariation (int a[], int n)
{
    for (int i = 1; i <= n; i++)
    {
        int j = 0;
        while (j < a[i])
        {
            cout << i << " ";
            j++;
        }
    }
    cout << endl;
}

void initialize (int a[], int n)
{
    for (int i = 1; i <= n; i++)
    {
        a[i] = 0;
    }
}

void rechange (int a[], int n)
{
    int sum = a[1];
    int position = 0;
    for (int i = 2; i <= n; i++)
    {
        if (sum >= i)
        {
            a[i]++;
            sum = sum - i;
            position = i;
            break;
        }
        else
        {
            sum += a[i]*i;
        }
    }
    initialize(a, position - 1);
    for (int j = position - 1; j >= 1 && sum > 0; j)
    {
        if (j == 1 || (sum == n - position && a[position] == 1))
        {
            a[1] = sum;
            sum = 0;
        }
        else if (sum > j)
        {
            a[j]++;
            sum = sum - j;
        }
        else
        {
            j--;
        }
    }
}

int const MAX = 100500;

void showResult (int n)
{
    int a[MAX];
    if (n == 0 || n == 1)
    {
        cout << n << endl;
    }
    else
    {
        initialize(a, n);
        a[1] = n;
        while (a[n] != 1)
        {
            printVariation (a, n);
            rechange(a, n);
        }
        printVariation (a, n);
    }
}

int main()
{
    /*Different sums*/
    cout << "Write N:" << endl;
    int n = 0;
    cin >> n;
    showResult(n);
    return 0;
}

