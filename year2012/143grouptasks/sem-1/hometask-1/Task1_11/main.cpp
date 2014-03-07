#include <iostream>

using namespace std;

void qSort (int x[], int left, int right)
{
    int i = left;
    int j = right;
    int m = x[(i + j)/ 2];
    while (i <= j)
    {
        while (x[i] < m)
        {
            i++;
        }
        while (x[j] > m)
        {
            j--;
        }
        if (i <= j)
        {
            int rotate = x[i];
            x[i] = x[j];
            x[j] = rotate;
            i++;
            j--;
        }
    }
    if (left < j)
    {
        qSort(x, left, j);
    }
    if (i < right)
    {
        qSort(x, i, right);
    }
}

int main()
{
    cout << "Write element's number: ";
    int n = 0;
    cin >> n;
    cout << "Write array:\n";
    int const g = 10000;
    int x[g];
    for (int i = 0; i < n; i++)
    {
        cin >> x[i];
    }

    qSort (x, 0, n - 1);

    for (int i = 0; i < n; i++)
    {
        cout << x[i] << " ";
    }
    return 0;
}

