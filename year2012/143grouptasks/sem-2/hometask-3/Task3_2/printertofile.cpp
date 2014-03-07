#include "printertofile.h"

PrinterToFile::PrinterToFile(int **array, int size)
    :Printer(array, size)
{
    char *filename = new char[1000];
    printf("Write filename:\n");
    ///You can use out.txt or another
    scanf("%s", filename);
    pOut = fopen(filename, "w");
    delete[] filename;
}

PrinterToFile::~PrinterToFile()
{
    fclose(pOut);
}

void PrinterToFile::printEndl()
{
    fprintf(pOut, "\n");
}

void PrinterToFile::printLine()
{
    fprintf(pOut, "-------------------------\n");
}

void PrinterToFile::printOne(int i, int j)
{
    fprintf(pOut, "%d ", pArray[i][j]);
}
