#include "colorswatch.h"

#include <QAction>
#include <QtEvents>
#include <QFrame>
#include <QMainWindow>
#include <QMenu>
#include <QPainter>
#include <QImage>
#include <QColor>
#include <QDialog>
#include <QGridLayout>
#include <QSpinBox>
#include <QLabel>
#include <QPainterPath>
#include <QPushButton>
#include <QHBoxLayout>
#include <QBitmap>
#include <QtDebug>

class ColorDock : public QFrame
{
    Q_OBJECT
public:
    ColorDock(QWidget *parent);

    virtual QSize sizeHint() const;
    virtual QSize minimumSizeHint() const;

    void setCustomSizeHint(const QSize &size);

public slots:

protected:
    void paintEvent(QPaintEvent *);
    QSize szHint, minSzHint;
};


ColorDock::ColorDock(QWidget *parent)
    : QFrame(parent)
{
    QFont font = this->font();
    font.setPointSize(8);
    setFont(font);
    szHint = QSize(-1, -1);
    minSzHint = QSize(125, 75);

}

QSize ColorDock::sizeHint() const
{
    return szHint;
}

QSize ColorDock::minimumSizeHint() const
{
    return minSzHint;
}

void ColorDock::paintEvent(QPaintEvent *)
{
    QPainter p(this);
    p.setRenderHint(QPainter::Antialiasing);
    p.fillRect(rect(), QColor("#F1F1F1"));

    p.save();

    extern void render_qt_text(QPainter *, int, int, const QColor &);
    render_qt_text(&p, width(), height(), QColor("#F8F8F8"));

    p.restore();
}

void ColorDock::setCustomSizeHint(const QSize &size)
{
    szHint = size;
    updateGeometry();
}

ColorSwatch::ColorSwatch(QWidget *parent, Qt::WindowFlags flags)
    : QDockWidget(parent, flags)
{
    setObjectName("Dock Widget");
    setWindowTitle(objectName() + QLatin1String(" [*]"));

    QFrame *swatch = new ColorDock(this);
    swatch->setFrameStyle(QFrame::Box | QFrame::Sunken);
    setWidget(swatch);

    setFeatures(features() | DockWidgetClosable);
    setFeatures(features() | DockWidgetMovable);
    setFeatures(features() | DockWidgetFloatable);
    setAllowedAreas(Qt::AllDockWidgetAreas);

    menu = new QMenu("Menu", this);
    menu->addAction(toggleViewAction());
    menu->addSeparator();

    //toggleViewAction()->setShortcut(Qt::CTRL|Qt::Key_R);

}

void ColorSwatch::contextMenuEvent(QContextMenuEvent *event)
{
    event->accept();
    menu->exec(event->globalPos());
}

void ColorSwatch::resizeEvent(QResizeEvent *e)
{
    QDockWidget::resizeEvent(e);
}


#include "colorswatch.moc"
