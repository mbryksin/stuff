#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QStringList choices;
    choices << "+" << "-" << "*" << "/";
    ui->comboBox->addItems(choices);

    calc = new Calc();
    connect(ui->spinBox1, SIGNAL(valueChanged(int)), calc, SLOT(changeValue1(int)));
    connect(ui->spinBox2, SIGNAL(valueChanged(int)), calc, SLOT(changeValue2(int)));
    connect(ui->comboBox, SIGNAL(currentIndexChanged(int)), calc, SLOT(changeOperation(int)));
    connect(calc, SIGNAL(resultCalculated(QString)), ui->lineEdit, SLOT(setText(QString)));
}

MainWindow::~MainWindow()
{
    delete ui;
    delete calc;
}


