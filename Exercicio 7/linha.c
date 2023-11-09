/*
Enzo Reis de Oliveira
156474
*/

#include <GL/glut.h>

// Codificação das regiões para o algoritmo de Cohen-Sutherland
const int REGIAO_INTERNA = 0; // Dentro da janela de recorte
const int REGIAO_ESQUERDA = 1;
const int REGIAO_DIREITA = 2;
const int REGIAO_INFERIOR = 4;
const int REGIAO_SUPERIOR = 8;

// Coordenadas da janela de recorte
float recorteXMin = 50, recorteYMin = 50, recorteXMax = 200, recorteYMax = 200;
int contadorCliques = 0;
float linhaX0, linhaY0, linhaX1, linhaY1;

// Protótipos das funções
void recortarLinha(float x0, float y0, float x1, float y1);
void desenhar();
void cliqueMouse(int botao, int estado, int x, int y);
void inicializar();
int calcularCodigoRegiao(float x, float y);

int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(400, 300);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Algoritmo de Recorte de Cohen-Sutherland");
    inicializar();
    glutDisplayFunc(desenhar);
    glutMouseFunc(cliqueMouse);
    glutMainLoop();
    return 0;
}

void inicializar()
{
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glMatrixMode(GL_PROJECTION);
    gluOrtho2D(0, 400, 0, 300);
}

void desenhar()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1.0, 0.0, 0.0);

    // Desenhar a janela de recorte
    glBegin(GL_LINE_LOOP);
    glVertex2f(recorteXMin, recorteYMin);
    glVertex2f(recorteXMax, recorteYMin);
    glVertex2f(recorteXMax, recorteYMax);
    glVertex2f(recorteXMin, recorteYMax);
    glEnd();

    glFlush();
}

int calcularCodigoRegiao(float x, float y)
{
    int codigo = REGIAO_INTERNA;

    if (x < recorteXMin)
        codigo |= REGIAO_ESQUERDA;
    else if (x > recorteXMax)
        codigo |= REGIAO_DIREITA;
    if (y < recorteYMin)
        codigo |= REGIAO_INFERIOR;
    else if (y > recorteYMax)
        codigo |= REGIAO_SUPERIOR;

    return codigo;
}

void recortarLinha(float x0, float y0, float x1, float y1)
{
    int codigoP0 = calcularCodigoRegiao(x0, y0);
    int codigoP1 = calcularCodigoRegiao(x1, y1);
    int aceitar = 0;

    while (1)
    {
        if (!(codigoP0 | codigoP1))
        {
            // Ambos pontos dentro: aceitar e sair
            aceitar = 1;
            break;
        }
        else if (codigoP0 & codigoP1)
        {
            // Ambos pontos fora: rejeitar e sair
            break;
        }
        else
        {
            // Calcula o ponto de interseção
            float x, y;
            int codigoFora = codigoP0 ? codigoP0 : codigoP1;

            if (codigoFora & REGIAO_SUPERIOR)
            {
                x = x0 + (x1 - x0) * (recorteYMax - y0) / (y1 - y0);
                y = recorteYMax;
            }
            else if (codigoFora & REGIAO_INFERIOR)
            {
                x = x0 + (x1 - x0) * (recorteYMin - y0) / (y1 - y0);
                y = recorteYMin;
            }
            else if (codigoFora & REGIAO_DIREITA)
            {
                y = y0 + (y1 - y0) * (recorteXMax - x0) / (x1 - x0);
                x = recorteXMax;
            }
            else if (codigoFora & REGIAO_ESQUERDA)
            {
                y = y0 + (y1 - y0) * (recorteXMin - x0) / (x1 - x0);
                x = recorteXMin;
            }

            // Substitua ponto fora pela interseção
            if (codigoFora == codigoP0)
            {
                x0 = x;
                y0 = y;
                codigoP0 = calcularCodigoRegiao(x0, y0);
            }
            else
            {
                x1 = x;
                y1 = y;
                codigoP1 = calcularCodigoRegiao(x1, y1);
            }
        }
    }
    if (aceitar)
    {
        glColor3f(0.0, 1.0, 0.0);
        glBegin(GL_LINES);
        glVertex2f(x0, y0);
        glVertex2f(x1, y1);
        glEnd();
    }
    glFlush();
}

void cliqueMouse(int botao, int estado, int x, int y)
{
    if (botao == GLUT_LEFT_BUTTON && estado == GLUT_DOWN)
    {
        if (contadorCliques == 0)
        {
            linhaX0 = x;
            linhaY0 = 300 - y;
            contadorCliques = 1;
        }
        else
        {
            linhaX1 = x;
            linhaY1 = 300 - y;
            contadorCliques = 0;

            desenhar();
            recortarLinha(linhaX0, linhaY0, linhaX1, linhaY1);
        }
    }
}
