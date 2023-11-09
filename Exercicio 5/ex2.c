/*
  Enzo Reis de Oliveira
  156474
  Proposta de Exercícios 01 - Animação OpenGL - Catavento
*/

#include <GL/glut.h>
#include <math.h>
#include <time.h>

typedef int bool;
#define true 1
#define false 0

float angle = 0.0f;
float speed = 0.0f;
bool isAccelerating = false;
clock_t lastTime = 0;
float timeInterval = 0.5;

void update()
{
    if (isAccelerating)
    {
        printf("Accelerating\n");
        clock_t currentTime = clock();
        float elapsed = (float)(currentTime - lastTime) / CLOCKS_PER_SEC;

        if (elapsed >= timeInterval)
        {
            speed += 1.0f;
            printf("Speed increased: %f\n", speed);
            lastTime = currentTime;
        }
    }

    angle += speed;

    if (angle > 360.0f)
    {
        angle -= 360.0f;
    }

    glutPostRedisplay();
}

void draw_windmill()
{
    // Desenha o suporte (um cone vertical)
    glPushMatrix();
    glColor3f(1.0f, 0.0f, 0.0f); // Cor vermelha para o suporte
    glRotatef(-90, 1.0f, 0.0f, 0.0f);
    glutWireCone(0.1, 0.5, 20, 20);
    glPopMatrix();

    // Desenha as pás do catavento
    glPushMatrix();
    glTranslatef(0.0f, 0.5f, 0.0f);     // Mover para a ponta do suporte
    glColor3f(0.0f, 0.0f, 1.0f);        // Cor azul para as hélices
    glRotatef(angle, 0.0f, 1.0f, 0.0f); // Rotação para animação das pás

    for (int i = 0; i < 3; ++i)
    {
        glPushMatrix();
        glRotatef(90, 0.0f, 0.0f, 1.0f);         // Rotação adicional de 90 graus em torno do eixo Z
        glRotatef(120.0f * i, 0.0f, 1.0f, 0.0f); // Rotação para distribuição das pás
        glutWireCone(0.05, 0.2, 10, 10);         // Desenha a pá
        glPopMatrix();
    }

    glPopMatrix();
}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glLoadIdentity();
    draw_windmill();
    glutSwapBuffers();
}

void keyboard(unsigned char key, int x, int y)
{
    if (key == 27)
    {
        exit(0);
    }
}

void specialKeys(int key, int x, int y)
{
    switch (key)
    {
    case GLUT_KEY_RIGHT:
        speed += 1.0f;
        break;
    case GLUT_KEY_LEFT:
        speed -= 1.0f;
        break;
    }
}

void mouse(int button, int state, int x, int y)
{
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
    {
        printf("Left mouse button pressed.\n");
        isAccelerating = true;
        lastTime = clock();
    }
    else if (button == GLUT_LEFT_BUTTON && state == GLUT_UP)
    {
        printf("Left mouse button released.\n");
        isAccelerating = false;
    }
    else if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN)
    {
        printf("Right mouse button pressed.\n");
        speed = 0.0f;
    }
}

int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(800, 600);
    glutInitWindowPosition(50, 50);
    glutCreateWindow("Windmill");
    glutDisplayFunc(display);
    glutIdleFunc(update);
    glutKeyboardFunc(keyboard);
    glutSpecialFunc(specialKeys);
    glutMouseFunc(mouse);
    glutMainLoop();

    return 0;
}