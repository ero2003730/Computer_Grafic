/*
  Enzo Reis de Oliveira
  156474
  Proposta de Exercícios 02 - Transformações 2D - OpenGL - Flor
*/

#include <GL/glut.h>
#include <math.h>

float angle = 0.0f; // ângulo de rotação

void keyboard(unsigned char key, int x, int y)
{
    switch (key)
    {
    case 'd':
        angle += 5.0f;
        break;
    case 'a':
        angle -= 5.0f;
        break;
    }
    glutPostRedisplay();
}

void specialKeys(int key, int x, int y)
{
    switch (key)
    {
    case GLUT_KEY_RIGHT:
        angle += 5.0f;
        break;
    case GLUT_KEY_LEFT:
        angle -= 5.0f;
        break;
    }
    glutPostRedisplay();
}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT);

    // Fundo azul
    glClearColor(0.0f, 0.0f, 1.0f, 1.0f);

    // Chão verde
    glColor3f(0.0f, 1.0f, 0.0f);
    glBegin(GL_QUADS);
    glVertex2f(-1.0f, -1.0f);
    glVertex2f(1.0f, -1.0f);
    glVertex2f(1.0f, -0.5f);
    glVertex2f(-1.0f, -0.5f);
    glEnd();

    // Tronco marrom
    glColor3f(0.5f, 0.5f, 0.0f);
    glBegin(GL_QUADS);
    glVertex2f(-0.01f, -0.5f);
    glVertex2f(0.01f, -0.5f);
    glVertex2f(0.01f, 0.0f);
    glVertex2f(-0.01f, 0.0f);
    glEnd();

    // Desenhar o centro da flor
    glColor3f(1.0, 1.0, 0.0);
    glBegin(GL_POLYGON);
    for (int i = 0; i < 360; i++)
    {
        float theta = i * 3.14159 / 180;
        glVertex2f(0.1 * cos(theta), 0.1 * sin(theta));
    }
    glEnd();

    // Desenhar um SOL
    glPushMatrix();
    glTranslatef(0.8f, 0.8f, 0.0f); // Transladar para o canto superior direito
    glColor3f(1.0, 1.0, 0.0);
    glBegin(GL_POLYGON);
    for (int i = 0; i < 360; i++)
    {
        float theta = i * 3.14159 / 180;
        glVertex2f(0.4 * cos(theta), 0.4 * sin(theta));
    }
    glEnd();
    glPopMatrix();

    // Desenhar as pétalas da flor
    glColor3f(1.0, 0.0, 1.0);
    for (int i = 0; i < 360; i += 45)
    {
        glPushMatrix();
        glRotatef(angle, 0.0f, 0.0f, 1.0f); // Rotação
        float theta = i * 3.14159 / 180;
        glTranslatef(0.2 * cos(theta), 0.2 * sin(theta), 0.0);
        glBegin(GL_POLYGON);
        for (int j = 0; j < 360; j++)
        {
            float angle = j * 3.14159 / 180;
            glVertex2f(0.1 * cos(angle), 0.1 * sin(angle));
        }
        glEnd();
        glPopMatrix();
    }

    glFlush();
}

int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutCreateWindow("OpenGL Flower");
    glutDisplayFunc(display);
    glutKeyboardFunc(keyboard);   // Registrar função para teclas alfanuméricas
    glutSpecialFunc(specialKeys); // Registrar função para teclas especiais
    glutMainLoop();
    return 0;
}
