#include "QApplication"
#include "cube.h"
#include <QtGui>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    if (!QGLFormat::hasOpenGL())
      qFatal("This system has no OpenGL support");

    Cube cube;
    cube.resize(300, 300);
    cube.show();

    return app.exec();
}
