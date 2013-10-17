#include "customplot.h"
#include <QGridLayout>

CustomPlot::CustomPlot(QWidget *parent) :
    QWidget(parent)
{
    connect(this, SIGNAL(textChanged(QString)), &label, SLOT(setText(QString)));
    plot = new QCustomPlot();
    label.setAlignment(Qt::AlignCenter);
    numbers.setAlignment(Qt::AlignCenter);
    plot->setMinimumSize(400, 300);

    QGridLayout *layout = new QGridLayout;
    layout->addWidget(&label, 0, 0);
    layout->addWidget(&numbers, 1, 0);
    layout->addWidget(plot, 2, 0);
    setLayout(layout);
    setWindowTitle(tr("CustomPlot"));

    plotInit();

    addGraph(0, "red");
    addGraph(1, "green");
    addGraph(2, "blue");
}

void CustomPlot::plotInit()
{
//    include this section to fully disable antialiasing for higher performance:
    /*
    ui->customPlot->setNotAntialiasedElements(QCP::aeAll);
    QFont font;
    font.setStyleStrategy(QFont::NoAntialias);
    ui->customPlot->xAxis->setTickLabelFont(font);
    ui->customPlot->yAxis->setTickLabelFont(font);
    ui->customPlot->legend->setFont(font);
    */
    plot->xAxis->setTickLabelType(QCPAxis::ltDateTime);
    plot->xAxis->setDateTimeFormat("mm:ss");
    plot->xAxis->setAutoTickStep(false);
    plot->xAxis->setTickStep(1);
    plot->setupFullAxesBox();
//    make left and bottom axes transfer their ranges to right and top axes:
    connect(plot->xAxis, SIGNAL(rangeChanged(QCPRange)),
           plot->xAxis2, SLOT(setRange(QCPRange)));
    connect(plot->yAxis, SIGNAL(rangeChanged(QCPRange)),
           plot->yAxis2, SLOT(setRange(QCPRange)));
}

void CustomPlot::addGraph(int n, QColor color)
{
    plot->addGraph();
    plot->graph(2*n)->setPen(QPen(color));
    plot->addGraph();
    plot->graph(2*n+1)->setPen(QPen(color));
    plot->graph(2*n+1)->setLineStyle(QCPGraph::lsNone);
    plot->graph(2*n+1)->setScatterStyle(QCP::ssDisc);
}

void CustomPlot::drawData(QVector<double> args)
{
//    QObject* x = sender();
//    Device* y = static_cast<Device*>(x);
//    int n = y->dev_num;
    QString buf;
    buf.sprintf("%g %g %g", args[0], args[1], args[2]);
    numbers.setText(buf);
    double key = QDateTime::currentDateTime().toMSecsSinceEpoch()/1000.0;
    for (int n = 0; n < args.count(); n++)
    {
        plot->graph(2*n)->addData(key, args[n]);
        plot->graph(2*n+1)->clearData();
        plot->graph(2*n+1)->addData(key, args[n]);
        plot->graph(2*n)->removeDataBefore(key-5);
        plot->graph(2*n)->rescaleValueAxis(true);
        plot->xAxis->setRange(key+0.2, 5, Qt::AlignRight);
        plot->replot();
    }
}

void CustomPlot::clearData()
{
    for (int n = 0; n < 3; n++)
    {
        plot->graph(2*n)->clearData();
        plot->graph(2*n+1)->clearData();
        plot->replot();
    }
}

