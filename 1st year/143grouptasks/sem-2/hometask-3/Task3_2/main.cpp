#include <stdio.h>
#include <stdlib.h>
#include "printertofile.h"
#include "printertoconsole.h"

enum Choise
{
    TOFILE,
    TOCONSOLE
};

void fillArray(int **array, int size, FILE *in)
{
    for (int i = 0; i < size; i++)
    {
        array[i] = new int[size];
        for (int j = 0; j < size; j++)
            fscanf(in, "%d", &array[i][j]);
    }
}

void makeChoise(Printer *&printer, int **array, int size)
{
    printf("----------------------\n");
    printf("What kind of print do you want to use?\n");
    printf("0 - To File\n");
    printf("1 - To Console\n");
    Choise x = TOCONSOLE;
    scanf("%d", &x);
    switch (x)
    {
    case TOFILE:
    {
        printer = new PrinterToFile(array, size);
        break;
    }
    case TOCONSOLE:
        printer = new PrinterToConsole(array, size);
        break;
    default:
        makeChoise(printer, array, size);
        return;
    }
}

int main()
{
    int size = 0;
    FILE *in = fopen("in.txt", "r");
    fscanf(in, "%d", &size);
    int **array = new int*[size];
    fillArray(array, size, in);

    Printer *printer = NULL;
    makeChoise(printer, array, size);
    printer->printMatrix();
    printer->printSpiral();
    delete printer;
    delete[] array;
    fclose(in);
    return 0;
}

