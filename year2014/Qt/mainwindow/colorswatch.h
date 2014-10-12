#pragma once

#include <QDockWidget>

QT_FORWARD_DECLARE_CLASS(QAction)
QT_FORWARD_DECLARE_CLASS(QActionGroup)
QT_FORWARD_DECLARE_CLASS(QMenu)

class ColorSwatch : public QDockWidget
{
    Q_OBJECT

public:
    explicit ColorSwatch(QWidget *parent = 0, Qt::WindowFlags flags = 0);
    QMenu *menu;

protected:
    virtual void contextMenuEvent(QContextMenuEvent *event);
    virtual void resizeEvent(QResizeEvent *e);

};
