#include "matrixsorter.h"
#include "stdio.h"

MatrixSorter::MatrixSorter(int **array, int rows, int cols)
    :sArray(array), sRows(rows), sCols(cols)
{
}

MatrixSorter::~MatrixSorter()
{
    for (int i = 0; i < sRows; i++)
        delete[] sArray[i];
    delete[] sArray;
}

void MatrixSorter::print()
{
    printf("------------------\n");
    for (int i = 0; i < sRows; i++)
    {
        for (int j = 0; j < sCols; j++)
            printf("%d ", sArray[i][j]);
        printf("\n");
    }
}

void MatrixSorter::swapCols(int a, int b)
{
    for (int i = 0; i < sRows; i++)
    {
        int x = sArray[i][a];
        sArray[i][a] = sArray[i][b];
        sArray[i][b] = x;
    }
}

void MatrixSorter::sort()
{
    for (int i = 0; i < sCols; i++)
    {
        for (int j = 0; j < sCols - 1; j++)
        {
            if (sArray[0][j] > sArray[0][j + 1])
                swapCols(j, j + 1);
        }
    }
}
