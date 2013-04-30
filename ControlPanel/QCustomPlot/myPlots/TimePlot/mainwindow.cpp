#include "mainwindow.h"
#include "ui_mainwindow.h"
#define customPlot ui->customPlot

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    // set locale to english, so we get english month names:
    customPlot->setLocale(QLocale(QLocale::English, QLocale::UnitedKingdom));
    // seconds of current time, we'll use it as starting point in time for data:
    double now = QDateTime::currentDateTime().toTime_t();
    srand(8); // set the random seed, so we always get the same random data
    // create multiple graphs:
    for (int gi=0; gi<5; ++gi)
    {
      customPlot->addGraph();
      QPen pen;
      pen.setColor(QColor(0, 0, 255, 200));
      customPlot->graph()->setLineStyle(QCPGraph::lsLine);
      customPlot->graph()->setPen(pen);
      customPlot->graph()->setBrush(QBrush(QColor(255/4.0*gi,160,50,150)));
      // generate random walk data:
      QVector<double> time(250), value(250);
      for (int i=0; i<250; ++i)
      {
        time[i] = now + 24*3600*i;
        if (i == 0)
          value[i] = (i/50.0+1)*(rand()/(double)RAND_MAX-0.5);
        else
          value[i] = fabs(value[i-1])*(1+0.02/4.0*(4-gi)) + (i/50.0+1)*(rand()/(double)RAND_MAX-0.5);
      }
      customPlot->graph()->setData(time, value);
    }
    // configure bottom axis to show date and time instead of number:
    customPlot->xAxis->setTickLabelType(QCPAxis::ltDateTime);
    customPlot->xAxis->setDateTimeFormat("MMMM\nyyyy");
    // set a more compact font size for bottom and left axis tick labels:
    customPlot->xAxis->setTickLabelFont(QFont(QFont().family(), 8));
    customPlot->yAxis->setTickLabelFont(QFont(QFont().family(), 8));
    // set a fixed tick-step to one tick per month:
    customPlot->xAxis->setAutoTickStep(false);
    customPlot->xAxis->setTickStep(2628000); // one month in seconds
    customPlot->xAxis->setSubTickCount(3);
    // apply manual tick and tick label for left axis:
    QVector<double> tickVector;
    QVector<QString> tickLabels;
    tickVector << 5 << 55;
    tickLabels << "Not so\nhigh" << "Very\nhigh";
    customPlot->yAxis->setAutoTicks(false);
    customPlot->yAxis->setAutoTickLabels(false);
    customPlot->yAxis->setTickVector(tickVector);
    customPlot->yAxis->setTickVectorLabels(tickLabels);
    // set axis labels:
    customPlot->xAxis->setLabel("Date");
    customPlot->yAxis->setLabel("Random wobbly lines value");
    // make top and right axes visible but without ticks and labels:
    customPlot->xAxis2->setVisible(true);
    customPlot->yAxis2->setVisible(true);
    customPlot->xAxis2->setTicks(false);
    customPlot->yAxis2->setTicks(false);
    customPlot->xAxis2->setTickLabels(false);
    customPlot->yAxis2->setTickLabels(false);
    // set axis ranges to show all data:
    customPlot->xAxis->setRange(now, now+24*3600*249);
    customPlot->yAxis->setRange(0, 60);
    // activate legend and position it in top left corner:
    customPlot->legend->setVisible(true);
    customPlot->legend->setPositionStyle(QCPLegend::psTopLeft);
}

MainWindow::~MainWindow()
{
    delete ui;
}
