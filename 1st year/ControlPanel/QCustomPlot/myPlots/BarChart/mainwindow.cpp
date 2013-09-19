#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QCPBars *myBars = new QCPBars(ui->customPlot->xAxis, ui->customPlot->yAxis);
    ui->customPlot->addPlottable(myBars);
    // now we can modify properties of myBars:
    myBars->setName("Pretty bars");
    QVector<double> keyData;
    QVector<double> valueData;
    keyData << 0 << 1 << 2 << 3 << 4;
    valueData << 0 << 2 << 4 << 8 << 0;
    myBars->setData(keyData, valueData);
    ui->customPlot->rescaleAxes();
    ui->customPlot->replot();
}

MainWindow::~MainWindow()
{
    delete ui;
}
