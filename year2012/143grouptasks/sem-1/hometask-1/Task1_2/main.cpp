#include <QtCore/QCoreApplication>
#include <iostream>
using namespace std;

int main()
{
    cout << "A = p * B + r" << endl;
    cout << "Write A: ";
    int a = 0;
    cin >> a;
    cout << "Write B: ";
    int b = 0;
    cin >> b;

    int p = 0;
    do {
        ++p;
    } while (a - b * p >= b);

    cout << "p = ";
    cout << p << endl;
    cout << "r = ";
    cout << a - p * b;
    cin >> a;
}
