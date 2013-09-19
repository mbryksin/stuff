#include <QtGui/QApplication>
#include "sender.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Sender w(0,2626);
    Sender w2(3.14,2323);
    Sender w3(1.57, 2121);
    w.show();
    w2.show();
    w3.show();
    return a.exec();
}
