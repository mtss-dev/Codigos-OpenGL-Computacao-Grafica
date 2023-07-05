#include <GL/glut.h>
#include <cmath>
#include <iostream>

float abc[4][3] = {{1.0, 0.0, 2.0}, {3.0, 0.0, 4.0}, {2.0, 0.0, 6.0}, {5.0, 0.0, 7.0}};
float angleX = 0, angleY = 0, angleZ = 0;

void drawBezier(float t, float *output)
{
    for (int i = 0; i < 3; i++)
    {
        output[i] = pow((1 - t), 3) * abc[0][i] + 3 * t * pow((1 - t), 2) * abc[1][i] + 3 * (1 - t) * pow(t, 2) * abc[2][i] + pow(t, 3) * abc[3][i];
    }
}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    gluLookAt(0, -10, 5, 0, 0, 0, 0, 0, 1);

    glRotatef(angleX, 1.0f, 0.0f, 0.0f);
    glRotatef(angleY, 0.0f, 1.0f, 0.0f);
    glRotatef(angleZ, 0.0f, 0.0f, 1.0f);

    glColor3f(0.0, 0.0, 0.0); // Black

    glBegin(GL_TRIANGLE_STRIP);
    for (float t = 0.0; t <= 1.0; t += 0.01)
    {
        float P[3];
        drawBezier(t, P);
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
    glClearColor(1.0, 1.0, 1.0, 0.0); // White background
    glEnable(GL_DEPTH_TEST);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60.0, 1.0, 0.1, 100.0);
    glMatrixMode(GL_MODELVIEW);
}

void handleKeypress(unsigned char key, int x, int y)
{
    switch (key)
    {
    case 'x':
        angleX += 5;
        break;
    case 'X':
        angleX -= 5;
        break;
    case 'y':
        angleY += 5;
        break;
    case 'Y':
        angleY -= 5;
        break;
    case 'z':
        angleZ += 5;
        break;
    case 'Z':
        angleZ -= 5;
        break;
    }
    glutPostRedisplay();
}

int main(int argc, char *argv[])
{
    std::cout << "Use x or X to move the x-axis, y or Y to y-axis, and z or Z to z-axis" << std::endl;

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(640, 480);
    glutInitWindowPosition(100, 150);
    glutCreateWindow("Bezier Surface");
    glutDisplayFunc(display);
    glutKeyboardFunc(handleKeypress);
    init();
    glutMainLoop();
    return 0;
}
