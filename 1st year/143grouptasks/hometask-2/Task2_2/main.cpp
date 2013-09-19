#include <iostream>

using namespace std;

int degree (int a, int n)
{
    int rez = 1;
    while (n > 0)
    {
        if (n % 2 == 0)
        {
            a = a * a;
            n = n / 2;
        }
        else
        {
            rez = rez * a;
            n--;
        }
    }
    return rez;
}

int main()
{
    cout << "A^n with O(log(n)):" << endl;
    cout << "Write A and N:" << endl;
    int a = 0;
    cin >> a;
    int n = 0;
    cin >> n;
    cout << degree(a, n) << endl;
    return 0;
}

