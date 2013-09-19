#include <iostream>
using namespace std;

int main()
{
    cout << "Write X: ";
    int x = 0;
    cin >> x;
    int a = x * x;
    int s = (a + x) * (x + 1)+1;
    cout << "Result: ";
    cout << s << endl;
    cin.get();
    return 0;
}
