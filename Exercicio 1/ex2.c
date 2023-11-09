/*
  Enzo Reis de Oliveira
  156474
  Exercicio 2 - Proposta de Exercícios - OpenGL - Interação
*/

#include <GL/glut.h>

// Funções que serão utilizadas
void draw();
void mouse(int button, int state, int mouse_x, int mouse_y);
void keyboard(unsigned char key, int x, int y);

// Variáveis globais que serão utilizadas
float x = 0.0f;
float y = 0.0f;
// Red, green, blue
float r = 0.0f;
float g = 0.0f;
float b = 1.0f;

int main(int argc, char **argv) 
{
    // Inicialização do GLUT
    glutInit(&argc, argv);

    // Configuração inicial da janela
    glutInitDisplayMode(GLUT_SINGLE);
    glutInitWindowSize(500, 500);
    glutInitWindowPosition(100, 100);

    // Criação da janela
    glutCreateWindow("Ponto Colorido com Mouse e Teclado");

    // Registra as funções de callback
    glutDisplayFunc(draw);
    glutMouseFunc(mouse);
    glutKeyboardFunc(keyboard);

    // Entra no laço principal do GLUT
    glutMainLoop();

    return 0;
}

void draw() 
{
    // Geralmente antes de qualquer procedimento devemos limpar a área onde vamos desenhar
    glClear(GL_COLOR_BUFFER_BIT);

    // Cor azul
    glColor3f(r, g, b);

    // Definindo o tamanho do ponto
    glPointSize(5.0);

    // Marcam o início e o fim da lista de vértices e descrevem o tipo de objeto que será desenhado
    glBegin(GL_POINTS);
        glVertex2f(x, y);
    glEnd();

    glFlush();
}

void mouse(int button, int state, int mouse_x, int mouse_y) 
{
    // Verificação para ver se é o botão esquerdo do mouse sendo utilizado,
    // e se a ação do mouse é para baixo ou para cima (clicando ou soltando)
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) 
    {
        // Está convertendo as coordenadas do mouse (mouse_x e mouse_y) para o sistema de coordenadas do OpenGL
        x = (float)(mouse_x - 250) / 250;
        y = (float)(250 - mouse_y) / 250;

        // Basicamente chamar draw para fazer a mudança
        glutPostRedisplay();
    }
}

void keyboard(unsigned char key, int x, int y) 
{
    // Basicamente toda vez que clica em uma das teclas, as variáveis globais são alteradas de acordo com cada número
    switch(key) 
    {
        case '0':
            r = 0.0f; g = 0.0f; b = 0.0f; break;
        case '1':
            r = 1.0f; g = 0.0f; b = 0.0f; break;
        case '2':
            r = 0.0f; g = 1.0f; b = 0.0f; break;
        case '3':
            r = 0.0f; g = 0.0f; b = 1.0f; break;
        case '4':
            r = 1.0f; g = 1.0f; b = 0.0f; break;
        case '5':
            r = 1.0f; g = 0.0f; b = 1.0f; break;
        case '6':
            r = 0.0f; g = 1.0f; b = 1.0f; break;
        case '7':
            r = 0.5f; g = 0.5f; b = 0.5f; break;
        case '8':
            r = 0.6f; g = 0.4f; b = 0.2f; break;
        case '9':
            r = 0.9f; g = 0.7f; b = 0.1f; break;
        default: return;
    }

    // Depois de trocar, apenas chamar de novo para trocar de cor
    glutPostRedisplay();
}
