/*
  Enzo Reis de Oliveira
  156474
  Exercicio 1 - Proposta de Exercícios - OpenGL - Interação
*/

#include <stdio.h>
#include <GL/glut.h>


// Funções que serão utilizadas
void draw();
void mouse(int button, int state, int mouse_x, int mouse_y);


// Apenas variáveis globais
float x = 0.0f;
float y = 0.0f;


int main(int argc, char** argv) 
{
    glutInit(&argc, argv); 
    // Iniciando com um buffer 'single'
    glutInitDisplayMode(GLUT_SINGLE); 
    // Apenas inicializando a janela para tamanho 500
    glutInitWindowSize(500, 500); 
    // Apenas dá a coordenada do canto superior esquerdo. Ou seja, a janela vai ter tamanho de 500x500 começando no canto superior esquerdo posição (100,100)
    glutInitWindowPosition(100, 100); 
    // Criando a janela com uma string que será chamada depois
    glutCreateWindow("Ponto Azul com Mouse"); 
    // Aqui estamos chamando a função que desenha
    glutDisplayFunc(draw); 
    // Aqui estamos chamando a função que interage com o mouse
    glutMouseFunc(mouse); 
    glutMainLoop();

    return 0;
}

void draw() 
{
    // Geralmente antes de qualquer procedimento devemos limpar a área onde vamos desenhar
    glClear(GL_COLOR_BUFFER_BIT); 
    // Cor azul
    glColor3f(0.0, 0.0, 1.0); 
    // Definindo o tamanho do ponto
    glPointSize(5.0); 
    // Marcam o início e o fim da lista de vértices e descrevem o tipo de objeto que será desenhado
    glBegin(GL_POINTS); 
        // Posição do ponto (inicialmente 0,0)
        glVertex2f(x, y); 
    glEnd();
    glFlush();
}

void mouse(int button, int state, int mouse_x, int mouse_y) 
{
    // Verificação para ver se é o botão esquerdo do mouse sendo utilizado, e se a ação do mouse é para baixo ou para cima (clicando ou soltando)
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) 
    {
        // Está convertendo as coordenadas do mouse (mouse_x e mouse_y) para o sistema de coordenadas do OpenGL
        x = (float)(mouse_x - 250) / 250;
        y = (float)(250 - mouse_y) / 250;
        // Basicamente chamar draw para fazer a mudança
        glutPostRedisplay();
    }
}
