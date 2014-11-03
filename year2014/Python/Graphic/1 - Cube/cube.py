from OpenGL.GL import *
from OpenGL.GLUT import *
from OpenGL.GLU import *

w = 640
h = 480
a = 2.205

def DrawCube():
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT)
    glViewport(0, 0, w, h)
    glLoadIdentity()

    glMatrixMode(GL_PROJECTION)
	
	#gluPerspective(45.0, 1.0*w/h, 7, 7/a)
	#gluPerspective(45.0, 1.0*w/h, 9, 9/a)
    gluPerspective(45.0, 1.0*w/h, 8, 8/a)

	#glOrtho(-2, 2, -2.0*h/w, 2.0*h/w, 0, 10)
	

    glTranslatef(0, 0, -4)

    glBegin(GL_QUADS)

    glColor3f(0.5, 0.5, 0.5)
    glVertex3f( 1, 1,-1)
    glVertex3f(-1, 1,-1)
    glVertex3f(-1, 1, 1)
    glVertex3f( 1, 1, 1) 

    glColor3f(0.5, 0.5, 0.5)
    glVertex3f( 1,-1, 1)
    glVertex3f(-1,-1, 1)
    glVertex3f(-1,-1,-1)
    glVertex3f( 1,-1,-1) 

    glColor3f(0.9, 0.9, 0.9)
    glVertex3f( 1,-1,-1)
    glVertex3f(-1,-1,-1)
    glVertex3f(-1, 1,-1)
    glVertex3f( 1, 1,-1)

    glColor3f(0.7, 0.7, 0.7)
    glVertex3f(-1, 1, 1) 
    glVertex3f(-1, 1,-1)
    glVertex3f(-1,-1,-1) 
    glVertex3f(-1,-1, 1) 

    glColor3f(0.7, 0.7, 0.7)
    glVertex3f( 1, 1,-1) 
    glVertex3f( 1, 1, 1)
    glVertex3f( 1,-1, 1)
    glVertex3f( 1,-1,-1)

    glEnd()
    glutSwapBuffers()	 
 
def main():
 
    glutInit(sys.argv)
    glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH)
    glutInitWindowSize(w,h)

    glutCreateWindow('Cube')

    glutDisplayFunc(DrawCube)
    glutIdleFunc(DrawCube)

    glutMainLoop()
 
main() 