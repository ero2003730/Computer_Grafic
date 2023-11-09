/*
  Enzo Reis de Oliveira
  156474
  Exercicio 4 - Proposta de Exercícios 02 - Bresenham para traçado de circunferências
*/

#include <GL/glut.h>
#include <stdbool.h>
#include <math.h>

// funções que serão utilizadas
void draw();
void mouse(int button, int state, int mouse_x, int mouse_y);
void keyboard(unsigned char key, int x, int y);
void drawCircle(int xc, int yc, int r);

// variáveis globais que serão utilizadas
float circle_x = 0.0f;
float circle_y = 0.0f;
bool first_click = true;
int radius = 50; // valor inicial do raio

int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE);
    glutInitWindowSize(500, 500);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Traçar círculo com Bresenham");
    glutDisplayFunc(draw);
    glutMouseFunc(mouse);
    glutKeyboardFunc(keyboard);
    glutMainLoop();
    return 0;
}

void draw()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(0.0f, 0.0f, 1.0f);

    if (first_click == false)
    {
        int x = (int)(circle_x * 250);
        int y = (int)(circle_y * 250);

        glBegin(GL_POINTS);
        drawCircle(x, y, radius);
        glEnd();
    }

    glFlush();
}

void mouse(int button, int state, int mouse_x, int mouse_y)
{
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
    {
        float x = (float)(mouse_x - 250) / 250;
        float y = (float)(250 - mouse_y) / 250;

        circle_x = x;
        circle_y = y;
        first_click = false;

        glutPostRedisplay();
    }
}

void keyboard(unsigned char key, int x, int y)
{
    switch (key)
    {
    case '+':
        radius += 5; // Aumenta o raio em 5 unidades
        break;
    case '-':
        if (radius > 5) // Estabelece um raio mínimo de 5
        {
            radius -= 5; // Diminui o raio em 5 unidades
        }
        break;
    }
    glutPostRedisplay();
}

void drawCircle(int xc, int yc, int r)
{
    int x = 0, y = r;
    int d = 3 - 2 * r;

    while (y >= x)
    {
        glVertex2f((float)(xc + x) / 250, (float)(yc + y) / 250);
        glVertex2f((float)(xc - x) / 250, (float)(yc + y) / 250);
        glVertex2f((float)(xc + x) / 250, (float)(yc - y) / 250);
        glVertex2f((float)(xc - x) / 250, (float)(yc - y) / 250);
        glVertex2f((float)(xc + y) / 250, (float)(yc + x) / 250);
        glVertex2f((float)(xc - y) / 250, (float)(yc + x) / 250);
        glVertex2f((float)(xc + y) / 250, (float)(yc - x) / 250);
        glVertex2f((float)(xc - y) / 250, (float)(yc - x) / 250);

        // Atualiza d e x
        if (d > 0)
        {
            y--;
            d = d + 4 * (x - y) + 10;
        }
        else
        {
            d = d + 4 * x + 6;
        }
        x++;
    }
}