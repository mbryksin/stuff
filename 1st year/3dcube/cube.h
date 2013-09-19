#ifndef CUBE_H
#define CUBE_H

#include <QGLWidget>
#include <GL/glu.h>
#include <GL/gl.h>
#include <GL/glut.h>
#include <QtGui>

class Cube : public QGLWidget
{
public:
    explicit Cube(QWidget *parent = 0);

protected:
  void initializeGL();
  void resizeGL(int width, int height);
  void paintGL();
  void mousePressEvent(QMouseEvent *ev);
  void mouseMoveEvent(QMouseEvent *event);
  void keyPressEvent(QKeyEvent* pe);

private:
  void drawCube();
  GLfloat rotationX;
  GLfloat rotationY;
  GLfloat rotationZ;
  GLfloat translationZ;
  QPoint lastPos;


    void rotate_up();
    void rotate_down();
    void rotate_left();
    void rotate_right();
    void translate_down();
    void translate_up();
    void defaultScene();
    void drawAxis();

    int vector[3];
};


#endif // CUBE_H
