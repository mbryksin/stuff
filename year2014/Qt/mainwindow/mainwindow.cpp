#include "mainwindow.h"
#include "toolbar.h"

#include <QAction>
#include <QDockWidget>
#include <QLayout>
#include <QMenu>
#include <QMenuBar>
#include <QStatusBar>
#include <QTextEdit>
#include <QFile>
#include <QDataStream>
#include <QFileDialog>
#include <QMessageBox>
#include <QSignalMapper>
#include <QApplication>
#include <QPainter>
#include <QMouseEvent>
#include <QLineEdit>
#include <QComboBox>
#include <QLabel>
#include <QPushButton>
#include <qdebug.h>

Q_DECLARE_METATYPE(QDockWidget::DockWidgetFeatures)

MainWindow::MainWindow(const QMap<QString, QSize> &customSizeHints,
                        QWidget *parent, Qt::WindowFlags flags)
    : QMainWindow(parent, flags)
{
    setObjectName("MainWindow");
    setWindowTitle("TRIK Telemetry Dashboard");
    toolBar = new ToolBar("Tool Bar", this);
    addToolBar(Qt::LeftToolBarArea, toolBar);

    statusBar()->showMessage(tr("Ready"));

    DockOptions opts;
    opts |= AllowNestedDocks;
    opts |= AnimatedDocks;
    QMainWindow::setDockOptions(opts);

    mapper = new QSignalMapper(this);
    connect(mapper, SIGNAL(mapped(int)), this, SLOT(setCorner(int)));

    connect(toolBar->accelAction, SIGNAL(triggered()), this, SLOT(createDockWidget()));

}


QAction *addAction(QMenu *menu, const QString &text, QActionGroup *group, QSignalMapper *mapper,
                    int id)
{
    bool first = group->actions().isEmpty();
    QAction *result = menu->addAction(text);
    result->setCheckable(true);
    result->setChecked(first);
    group->addAction(result);
    QObject::connect(result, SIGNAL(triggered()), mapper, SLOT(map()));
    mapper->setMapping(result, id);
    return result;
}

void MainWindow::setCorner(int id)
{
    switch (id) {
        case 0:
            QMainWindow::setCorner(Qt::TopLeftCorner, Qt::TopDockWidgetArea);
            break;
        case 1:
            QMainWindow::setCorner(Qt::TopLeftCorner, Qt::LeftDockWidgetArea);
            break;
        case 2:
            QMainWindow::setCorner(Qt::TopRightCorner, Qt::TopDockWidgetArea);
            break;
        case 3:
            QMainWindow::setCorner(Qt::TopRightCorner, Qt::RightDockWidgetArea);
            break;
        case 4:
            QMainWindow::setCorner(Qt::BottomLeftCorner, Qt::BottomDockWidgetArea);
            break;
        case 5:
            QMainWindow::setCorner(Qt::BottomLeftCorner, Qt::LeftDockWidgetArea);
            break;
        case 6:
            QMainWindow::setCorner(Qt::BottomRightCorner, Qt::BottomDockWidgetArea);
            break;
        case 7:
            QMainWindow::setCorner(Qt::BottomRightCorner, Qt::RightDockWidgetArea);
            break;
    }
}

void MainWindow::showEvent(QShowEvent *event)
{
    QMainWindow::showEvent(event);
}

void MainWindow::createDockWidget()
{
    QDockWidget *dw = new QDockWidget();
    QAction* action = (QAction*)sender();
    dw->setObjectName(action->text());
    dw->setFeatures(dw->features() | QDockWidget::DockWidgetClosable);
    dw->setFeatures(dw->features() | QDockWidget::DockWidgetMovable);
    dw->setFeatures(dw->features() | QDockWidget::DockWidgetFloatable);
    dw->setAllowedAreas(Qt::AllDockWidgetAreas);
    dw->setWindowTitle(action->text());
    dw->setWidget(new QTextEdit);

    addDockWidget(Qt::TopDockWidgetArea, dw);
    //connect(dw->closeEvent(), SIGNAL(triggered(bool)) , this, SLOT(destroyDockWidget()));
    widgets.append(dw);
}

void MainWindow::destroyDockWidget()
{
 //   int index = destroyDockWidgetMenu->actions().indexOf(action);
  //  delete widgets.takeAt(index);
    //QDockWidget *dw = (QDockWidget*) sender();
    //action->deleteLater();
    qDebug()<<"delete";
}
