#include <math.h>
#include <iostream>
#include <GL/glut.h>

#define PI 3.14159265358979324

using namespace std;

// Variáveis globais.
float startPoint[3] = {5.0, 0.0, 10.0}; // Ponto A
float endPoint[3] = {10.0, 0.0, 10.0}; // Ponto B
float angleX = 0.0; // Ângulo de rotação em torno do eixo X.
float angleY = 0.0; // Ângulo de rotação em torno do eixo Y.

// Função para desenhar um disco com um buraco central.
void desenharDiscoComBuraco(float cx, float cy, float cz, float raioExterno, float raioInterno, int numFatias)
{
    glBegin(GL_TRIANGLE_STRIP);
    for (int i = 0; i <= numFatias; i++)
    {
        float theta = 2.0 * PI * static_cast<float>(i) / static_cast<float>(numFatias);
        float x = raioExterno * cos(theta);
        float y = raioExterno * sin(theta);
        glVertex3f(cx + x, cy + y, cz);
        glVertex3f(cx + raioInterno * cos(theta), cy + raioInterno * sin(theta), cz);
    }
    glEnd();
}

// Função de inicialização.
void inicializar(void)
{
    glClearColor(1.0, 1.0, 1.0, 0.0);
}

// Função de desenho.
void desenharCena(void)
{
    glClear(GL_COLOR_BUFFER_BIT);

    glLoadIdentity();
    gluLookAt(0.0, 0.0, 30.0 - (startPoint[2] + endPoint[2]) / 2.0, 0.0, 0.0, -(startPoint[2] + endPoint[2]) / 2.0, 0.0, 1.0, 0.0);

    glRotatef(angleX, 1.0, 0.0, 0.0); // Rotacionar em torno do eixo X.
    glRotatef(angleY, 0.0, 1.0, 0.0); // Rotacionar em torno do eixo Y.

    glColor3f(1.0, 0.0, 0.0); // Cor vermelha.

    // Calcular o raio externo com base na distância entre A e B.
    float raioExterno = sqrt(pow(startPoint[0] - endPoint[0], 2) + pow(startPoint[1] - endPoint[1], 2) + pow(startPoint[2] - endPoint[2], 2));

    // Calcular o raio interno com base no tamanho do buraco.
    float raioInterno = sqrt(pow(raioExterno, 2) - pow(raioExterno / 2.0, 2));

    // Desenhar o disco com o buraco.
    desenharDiscoComBuraco(startPoint[0] - (startPoint[0] + endPoint[0]) / 2.0, startPoint[1] - (startPoint[1] + endPoint[1]) / 2.0, startPoint[2] - (startPoint[2] + endPoint[2]) / 2.0, raioExterno, raioInterno, 100);

    glutSwapBuffers();
}

// Função de timer para controlar a velocidade de rotação.
void temporizador(int value)
{
    angleX += 1.0; // Incrementar o ângulo em torno do eixo X.
    angleY += 1.0; // Incrementar o ângulo em torno do eixo Y.

    if (angleX > 360.0)
        angleX -= 360.0;

    if (angleY > 360.0)
        angleY -= 360.0;

    glutPostRedisplay();
    glutTimerFunc(10, temporizador, 0);
}

// Função de redimensionamento da janela OpenGL.
void redimensionar(int largura, int altura)
{
    glViewport(0, 0, (GLsizei)largura, (GLsizei)altura);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60.0, (float)largura / (float)altura, 1.0, 100.0);
    glMatrixMode(GL_MODELVIEW);
}

// Função principal.
int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(500, 500);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Disco com Buraco Rotacionando");
    inicializar();
    glutDisplayFunc(desenharCena);
    glutReshapeFunc(redimensionar);
    glutTimerFunc(10, temporizador, 0);
    glutMainLoop();

    return 0;
}
