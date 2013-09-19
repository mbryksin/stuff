#include "printertoconsole.h"

PrinterToConsole::PrinterToConsole(int **array, int size)
    :Printer(array, size)
{
}

void PrinterToConsole::printEndl()
{
    fprintf(stdout, "\n");
}

void PrinterToConsole::printLine()
{
    fprintf(stdout, "-------------------------\n");
}

void PrinterToConsole::printOne(int i, int j)
{
    fprintf(stdout, "%d ", pArray[i][j]);
}
