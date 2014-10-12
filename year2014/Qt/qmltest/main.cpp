#include <QApplication>
#include <QtGui>
#include <QToolBox>
#include <QPushButton>
#include <QGridLayout>

int main(int argc, char **argv)
{
    QApplication a(argc, argv);
    QToolBox tb;
    QToolBox *motors = new QToolBox();
    QGridLayout* motorsLayout = new QGridLayout();

    motorsLayout->addItem(new QPushButton("JM1"), 0, 0);
    motorsLayout->addItem(new QPushButton("JM2"), 0, 1);

    motors->addItem(new QPushButton("JM2"), "J2");
    tb.addItem(new QPushButton("Accelerometer"), "3D Sensors");
    tb.addItem(motorsLayout, "Motors");
    tb.addItem(new QPushButton("C"), "Servomotors");
    tb.show();
    return a.exec();
}
