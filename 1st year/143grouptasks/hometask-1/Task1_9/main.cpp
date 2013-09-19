#include <QtCore/QCoreApplication>
#include <iostream>
using namespace std;

int main()
{
    cout << "A^n\n";
    cout << "Write A: ";
    int a = 0;
    cin >> a;
    cout << "Write n: ";
    int n = 0;
    cin >> n;
    int r = a;
    for (int i = 0; i < n - 1; i++) {
        r = r * a;
    }
    cout << "Result = ";
    cout << r;
    cin >> a;
}
