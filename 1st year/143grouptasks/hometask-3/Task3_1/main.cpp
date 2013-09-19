#include <iostream>

void addElement (int a[], int k, int const n)
{
    int newElement = a[k];
    while(k <= n / 2)
    {
        int child = 2 * k;
        if (child < n && a[child] < a[child + 1])
        {
            child++;
        }
        if (newElement >= a[child])
        {
            break;
        }
        a[k] = a[child];
        k = child;
    }
    a[k] = newElement;
}

void heapsort(int a[], int const n)
{
    for(int i = n / 2; i >= 1; i--)
    {
        addElement(a, i, n);
    }
    for(int i = n; i > 1; i--)
    {
        int swap = a[i];
        a[i] = a[1];
        a[1] = swap;
        addElement(a, 1, i - 1);
    }
}

int findMaximum (int a[], int const n, bool &f)
{
    int maximum = a[n];
    for (int i = n - 1; i > 0; i--)
    {
        if (a[i] == maximum)
        {
            f = true;
            return maximum;
        }
        else
        {
            maximum = a[i];
        }
    }
    return -1488;
}

int const max = 100500;

int main()
{
    /*Double element*/
    int a[max]={};
    std::cout << "Count of elements:\n";
    int n = 0;
    std::cin >> n;
    std::cout << "Write Array:\n";
    for (int i = 1; i <= n; i++)
    {
        std::cin >> a[i];
    }
    heapsort(a, n);
    bool f = false;
    int result = findMaximum(a, n, f);

    if (f)
    {
        std::cout << "Max double element = "<< result << std::endl;
    }
    else
    {
        std::cout << "You shoot your leg!" << std::endl;
    }
    return 0;
}

