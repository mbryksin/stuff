#pragma once

#include <QToolBar>

QT_FORWARD_DECLARE_CLASS(QAction)
QT_FORWARD_DECLARE_CLASS(QToolBox)
QT_FORWARD_DECLARE_CLASS(QMenu)
QT_FORWARD_DECLARE_CLASS(QLabel)

class ToolBar : public QToolBar
{
    Q_OBJECT

public:
    ToolBar(const QString &title, QWidget *parent);
    QToolBox* menuBox;
    QAction* accelAction;
    QAction* gyroAction;

protected:
    void enterEvent(QEvent*);
    void leaveEvent(QEvent*);

private:
    void insertToolBox();

private slots:

};
