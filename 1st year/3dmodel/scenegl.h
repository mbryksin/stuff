#ifndef SCENEGL_H
#define SCENEGL_H

#include <QGLWidget>
#include <GL/glu.h>


class SceneGL : public QGLWidget
{
    Q_OBJECT
public:
    explicit SceneGL(QWidget *parent = 0);

protected:
    void initializeGL();
    void resizeGL(int nWidth,int nHeight);
    void paintGL();

    void mousePressEvent(QMouseEvent* pe);
    void mouseMoveEvent(QMouseEvent* pe);
    void mouseReleaseEvent(QMouseEvent* pe);
    void wheelEvent(QWheelEvent* pe);
    void keyPressEvent(QKeyEvent* pe);

signals:

public slots:

private:
    int rot;
    void update();
    void drawAxis();

    QPoint ptrMousePosition;

    GLfloat xRot;//поворот камеры относительно X
    GLfloat yRot;//поворот камеры относительно Y
    GLfloat zRot;//поворот камеры относительно Z
    GLfloat zTra;// перемещение камеры по оси Z( происходит перд поворотом)
    GLfloat nSca;// чувствительность мыши

    void scale_plus();
    void scale_minus();
    void rotate_up();
    void rotate_down();
    void rotate_left();
    void rotate_right();
    void translate_down();
    void translate_up();
    void defaultScene();
    void glDrawCube();
};

#endif // SCENEGL_H
