#include <QtGui/QApplication>
#include "filefinder.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    FileFinder w;
    w.show();
    
    return a.exec();
}
