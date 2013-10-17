#pragma once

#include <QWidget>
#include <QLabel>
#include "lib/qcustomplot.h"

class CustomPlot : public QWidget
{
    Q_OBJECT
public:
    CustomPlot(QWidget *parent = 0);
    void clearData();
    QLabel              label;
    QLabel              numbers;

protected:
    void plotInit();
    void addGraph(int n, QColor color);

signals:
    void textChanged(QString);

public slots:
    void drawData(QVector<double> args);

private:
    QCustomPlot         *plot;
};
