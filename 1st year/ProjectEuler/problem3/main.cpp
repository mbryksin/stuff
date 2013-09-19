#include <iostream>

using namespace std;


int main()
{
    unsigned long long int largefactor = 600851475143;
    for(int i = 2;;)
    {
        if (largefactor <= i)
            break;
        if (largefactor % i == 0)
        {
            largefactor = largefactor / i;
        }
        else
            i++;
    }

    cout << largefactor << endl;

    cin.get();
    return 0;
}
