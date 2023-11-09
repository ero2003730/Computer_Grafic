/*
  Enzo Reis de Oliveira
  156474
  Exercicio 3 - Proposta de Exercícios - OpenGL - Interação
*/

#include <GL/glut.h>
#include <stdbool.h>

// funcoes que serao utilizadas 
void draw();
void mouse(int button, int state, int mouse_x, int mouse_y);
void keyboard(unsigned char key, int x, int y);


// variaveis globais que serao utilizadas
float x_1 = 0.0f;
float y_1 = 0.0f;
float x_2 = 0.0f;
float y_2 = 0.0f;
// red green blue
float r = 0.0f;
float g = 0.0f;
float b = 1.0f;
// variavel de controle, para saber se estamos no primeiro ou segundo click
bool first_click = true;


int main(int argc, char **argv) 
{
  // Inicialização do GLUT
    glutInit(&argc, argv);

  // Configuração inicial da janela
    glutInitDisplayMode(GLUT_SINGLE);
    glutInitWindowSize(500, 500);
    glutInitWindowPosition(100, 100);

  // Criação da janela
    glutCreateWindow("Traçar linha entre dois pontos");

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

    // So queremos que gere uma nova linha quando tivermos no segundo click
    // Só desenha a linha após o segundo clique
    if (first_click == false)  
    {
        glBegin(GL_LINES); 
            glVertex2f(x_1, y_1); 
            glVertex2f(x_2, y_2); 
        glEnd();
    }
    glFlush();
}

void mouse(int button, int state, int mouse_x, int mouse_y)
{
    // Verificação para ver se é o botão esquerdo do mouse sendo utilizado,
    // e se a ação do mouse é para baixo ou para cima (clicando ou soltando)
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
    {
        // Está convertendo as coordenadas do mouse (mouse_x e mouse_y) para o sistema de      coordenadas do OpenGL
        float x = (float)(mouse_x - 250) / 250;
        float y = (float)(250 - mouse_y) / 250;

        // Verificando se é o primeiro click sendo feito, se for o primeiro click entao salvar as posicoes referentes ao primeiro click
        if (first_click == true) 
        {
            x_1 = x;
            y_1 = y;
            first_click = false;
        } 
        // Verificando se é o segundo click endo feito, se for o segundo click entao salvar as posicoes referentes ao segundo click
        else 
        {
            x_2 = x;
            y_2 = y;
            first_click = true;
        }

        glutPostRedisplay();
    }
}

void keyboard(unsigned char key, int x, int y) 
{
  // Basicamente toda vez que clica em uma das teclas, as variaveis globais sao alteradas de acordo com cada numero
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
