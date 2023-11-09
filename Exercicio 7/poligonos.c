/*
Enzo Reis de Oliveira
156474
*/

#include <GL/glut.h>
#include <stdio.h>
#include <stdbool.h>

typedef struct
{
    float x, y;
} Ponto;

Ponto triangulo[3];
int indicePonto = 0;

bool dentro(Ponto pt, Ponto cantoSuperiorEsq, Ponto cantoInferiorDir, int borda)
{
    switch (borda)
    {
    case 0:
        return pt.y >= cantoSuperiorEsq.y; // Borda superior
    case 1:
        return pt.x <= cantoInferiorDir.x; // Borda direita
    case 2:
        return pt.y <= cantoInferiorDir.y; // Borda inferior
    case 3:
        return pt.x >= cantoSuperiorEsq.x; // Borda esquerda
    }
    return false;
}

Ponto intersecao(Ponto p1, Ponto p2, Ponto cantoSuperiorEsq, Ponto cantoInferiorDir, int borda)
{
    float m = (p2.y - p1.y) / (p2.x - p1.x);
    Ponto pt;
    switch (borda)
    {
    case 0: // Borda superior
        pt.x = p1.x + (cantoSuperiorEsq.y - p1.y) / m;
        pt.y = cantoSuperiorEsq.y;
        break;
    case 1: // Borda direita
        pt.x = cantoInferiorDir.x;
        pt.y = p1.y + m * (cantoInferiorDir.x - p1.x);
        break;
    case 2: // Borda inferior
        pt.x = p1.x + (cantoInferiorDir.y - p1.y) / m;
        pt.y = cantoInferiorDir.y;
        break;
    case 3: // Borda esquerda
        pt.x = cantoSuperiorEsq.x;
        pt.y = p1.y + m * (cantoSuperiorEsq.x - p1.x);
        break;
    }
    return pt;
}

void recortarPoligono(Ponto ptsEntrada[], int qtdEntrada, Ponto ptsSaida[], int *qtdSaida, Ponto cantoSuperiorEsq, Ponto cantoInferiorDir)
{
    Ponto s = ptsEntrada[qtdEntrada - 1]; // O último ponto
    for (int borda = 0; borda < 4; borda++)
    {
        *qtdSaida = 0;
        for (int i = 0; i < qtdEntrada; i++)
        {
            Ponto e = ptsEntrada[i]; // O ponto atual
            if (dentro(e, cantoSuperiorEsq, cantoInferiorDir, borda))
            {
                if (!dentro(s, cantoSuperiorEsq, cantoInferiorDir, borda))
                {
                    ptsSaida[*qtdSaida] = intersecao(s, e, cantoSuperiorEsq, cantoInferiorDir, borda);
                    (*qtdSaida)++;
                }
                ptsSaida[*qtdSaida] = e;
                (*qtdSaida)++;
            }
            else if (dentro(s, cantoSuperiorEsq, cantoInferiorDir, borda))
            {
                ptsSaida[*qtdSaida] = intersecao(s, e, cantoSuperiorEsq, cantoInferiorDir, borda);
                (*qtdSaida)++;
            }
            s = e;
        }
        qtdEntrada = *qtdSaida;
        for (int i = 0; i < qtdEntrada; i++)
        {
            ptsEntrada[i] = ptsSaida[i];
        }
    }
}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT);

    Ponto cantoRecorte1 = {100, 100};
    Ponto cantoRecorte2 = {400, 400};

    // Desenha área de recorte
    glColor3f(1.0, 0.0, 0.0);
    glBegin(GL_LINE_LOOP);
    glVertex2f(cantoRecorte1.x, cantoRecorte1.y);
    glVertex2f(cantoRecorte2.x, cantoRecorte1.y);
    glVertex2f(cantoRecorte2.x, cantoRecorte2.y);
    glVertex2f(cantoRecorte1.x, cantoRecorte2.y);
    glEnd();

    // Desenha triângulo original
    glColor3f(0.0, 1.0, 0.0);
    glBegin(GL_TRIANGLES);
    for (int i = 0; i < 3; i++)
    {
        glVertex2f(triangulo[i].x, triangulo[i].y);
    }
    glEnd();

    // Recorta o triângulo
    Ponto pontosRecortados[10];
    int contagemRecortados = 0;
    recortarPoligono(triangulo, 3, pontosRecortados, &contagemRecortados, cantoRecorte1, cantoRecorte2);

    // Desenha polígono recortado
    if (contagemRecortados > 0)
    {
        glColor3f(0.0, 0.0, 1.0);
        glBegin(GL_POLYGON);
        for (int i = 0; i < contagemRecortados; i++)
        {
            glVertex2f(pontosRecortados[i].x, pontosRecortados[i].y);
        }
        glEnd();
    }

    glFlush();
}

void mouse(int botao, int estado, int x, int y)
{
    if (botao == GLUT_LEFT_BUTTON && estado == GLUT_DOWN)
    {
        if (indicePonto < 3)
        {
            triangulo[indicePonto].x = x;
            triangulo[indicePonto].y = 500 - y; // Conversão de coordenada
            indicePonto++;
            if (indicePonto == 3)
            {
                glutPostRedisplay();
            }
        }
    }
}

int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitWindowSize(500, 500);
    glutCreateWindow("Sutherland-Hodgman");
    glClearColor(1.0, 1.0, 1.0, 1.0);
    glOrtho(0, 500, 0, 500, -1, 1);
    glutDisplayFunc(display);
    glutMouseFunc(mouse);
    glutMainLoop();
    return 0;
}
