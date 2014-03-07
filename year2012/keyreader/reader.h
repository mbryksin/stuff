#ifndef READER_H
#define READER_H

#include <QWidget>
#include <QIODevice>
#include <QFile>
#include <QSocketNotifier>
#include <QPointer>

class QLabel;
class QHBoxLayout;
class Reader : public QWidget
{
    Q_OBJECT
    
public:
    Reader();

private:

    QFile file;
    QLabel *label;
    QHBoxLayout *layout;

protected:
    void keyPressEvent(QKeyEvent *event);
};

#endif // READER_H
