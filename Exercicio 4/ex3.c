/*
  Enzo Reis de Oliveira
  156474
  Proposta de Exercícios 02 - Transformações 2D - OpenGL - Robo
*/

#include <GL/glut.h>
#include <math.h>

float anguloBraco = 0.0, anguloPerna = 0.0;
float posX = 0.0;

void teclado(unsigned char tecla, int x, int y)
{
    if (tecla == 'd')
    {
        posX += 0.02;
        anguloBraco = sin(glutGet(GLUT_ELAPSED_TIME) * 0.001) * 0.05;
        anguloPerna = sin(glutGet(GLUT_ELAPSED_TIME) * 0.001) * 0.05;
    }
    if (tecla == 'a')
    {
        posX -= 0.02;
        anguloBraco = sin(glutGet(GLUT_ELAPSED_TIME) * 0.001) * 0.05;
        anguloPerna = sin(glutGet(GLUT_ELAPSED_TIME) * 0.001) * 0.05;
    }

    glutPostRedisplay();
}

void desenhaMembro(float x, float y, float angulo, float anguloExtra, float dx, float dy, float r, float g, float b)
{
    glPushMatrix();
    glColor3f(r, g, b);
    glTranslatef(x, y, 0);
    glRotatef(angulo, 0, 0, 1);
    glBegin(GL_QUADS);
    glVertex2f(dx, dy);
    glVertex2f(-dx, dy);
    glVertex2f(-dx, -dy);
    glVertex2f(dx, -dy);
    glEnd();
    glPopMatrix();

    glPushMatrix();
    glColor3f(r, g, b);
    glTranslatef(x - 2 * dx, y, 0);
    glRotatef(angulo * anguloExtra, 0, 0, 1);
    glBegin(GL_QUADS);
    glVertex2f(dx, dy);
    glVertex2f(-dx, dy);
    glVertex2f(-dx, -dy);
    glVertex2f(dx, -dy);
    glEnd();
    glPopMatrix();
}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT);

    glPushMatrix();
    glTranslatef(posX, 0.0, 0.0);

    // Cabeça do robô (redonda)
    glColor3f(1.0, 1.0, 1.0); // Branco
    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(0.0, 0.25);
    for (int i = 0; i <= 360; i++)
    {
        float x = 0.1 * cos(i * 3.14159 / 180.0);
        float y = 0.1 * sin(i * 3.14159 / 180.0);
        glVertex2f(x, y + 0.25);
    }
    glEnd();

    // Pescoço do robô
    glColor3f(0.5, 0.5, 0.5); // Cinza
    glBegin(GL_QUADS);
    glVertex2f(-0.05, 0.1);
    glVertex2f(0.05, 0.1);
    glVertex2f(0.05, 0.15);
    glVertex2f(-0.05, 0.15);
    glEnd();

    // Corpo do robô
    glColor3f(0.0, 1.0, 0.0); // Verde
    glBegin(GL_QUADS);
    glVertex2f(-0.1, -0.1);
    glVertex2f(0.1, -0.1);
    glVertex2f(0.1, 0.1);
    glVertex2f(-0.1, 0.1);
    glEnd();

    // Braço esquerdo - parte superior (mais comprido)
    glPushMatrix();
    glColor3f(0.0, 0.0, 1.0); // Azul
    glTranslatef(-0.1, 0.07, 0);
    glRotatef(anguloBraco, 0, 0, 1);
    glBegin(GL_QUADS);
    glVertex2f(0, 0.01);
    glVertex2f(-0.15, 0.01);  // Aumentado para -0.15
    glVertex2f(-0.15, -0.01); // Aumentado para -0.15
    glVertex2f(0, -0.01);
    glEnd();
    glPopMatrix();

    // Braço direito - parte superior (mais comprido)
    glPushMatrix();
    glColor3f(0.0, 0.0, 1.0); // Azul
    glTranslatef(0.1, 0.07, 0);
    glRotatef(-anguloBraco, 0, 0, 1);
    glBegin(GL_QUADS);
    glVertex2f(0, 0.01);
    glVertex2f(0.15, 0.01);  // Aumentado para 0.15
    glVertex2f(0.15, -0.01); // Aumentado para 0.15
    glVertex2f(0, -0.01);
    glEnd();
    glPopMatrix();

    // Perna esquerda - parte superior (mais comprida)
    glPushMatrix();
    glColor3f(1.0, 0.0, 0.0); // Vermelho
    glTranslatef(-0.06, -0.1, 0);
    glRotatef(anguloPerna, 0, 0, 1);
    glBegin(GL_QUADS);
    glVertex2f(0.01, 0);
    glVertex2f(0.01, -0.15);  // Aumentado para -0.15
    glVertex2f(-0.01, -0.15); // Aumentado para -0.15
    glVertex2f(-0.01, 0);
    glEnd();
    glPopMatrix();

    glBegin(GL_QUADS);
    glVertex2f(0.05, -0.3);
    glVertex2f(0.08, -0.3);
    glVertex2f(0.08, -0.1);
    glVertex2f(0.05, -0.1);
    glEnd();

    glFlush();
}

int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(400, 400);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Robot OpenGL");
    glClearColor(0.0, 0.0, 0.0, 1.0);
    gluOrtho2D(-0.5, 0.5, -0.5, 0.5);
    glutDisplayFunc(display);
    glutKeyboardFunc(teclado);
    glutMainLoop();
    return 0;
}
