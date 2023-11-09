/*
    Caio Bonani
    Davi Seiji
    Enzo Oliveira
    Mateus Romani
    Raphael Damasceno
*/

#include <GL/glut.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

float thetaX = 0.0;
float thetaY = 0.0;

void cubo(float c1, float c2, float c3)
{
    glColor3f(c1, c2, c3);
    glBegin(GL_POLYGON);
    glVertex3f(-0.1, 0.1, 0.1);
    glVertex3f(0.1, 0.1, 0.1);
    glVertex3f(0.1, -0.1, 0.1);
    glVertex3f(-0.1, -0.1, 0.1);
    glEnd();
    // glColor3f(0.0, 1.0, 0.0);
    glBegin(GL_POLYGON);
    glVertex3f(-0.1, 0.1, -0.1);
    glVertex3f(0.1, 0.1, -0.1);
    glVertex3f(0.1, -0.1, -0.1);
    glVertex3f(-0.1, -0.1, -0.1);
    glEnd();
    // glColor3f(0.0, 0.0, 1.0);
    glBegin(GL_POLYGON);
    glVertex3f(0.1, -0.1, 0.1);
    glVertex3f(0.1, 0.1, 0.1);
    glVertex3f(0.1, 0.1, -0.1);
    glVertex3f(0.1, -0.1, -0.1);
    glEnd();
    // glColor3f(1.0, 1.0, 0.0);
    glBegin(GL_POLYGON);
    glVertex3f(-0.1, -0.1, 0.1);
    glVertex3f(-0.1, 0.1, 0.1);
    glVertex3f(-0.1, 0.1, -0.1);
    glVertex3f(-0.1, -0.1, -0.1);
    glEnd();
    // glColor3f(1.0, 0.0, 1.0);
    glBegin(GL_POLYGON);
    glVertex3f(-0.1, 0.1, 0.1);
    glVertex3f(0.1, 0.1, 0.1);
    glVertex3f(0.1, 0.1, -0.1);
    glVertex3f(-0.1, 0.1, -0.1);
    glEnd();
    // glColor3f(0.0, 1.0, 1.0);
    glBegin(GL_POLYGON);
    glVertex3f(-0.1, -0.1, 0.1);
    glVertex3f(0.1, -0.1, 0.1);
    glVertex3f(0.1, -0.1, -0.1);
    glVertex3f(-0.1, -0.1, -0.1);
    glEnd();
}

void desenha()
{
    glClearColor(0, 0, 0, 0); // Preto
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glEnable(GL_DEPTH_TEST);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    // cabeça
    glPushMatrix();
    glTranslatef(0.0, 0.7, 0.0);
    cubo(0.4, 0.4, 0.4);
    glPopMatrix();

    // corpo
    glPushMatrix();
    glScalef(2.2, 3.2, 1);
    glTranslatef(0.0, 0.08, 0.0);
    cubo(1.0, 1.0, 0.0);
    glPopMatrix();

    // perna

    glPushMatrix();
    glTranslatef(-0.13, -0.2, 0.0);
    cubo(0.0, 0.0, 1.0);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-0.13, -0.4, 0.0);
    cubo(0.4, 0.4, 0.4);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0.13, -0.2, 0.0);
    cubo(0.0, 0.0, 1.0);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0.13, -0.4, 0.0);
    cubo(0.4, 0.4, 0.4);
    glPopMatrix();

    // Braço

    glPushMatrix();
    glTranslatef(0.3, 0.45, 0.0);
    glRotatef(75 - thetaX, 0.0, 0.0, 1.0);
    cubo(1.0, 1.0, 0.0);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0.3, 0.45, 0.0);
    glRotatef(75 - thetaX, 0.0, 0.0, 1.0);
    glTranslatef(0.2, 0.0, 0.0);
    cubo(0.4, 0.4, 0.4);
    glPopMatrix();

    //-------------------------------

    glPushMatrix();
    glTranslatef(-0.3, 0.45, 0.0);
    glRotatef(-75 + thetaX, 0.0, 0.0, 1.0);
    cubo(1.0, 1.0, 0.0);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-0.3, 0.45, 0.0);
    glRotatef(-75 + thetaX, 0.0, 0.0, 1.0);
    glTranslatef(-0.2, 0.0, 0.0);
    glRotatef(45, 0.0, 1.0, 0.0);
    cubo(0.4, 0.4, 0.4);
    glPopMatrix();

    glFlush();
}

void tecladoEspecial(int tecla, int x, int y)
{
    switch (tecla)
    {
    case GLUT_KEY_RIGHT:
        thetaY += 2;
        break;
    case GLUT_KEY_LEFT:
        thetaY -= 2;
        break;
    case GLUT_KEY_UP:

        if (thetaX < 160.0)
            thetaX += 2;

        printf("%f\n", thetaX);
        break;
    case GLUT_KEY_DOWN:
        if (thetaX > 0.0)
            thetaX -= 2;

        printf("%f\n", thetaX);
        break;
    default:
        break;
    }
    glutPostRedisplay();
}

int main(int argc, char *argv[])
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(1200, 1200);
    glutCreateWindow("Cubo");
    glutDisplayFunc(desenha);
    glutSpecialFunc(tecladoEspecial);
    glutMainLoop();
    return 0;
}