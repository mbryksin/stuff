#include "QApplication"
#include "scenegl.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    SceneGL scene;
    scene.setWindowTitle("Hello Gl window");
    scene.show();
    return app.exec();
}
