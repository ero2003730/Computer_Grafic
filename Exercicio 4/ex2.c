/*
  Enzo Reis de Oliveira
  156474
  Proposta de Exercícios 02 - Transformações 2D - OpenGL - Carro
*/

#include <GL/glut.h>
#include <math.h>

// Variáveis para controlar a posição do carro e o ângulo das rodas
float carX = 0.0f;
float wheelAngle = 0.0f;

// Função para tratar eventos do teclado
void keyboard(unsigned char key, int x, int y)
{
    // Mover o carro para a direita ('d') ou para a esquerda ('a')
    switch (key)
    {
    case 'd':
        carX += 0.05f;
        wheelAngle -= 10.0f; // Rotação da roda
        break;
    case 'a':
        carX -= 0.05f;
        wheelAngle += 10.0f; // Rotação da roda
        break;
    }
    // Solicitar a atualização da janela
    glutPostRedisplay();
}

// Função principal de renderização
void display()
{
    // Configurar a cor de fundo para azul
    glClearColor(0.0f, 0.0f, 1.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    glLoadIdentity();

    // Desenhar a estrada
    glColor3f(0.5, 0.5, 0.5);
    glBegin(GL_POLYGON);
    glVertex2f(-1.0f, -0.4f);
    glVertex2f(1.0f, -0.4f);
    glVertex2f(1.0f, -0.3f);
    glVertex2f(-1.0f, -0.3f);
    glEnd();

    // Transladar a posição do carro com base em carX
    glPushMatrix();
    glTranslatef(carX, 0.0f, 0.0f);

    // Desenhar o corpo do carro na cor vermelha
    glColor3f(1.0, 0.0, 0.0); // Red color for car body

    glBegin(GL_POLYGON);
    glVertex2f(-0.3f, -0.1f);
    glVertex2f(-0.2f, -0.1f);
    glVertex2f(-0.2f, 0.1f);
    glVertex2f(-0.3f, 0.1f);
    glEnd();

    glBegin(GL_POLYGON);
    glVertex2f(-0.2f, -0.1f);
    glVertex2f(0.2f, -0.1f);
    glVertex2f(0.2f, 0.2f);
    glVertex2f(-0.2f, 0.2f);
    glEnd();

    glBegin(GL_POLYGON);
    glVertex2f(0.2f, -0.1f);
    glVertex2f(0.3f, -0.1f);
    glVertex2f(0.3f, 0.1f);
    glVertex2f(0.2f, 0.1f);
    glEnd();

    // Desenhar as rodas
    glColor3f(0.0, 0.0, 0.0);
    float wheelPositions[2] = {-0.25f, 0.25f};
    for (int i = 0; i < 2; ++i)
    {
        glPushMatrix();
        glTranslatef(wheelPositions[i], -0.1f, 0.0f);
        glRotatef(wheelAngle, 0.0f, 0.0f, 1.0f);
        glBegin(GL_POLYGON);
        for (int j = 0; j < 360; j++)
        {
            float theta = j * 3.14159 / 180;
            float cx = 0.05 * cos(theta);
            float cy = 0.05 * sin(theta);
            glVertex2f(cx, cy);
        }
        glEnd();
        glPopMatrix();
    }

    glPopMatrix();
    glFlush();
}

// Função main com inicialização e loop principal
int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutCreateWindow("OpenGL Car");
    glutDisplayFunc(display);   // Registrar função de renderização
    glutKeyboardFunc(keyboard); // Registrar função de teclado
    glutMainLoop();             // Loop principal
    return 0;
}
