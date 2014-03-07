#include "cube.h"

static const QColor faceColors[6] = {
    QColor(240, 240, 240, 127),
    QColor(240, 240, 240, 127),
    QColor(200, 200, 200, 127),
    QColor(200, 200, 200, 127),
    QColor(160, 160, 160, 127),
    QColor(160, 160, 160, 127)
};

static const GLfloat coords[6][4][3] = {
    { { +1.0, -1.0, +1.0 }, { +1.0, -1.0, -1.0 },
      { +1.0, +1.0, -1.0 }, { +1.0, +1.0, +1.0 } },
    { { -1.0, -1.0, -1.0 }, { -1.0, -1.0, +1.0 },
      { -1.0, +1.0, +1.0 }, { -1.0, +1.0, -1.0 } },
    { { +1.0, -1.0, -1.0 }, { -1.0, -1.0, -1.0 },
      { -1.0, +1.0, -1.0 }, { +1.0, +1.0, -1.0 } },
    { { -1.0, -1.0, +1.0 }, { +1.0, -1.0, +1.0 },
      { +1.0, +1.0, +1.0 }, { -1.0, +1.0, +1.0 } },
    { { -1.0, -1.0, -1.0 }, { +1.0, -1.0, -1.0 },
      { +1.0, -1.0, +1.0 }, { -1.0, -1.0, +1.0 } },
    { { -1.0, +1.0, +1.0 }, { +1.0, +1.0, +1.0 },
      { +1.0, +1.0, -1.0 }, { -1.0, +1.0, -1.0 } }
};

Cube::Cube(QWidget *parent) :
    QGLWidget(parent)
{
  setFormat(QGLFormat(QGL::DoubleBuffer | QGL::DepthBuffer));
    defaultScene();

    vector[0] = 2;
    vector[1] = 2;
    vector[2] = 2;

}

void Cube::keyPressEvent(QKeyEvent* pe)
{
   switch (pe->key())
   {
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

void Cube::rotate_up()
{
   rotationX  += 1.0;
}

void Cube::rotate_down()
{
   rotationX -= 1.0;
}

void Cube::rotate_left()
{
   rotationZ  += 1.0;
}

void Cube::rotate_right()
{
   rotationZ -= 1.0;
}

void Cube::translate_down()
{
   translationZ -= 0.1;
}

void Cube::translate_up()
{
   translationZ += 0.1;
}

void Cube::defaultScene()
{
    rotationX = 0;
    rotationY = 0;
    rotationZ = 0;
    translationZ = 0;
}

void Cube::initializeGL()
{
    glShadeModel(GL_FLAT);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
}

void Cube::resizeGL(int width, int height)
{
    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    GLfloat x = (GLfloat)width / height;
    glFrustum(-x, x, -1.0, 1.0, 4.0, 30.0);
    glMatrixMode(GL_MODELVIEW);
}

void Cube::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);

    glLoadIdentity();
    glTranslatef(0.0, 0.0, -15.0 + translationZ);
    glRotatef(rotationX, 1.0, 0.0, 0.0);
    glRotatef(rotationY, 0.0, 1.0, 0.0);
    glRotatef(rotationZ, 0.0, 0.0, 1.0);
    glRotatef(90, 1.0, 0.0, 0.0);
//    glRotatef(-10, 0.0, 1.0, 0.0);
//    glRotatef(10, 1.0, 0.0, 0.0);
//    glRotatef(-30, 0.0, 0.0, 1.0);
    drawAxis();
//    glRotatef(30, 0.0, 0.0, 1.0);
    drawCube();
}

void Cube::drawAxis()
{
    float x = vector[0];
    float y = vector[1];
    float z = vector[2];



    glLineWidth(4.0f);
    glColor3f(1.00f, 1.00f, 0.00f);

    glPointSize(5);
    glBegin(GL_POINTS);
    glVertex3d(x,0,0);
    glVertex3d(0,y,0);
    glVertex3d(0,0,z);
    glVertex3d(x,y,z);
    glEnd();

    glBegin(GL_LINES);
    glVertex3f( 0.0f,  0.0f,  0.0f);
    glVertex3f( x,  0.0f,  0.0f);
    glVertex3f( 0.0f,  0.0f,  0.0f);
    glVertex3f( 0.0f, y,  0.0f);
    glVertex3f( 0.0f,  0.0f,  0.0f);
    glVertex3f( 0.0f,  0.0f, z);
    glVertex3f( 0.0f,  0.0f,  0.0f);
    glVertex3f( x,  y, z);
    glEnd();

    glLineWidth(2.0f);
    glBegin(GL_LINES);
    glColor4f(1.00f, 0.00f, 0.00f, 1.0f);
    if (x >= 0)
    {
        glVertex3f( 100.0f,  0.0f,  0.0f);
        glVertex3f( x,  0.0f,  0.0f);
        glVertex3f(-100.0f,  0.0f,  0.0f);
        glVertex3f(0.0f,  0.0f,  0.0f);
    } else
    {
        glVertex3f( 100.0f,  0.0f,  0.0f);
        glVertex3f( 0.0f,  0.0f,  0.0f);
        glVertex3f(-100.0f,  0.0f,  0.0f);
        glVertex3f( x,  0.0f,  0.0f);
    }

    QColor halfGreen(0, 128, 0, 255);
    qglColor(halfGreen);
    if (y >= 0.0)
    {
        glVertex3f( 0.0f,  100.0f,  0.0f);
        glVertex3f( 0.0f,  y,  0.0f);
        glVertex3f( 0.0f,  -100.0f,  0.0f);
        glVertex3f( 0.0f,  0.0f,  0.0f);
    } else
    {
        glVertex3f( 0.0f,  -100.0f,  0.0f);
        glVertex3f( 0.0f,  y,  0.0f);
        glVertex3f( 0.0f,  100.0f,  0.0f);
        glVertex3f( 0.0f,  0.0f,  0.0f);
    }

    glColor4f(0.00f, 0.00f, 1.00f, 9.0f);
    if (z >= 0.0)
    {
        glVertex3f( 0.0f,  0.0f,  100.0f);
        glVertex3f( 0.0f,  0.0f,  z);
        glVertex3f( 0.0f,  0.0f,  -100.0f);
        glVertex3f( 0.0f,  0.0f,  0.0f);
    } else
    {
        glVertex3f( 0.0f,  0.0f,  100.0f);
        glVertex3f( 0.0f,  0.0f,  0.0f);
        glVertex3f( 0.0f,  0.0f,  -100.0f);
        glVertex3f( 0.0f,  0.0f,  z);
    }
    glEnd();
}

void Cube::drawCube()
{

  for (int i = 0; i < 6; ++i) {
    glLoadName(i);
    glBegin(GL_QUADS);
    qglColor(faceColors[i]);
    for (int j = 0; j < 4; ++j) {
      glVertex3f(coords[i][j][0], coords[i][j][1], coords[i][j][2]);
    }
    glEnd();
  }
}

void Cube::mousePressEvent(QMouseEvent *ev)
{
  lastPos = ev->pos();
}

void Cube::mouseMoveEvent(QMouseEvent *event)
{
  GLfloat dx = (GLfloat)(event->x() - lastPos.x()) / width();
  GLfloat dy = (GLfloat)(event->y() - lastPos.y()) / height();
  rotationX += 180 * dy;
  rotationZ += 180 * dx;
  updateGL();

  lastPos = event->pos();
}
