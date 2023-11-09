/*
  Enzo Reis de Oliveira
  156474
  Proposta de Exercícios 01 - Animação OpenGL - Palhaco
*/

#include <GL/glut.h>
#include <math.h>

// Variáveis para controlar a rotação da cabeça
float headRotationX = 0.0f;
float headRotationY = 0.0f;
float headRotationStep = 2.0f;

// Função para desenhar uma esfera
void drawSphere(float radius, int slices, int stacks)
{
    // Inicializa um novo objeto quadric
    GLUquadricObj *sphere = gluNewQuadric();
    // Define o estilo de desenho para a esfera como preenchido
    gluQuadricDrawStyle(sphere, GLU_FILL);
    // Desenha a esfera
    gluSphere(sphere, radius, slices, stacks);
    // Deleta o objeto quadric para liberar memória
    gluDeleteQuadric(sphere);
}

// Função de renderização
void display()
{
    // Limpa os buffers
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    // Reinicia a matriz model-view
    glLoadIdentity();
    // Translada a cena para o fundo
    glTranslatef(0.0f, 0.0f, -5.0f);

    // Aplica rotações na cabeça
    glRotatef(headRotationX, 1, 0, 0);
    glRotatef(headRotationY, 0, 1, 0);

    // Define a cor da cabeça e desenha
    glColor3f(1.0f, 0.87f, 0.67f);
    drawSphere(1.0, 50, 50);

    // Desenhar o olho esquerdo
    glPushMatrix();
    glTranslatef(-0.25f, 0.35f, 0.75f);
    glColor3f(0.0f, 0.0f, 0.0f);
    drawSphere(0.2, 30, 30);

    // Desenhar a 'pupila' azul dentro do olho esquerdo
    glTranslatef(0.0f, 0.0f, 0.1f); // Mover um pouco para frente no eixo z
    glColor3f(0.0f, 0.0f, 1.0f);    // Cor azul
    drawSphere(0.12, 30, 30);       // Raio menor
    glPopMatrix();

    // Desenhar o olho direito
    glPushMatrix();
    glTranslatef(0.25f, 0.35f, 0.75f);
    glColor3f(0.0f, 0.0f, 0.0f);
    drawSphere(0.2, 30, 30);

    // Desenhar a 'pupila' azul dentro do olho direito
    glTranslatef(0.0f, 0.0f, 0.1f); // Mover um pouco para frente no eixo z
    glColor3f(0.0f, 0.0f, 1.0f);    // Cor azul
    drawSphere(0.12, 30, 30);       // Raio menor
    glPopMatrix();

    // Desenhar o nariz
    glPushMatrix();
    glTranslatef(0.0f, 0.0f, 1.0f);
    glColor3f(1.0f, 0.0f, 0.0f);
    drawSphere(0.15, 30, 30);
    glPopMatrix();

    // Desenhar o cabelo esquerda
    glPushMatrix();
    glTranslatef(-0.45f, 0.8f, 0.0f);
    glColor3f(1.0f, 0.5f, 0.0f);
    drawSphere(0.45, 50, 50);
    glPopMatrix();

    // Desenhar o cabelo direita
    glPushMatrix();
    glTranslatef(0.45f, 0.8f, 0.0f);
    glColor3f(1.0f, 0.5f, 0.0f);
    drawSphere(0.45, 50, 50);
    glPopMatrix();

    // Desenhar o sorriso
    glPushMatrix();
    glTranslatef(0.0f, -0.5f, 0.9f); // Ajustar a posição do sorriso

    glScalef(0.3, 0.1, 0.0);     // Aumentar a escala no eixo x para tornar o sorriso mais longo
    glColor3f(1.0f, 0.0f, 0.0f); // Definir a cor para vermelho
    glLineWidth(10.0);           // Definir a espessura da linha

    glBegin(GL_LINE_STRIP); // Desenhar o sorriso como uma linha contínua
    for (int i = -10; i <= 10; ++i)
    {
        float x = i / 10.0f;
        float y = sqrt(1.0f - (x * x) / (0.9f)); // Usar a fórmula da elipse
        glVertex3f(x, y, 0);
    }
    glEnd();
    glPopMatrix();

    glutSwapBuffers();
}

void reshape(int w, int h)
{
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0, (float)w / h, 1.0, 100.0);
    glMatrixMode(GL_MODELVIEW);
}

void specialKeys(int key, int x, int y)
{
    switch (key)
    {
    case GLUT_KEY_LEFT:
        headRotationY -= 5 * headRotationStep;
        break;
    case GLUT_KEY_RIGHT:
        headRotationY += 5 * headRotationStep;
        break;
    case GLUT_KEY_UP:
        headRotationX -= 5 * headRotationStep;
        break;
    case GLUT_KEY_DOWN:
        headRotationX += 5 * headRotationStep;
        break;
    }
    glutPostRedisplay();
}

int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(800, 600);
    glutCreateWindow("Palhaco Adaptado");

    glEnable(GL_DEPTH_TEST);

    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutSpecialFunc(specialKeys);

    glutMainLoop();

    return 0;
}
