#include <GL/glut.h>
#include <math.h>
#include <iostream>

using namespace std;

float startPoint[3] = {1.0, 0.0, 1.0};
float endPoint[3] = {7.0, 0.0, 7.0};
float angleX = 0, angleY = 0;

void interpolate(float t, float *output)
{
    output[0] = (1 - t) * startPoint[0] + t * endPoint[0];
    output[1] = (1 - t) * startPoint[1] + t * endPoint[1];
    output[2] = (1 - t) * startPoint[2] + t * endPoint[2];
}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    gluLookAt(0, -10, 5, 0, 0, 0, 0, 0, 1);

    glRotatef(angleX, 1.0f, 0.0f, 0.0f);
    glRotatef(angleY, 0.0f, 1.0f, 0.0f);

    glColor3f(0.0, 0.0, 0.0); // Preto

    glBegin(GL_TRIANGLE_STRIP);
    for (double t = 0.0; t <= 1.0; t += 0.01)
    {
        float P[3];
        interpolate(t, P);
        for (int i = 0; i <= 360; i += 10)
        {
            float theta = i * M_PI / 180;
            glVertex3f(P[0] * cos(theta), P[0] * sin(theta), P[2]);
        }
    }
    glEnd();
    glutSwapBuffers();
}

void init()
{
    glClearColor(1.0, 1.0, 1.0, 0.0); // Fundo branco
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60.0, 1.0, 0.1, 100.0);
    glMatrixMode(GL_MODELVIEW);
}

void handleKeypress(unsigned char key, int x, int y)
{
    switch (key)
    {
    case 'a':
    case 'A':
        angleY -= 5;
        break;
    case 'd':
    case 'D':
        angleY += 5;
        break;
    case 'w':
    case 'W':
        angleX -= 5;
        break;
    case 's':
    case 'S':
        angleX += 5;
        break;
    }
    glutPostRedisplay();
}

int main(int argc, char *argv[])
{
    std::cout << "Use 'a' or 'd' para mover no eixo x, 'w' ou 's' para mover no eixo y" << std::endl;
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(640, 480);
    glutInitWindowPosition(100, 150);
    glutCreateWindow("Superficie Canonica");
    glutDisplayFunc(display);
    glutKeyboardFunc(handleKeypress);
    init();
    glutMainLoop();
    return 0;
}
