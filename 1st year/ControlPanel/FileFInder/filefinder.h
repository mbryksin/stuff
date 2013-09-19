#ifndef FILEFINDER_H
#define FILEFINDER_H

#include <QtGui/QWidget>
#include <QLineEdit>
#include <QTextEdit>
#include <QDir>
#include <QApplication>

class FileFinder : public QWidget
{
    Q_OBJECT
    
public:
    FileFinder(QWidget *parent = 0);
    ~FileFinder();
    void start(const QDir& dir);
public slots:
    void slotBrowse();
    void slotFind();
private:
    QLineEdit *m_ptxtDir;
    QLineEdit *m_ptxtMask;
    QTextEdit *m_ptxtResult;
};

#endif // FILEFINDER_H
