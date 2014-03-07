#include "stdio.h"
#include "stdlib.h"
#include "matrixsorter.h"

void fillMatrix(int **array, int rows, int cols)
{
    for (int i = 0; i < rows; i++)
    {
        array[i] = new int[cols];
        for (int j = 0; j < cols; j++)
            array[i][j] = (rand() % 20) - 10;
    }
}

int main()
{
    int rows, cols = 0;
    printf("Rows:\n");
    scanf("%d", &rows);
    printf("Cols:\n");
    scanf("%d", &cols);
    int **array = new int*[rows];
    fillMatrix(array, rows, cols);
    MatrixSorter *sorter = new MatrixSorter(array, rows, cols);
    printf("Before sort:\n");
    sorter->print();
    printf("Arter sort:\n");
    sorter->sort();
    sorter->print();
    delete sorter;
    return 0;
}

