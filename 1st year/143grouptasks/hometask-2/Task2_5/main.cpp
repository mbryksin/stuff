#include <iostream>

using namespace std;

void add_element (int a[], int k, int n)
{
    int new_element = a[k];
    while(k <= n / 2)
    {
        int child = 2 * k;
        if (child < n && a[child] < a[child + 1])
        {
            child++;
        }
        if (new_element >= a[child])
        {
            break;
        }
        a[k] = a[child];
        k = child;
    }
    a[k] = new_element;
}

void heapsort(int a[], int n)
{
    for(int i = n / 2; i >= 1; i--)
    {
        add_element(a, i, n);
    }
    for(int i = n; i > 1; i--)
    {
        int swap = a[i];
        a[i] = a[1];
        a[1] = swap;
        add_element(a, 1, i - 1);
    }
}

int const MAX = 100500;

int main()
{
    /*Heapsort*/
    int a[MAX]={};
    cout << "Count of elements:" << endl;
    int n = 0;
    cin >> n;
    cout << "Write Array:" << endl;
    for (int i = 1; i <= n; i++)
    {
        cin >> a[i];
    }
    heapsort(a, n);
    for (int i = 1; i <= n; i++)
    {
        cout << a[i] << " ";
    }
    cout << endl;
    return 0;
}

