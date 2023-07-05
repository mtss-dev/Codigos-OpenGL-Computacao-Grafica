/* 
14 - Escreva um programa de animação que implemente o procedimento de rotação
bidimensional mostrado na apostila. Um polígono de entrada deve ser girado
repetidamente em pequenos passos em torno de um ponto de pivô no plano xy.
Pequenos ângulos devem ser usados para cada passo sucessivo na rotação, e
aproximações para as funções seno e cosseno devem ser usadas para acelerar os
cálculos. Para evitar excesso e acúmulo de erros de arredondamento, redenir
os valores originais das coordenadas para o objeto no início de cada nova
revolução.
*/

//Como compilar: g++ 14.cpp -o 14 -lstdc++ -lGL -lglut -lGLU
//Para executar: ./14

//Certifique de que todas as bibliotecas estejam instaladas

#include <GL/freeglut.h>
#include <math.h>

const int WINDOW_WIDTH = 800;
const int WINDOW_HEIGHT = 600;
const float PI = 3.14159265359f;
const float ROTATION_ANGLE = 0.05f;
const float PIVOT_X = 300;
const float PIVOT_Y = 300;

float angle = 0.0f;

void initialize() {
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, WINDOW_WIDTH, 0, WINDOW_HEIGHT);
}

void drawPolygon() {
    glColor3f(1.0, 1.0, 1.0);
    glBegin(GL_POLYGON);
    glVertex2f(100, 100);
    glVertex2f(200, 100);
    glVertex2f(200, 200);
    glVertex2f(100, 200);
    glEnd();
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glTranslatef(PIVOT_X, PIVOT_Y, 0.0);
    glRotatef(angle, 0.0, 0.0, 1.0);
    glTranslatef(-PIVOT_X, -PIVOT_Y, 0.0);

    drawPolygon();

    glFlush();
}

void idle() {
    angle += ROTATION_ANGLE;
    if (angle >= 360.0f)
        angle -= 360.0f;
    glutPostRedisplay();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Polygon Rotation");

    initialize();
    glutDisplayFunc(display);
    glutIdleFunc(idle);

    glutMainLoop();
    return 0;
}
