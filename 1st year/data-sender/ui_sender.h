/********************************************************************************
** Form generated from reading UI file 'sender.ui'
**
** Created: Wed Jul 3 13:50:21 2013
**      by: Qt User Interface Compiler version 4.8.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SENDER_H
#define UI_SENDER_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QMainWindow>
#include <QtGui/QMenuBar>
#include <QtGui/QPushButton>
#include <QtGui/QStatusBar>
#include <QtGui/QToolBar>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Sender
{
public:
    QWidget *centralWidget;
    QLabel *label;
    QPushButton *button;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *Sender)
    {
        if (Sender->objectName().isEmpty())
            Sender->setObjectName(QString::fromUtf8("Sender"));
        Sender->resize(191, 169);
        centralWidget = new QWidget(Sender);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        label = new QLabel(centralWidget);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(40, 20, 121, 21));
        QFont font;
        font.setPointSize(12);
        font.setBold(true);
        font.setWeight(75);
        label->setFont(font);
        button = new QPushButton(centralWidget);
        button->setObjectName(QString::fromUtf8("button"));
        button->setGeometry(QRect(40, 50, 101, 31));
        Sender->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(Sender);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 191, 21));
        Sender->setMenuBar(menuBar);
        mainToolBar = new QToolBar(Sender);
        mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
        Sender->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(Sender);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        Sender->setStatusBar(statusBar);

        retranslateUi(Sender);

        QMetaObject::connectSlotsByName(Sender);
    } // setupUi

    void retranslateUi(QMainWindow *Sender)
    {
        Sender->setWindowTitle(QApplication::translate("Sender", "Sender", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("Sender", "Data Sender", 0, QApplication::UnicodeUTF8));
        button->setText(QApplication::translate("Sender", "Set Connection", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class Sender: public Ui_Sender {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SENDER_H
