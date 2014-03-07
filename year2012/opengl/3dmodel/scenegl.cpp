#include "scenegl.h"
#include <math.h>
#include <QtGui>
#include <QTimer>

SceneGL::SceneGL(QWidget *parent) :
    QGLWidget(parent)
{
    defaultScene();

    setFormat(QGLFormat(QGL::DoubleBuffer)); // Двойная буферизация
    glDepthFunc(GL_LEQUAL); // Буфер глубины

}

void SceneGL::mousePressEvent(QMouseEvent* pe)
{
   ptrMousePosition = pe->pos();
}

void SceneGL::mouseReleaseEvent(QMouseEvent* pe)
{

}

void SceneGL::mouseMoveEvent(QMouseEvent* pe)
{
   xRot  = 180/nSca*(GLfloat)(pe->y()-ptrMousePosition.y())/height();
   zRot  = 180/nSca*(GLfloat)(pe->x()-ptrMousePosition.x())/width();

   ptrMousePosition = pe->pos();

   updateGL();
}

void SceneGL::wheelEvent(QWheelEvent* pe)
{
   if ((pe->delta())>0) scale_plus(); else if ((pe->delta())<0) scale_minus();

   updateGL();
}

void SceneGL::keyPressEvent(QKeyEvent* pe)
{
   switch (pe->key())
   {
      case Qt::Key_Plus:
         scale_plus();
      break;

      case Qt::Key_Equal:
         scale_plus();
      break;

      case Qt::Key_Minus:
         scale_minus();
      break;

      case Qt::Key_Up:
         rotate_up();
      break;

      case Qt::Key_Down:
         rotate_down();
      break;

      case Qt::Key_Left:
        rotate_left();
      break;

      case Qt::Key_Right:
         rotate_right();
      break;

      case Qt::Key_S:
         translate_down();
      break;

      case Qt::Key_W:
         translate_up();
      break;

      case Qt::Key_Space:
         defaultScene();
      break;

      case Qt::Key_Escape:
         this->close();
      break;
   }

   updateGL();
}

void SceneGL::scale_plus()
{
   nSca = nSca*1.1;
}

void SceneGL::scale_minus()
{
   nSca = nSca/1.1;
}

void SceneGL::rotate_up()
{
   xRot  += 1.0;
}

void SceneGL::rotate_down()
{
   xRot -= 1.0;
}

void SceneGL::rotate_left()
{
   zRot  += 1.0;
}

void SceneGL::rotate_right()
{
   zRot -= 1.0;
}

void SceneGL::translate_down()
{
   zTra -= 0.1;
}

void SceneGL::translate_up()
{
   zTra  += 0.1;
}

void SceneGL::defaultScene()
{
   xRot=0; yRot=0; zRot=0; zTra=0; nSca=1;
}

void SceneGL::initializeGL()
{
    glClearColor(0.0f,0.0f,0.0f,1.0f);


    //    glEnable(GL_DEPTH_TEST);
    glBlendFunc ( GL_SRC_COLOR, GL_ONE_MINUS_SRC_ALPHA);

    glEnable(GL_BLEND);
    QTimer *timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(update()));
    timer->start(10);

}

void SceneGL::resizeGL(int nWidth,int nHeight)
{
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(120.0, (GLdouble)nWidth / (GLdouble)nHeight, 0, 1000.0);
    glViewport(0, 0, (GLint)nWidth, (GLint)nHeight);
}

void SceneGL::update()
{
    rot++;
    updateGL();
}

void SceneGL::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);

    glLoadIdentity();

    glTranslatef(0.0f, 0.0, -4.0f);
    glTranslatef(0.0f, 0.0, zTra);
    glRotatef(90, 1.0f, 0.0f, 0.0f);
    glRotatef(xRot, 1.0f, 0.0f, 0.0f);
    glRotatef(yRot, 0.0f, 1.0f, 0.0f);
    glRotatef(zRot, 0.0f, 0.0f, 1.0f);

    drawAxis();
    glPushMatrix();
    glRotatef(30, 0.0f, 1.0f, 0.0f);
    glDrawCube();
    glPopMatrix();

}

void SceneGL::drawAxis()
{
    glLineWidth(3.0f);
    // до вызова команды ширина равна 9 пикселю по умолчанию
    // устанавливаем цвет последующих примитивов
    glColor4f(1.00f, 0.00f, 0.00f, 1.0f);
    // ось x кvoid Scene3D::drawAxis()
    {
        glLineWidth(3.0f);
        // до вызова команды ширина равна 9 пикселю по умолчанию

        // устанавливаем цвет последующих примитивов
        glColor4f(1.00f, 0.00f, 0.00f, 1.0f);
        // ось x красного цвета
        glBegin(GL_LINES); // построение линии
        glVertex3f( 9.0f,  0.0f,  0.0f); // первая точка
        glVertex3f(-9.0f,  0.0f,  0.0f); // вторая точка
        glEnd();

        QColor halfGreen(0, 128, 0, 255);
        qglColor(halfGreen);
        glBegin(GL_LINES);
        // ось y зеленого цвета
        glVertex3f( 0.0f,  9.0f,  0.0f);
        glVertex3f( 0.0f, -9.0f,  0.0f);

        glColor4f(0.00f, 0.00f, 1.00f, 9.0f);
        // ось z синего цвета
        glVertex3f( 0.0f,  0.0f,  9.0f);
        glVertex3f( 0.0f,  0.0f, -9.0f);
        glEnd();
    }
}

void SceneGL::glDrawCube()              // Рисование куба
{
       glBegin(GL_QUADS);               // Начинаем рисовать четырехугольники

       // Передняя сторона
       glColor4f(0.0f, 1.0f, 1.0f, 1.0f);

       glNormal3f( 0.0f, 0.0f, 1.0f);   // Нормаль вперед
       glTexCoord2f(0.0f, 0.0f);
       glVertex3f(-1.0f, -1.0f,  0.5f); // Низ Лево на текстуре и четырехугольнике
       glTexCoord2f(1.0f, 0.0f);
       glVertex3f( 1.0f, -1.0f,  0.5f); // Низ Право на текстуре и четырехугольнике
       glTexCoord2f(1.0f, 1.0f);
       glVertex3f( 1.0f,  1.0f,  0.5f); // Верх Право на текстуре и четырехугольнике
       glTexCoord2f(0.0f, 1.0f);
       glVertex3f(-1.0f,  1.0f,  0.5f); // Верх Лево на текстуре и четырехугольнике

       // Задняя сторона
       glNormal3f( 0.0f, 0.0f,-1.0f);   // Обратная нормаль
       glTexCoord2f(1.0f, 0.0f);
       glVertex3f(-1.0f, -1.0f, -0.5f); // Низ Право на текстуре и четырехугольнике
       glTexCoord2f(1.0f, 1.0f);
       glVertex3f(-1.0f,  1.0f, -0.5f); // Верх Право на текстуре и четырехугольнике
       glTexCoord2f(0.0f, 1.0f);
       glVertex3f( 1.0f,  1.0f, -0.5f); // Верх Лево на текстуре и четырехугольнике
       glTexCoord2f(0.0f, 0.0f);
       glVertex3f( 1.0f, -1.0f, -0.5f); // Низ Лево на текстуре и четырехугольнике

       // Верхняя грань
       glNormal3f( 0.0f, 1.0f, 0.0f);   // Нормаль вверх
       glTexCoord2f(0.0f, 1.0f);
       glVertex3f(-1.0f,  1.0f, -0.5f); // Верх Лево на текстуре и четырехугольнике
       glTexCoord2f(0.0f, 0.0f);
       glVertex3f(-1.0f,  1.0f,  0.5f); // Низ Лево на текстуре и четырехугольнике
       glTexCoord2f(1.0f, 0.0f);
       glVertex3f( 1.0f,  1.0f,  0.5f); // Низ Право на текстуре и четырехугольнике
       glTexCoord2f(1.0f, 1.0f);
       glVertex3f( 1.0f,  1.0f, -0.5f); // Верх Право на текстуре и четырехугольнике

       // Нижняя грань
       glNormal3f( 0.0f,-1.0f, 0.0f);   // Нормаль направлена вниз
       glTexCoord2f(1.0f, 1.0f);
       glVertex3f(-1.0f, -1.0f, -0.5f); // Верх Право на текстуре и четырехугольнике
       glTexCoord2f(0.0f, 1.0f);
       glVertex3f( 1.0f, -1.0f, -0.5f); // Верх Лево на текстуре и четырехугольнике
       glTexCoord2f(0.0f, 0.0f);
       glVertex3f( 1.0f, -1.0f,  0.5f); // Низ Лево на текстуре и четырехугольнике
       glTexCoord2f(1.0f, 0.0f);
       glVertex3f(-1.0f, -1.0f,  0.5f); // Низ Право на текстуре и четырехугольнике

       // Правая грань
       glNormal3f( 1.0f, 0.0f, 0.0f);   // Нормаль направлена вправо
       glTexCoord2f(1.0f, 0.0f);
       glVertex3f( 1.0f, -1.0f, -0.5f); // Низ Право на текстуре и четырехугольнике
       glTexCoord2f(1.0f, 1.0f);
       glVertex3f( 1.0f,  1.0f, -0.5f); // Верх Право на текстуре и четырехугольнике
       glTexCoord2f(0.0f, 1.0f);
       glVertex3f( 1.0f,  1.0f,  0.5f); // Верх Лево на текстуре и четырехугольнике
       glTexCoord2f(0.0f, 0.0f);
       glVertex3f( 1.0f, -1.0f,  0.5f); // Низ Лево на текстуре и четырехугольнике

       // Левая грань
       glNormal3f(-1.0f, 0.0f, 0.0f);   // Нормаль направлена влево
       glTexCoord2f(0.0f, 0.0f);
       glVertex3f(-1.0f, -1.0f, -0.5f); // Низ Лево на текстуре и четырехугольнике
       glTexCoord2f(1.0f, 0.0f);
       glVertex3f(-1.0f, -1.0f,  0.5f); // Низ Право на текстуре и четырехугольнике
       glTexCoord2f(1.0f, 1.0f);
       glVertex3f(-1.0f,  1.0f,  0.5f); // Верх Право на текстуре и четырехугольнике
       glTexCoord2f(0.0f, 1.0f);
       glVertex3f(-1.0f,  1.0f, -0.5f); // Верх Лево на текстуре и четырехугольнике
       glEnd();                         // Заканчиваем рисование четырехугольников
}
