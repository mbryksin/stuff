#pragma once
#include <QMainWindow>
#include <QTextEdit>

class ToolBar;

QT_FORWARD_DECLARE_CLASS(QMenu)
QT_FORWARD_DECLARE_CLASS(QSignalMapper)

class MainWindow : public QMainWindow
{
    Q_OBJECT

    ToolBar *toolBar;
    QSignalMapper *mapper;
    QList<QDockWidget*> widgets;

public:
    MainWindow(const QMap<QString, QSize> &customSizeHints,
                QWidget *parent = 0, Qt::WindowFlags flags = 0);

protected:
    void showEvent(QShowEvent *event);

public slots:

    void setCorner(int id);

    void createDockWidget();
    void destroyDockWidget();

private:

};
