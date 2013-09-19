#include <stdio.h>

int main(void)
{
    int i = 0;
    int sum = 0;
    for (i = 0; i < 1000; i++)
    {
        if ((i % 5 == 0) || (i % 3 == 0))
        {
            sum += i;
        }
    }
    printf("result = %d\n", sum);
    return 0;
}
