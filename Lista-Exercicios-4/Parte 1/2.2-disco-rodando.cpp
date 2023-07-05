#include <math.h>
#include <iostream>
#include <GL/glut.h>

#define PI 3.14159265358979324

using namespace std;

// Globals.
float A[3] = {5.0, 0.0, 10.0}; // Point A
float B[3] = {10.0, 0.0, 10.0}; // Point B
float angleX = 0.0; // Angle for rotation around X-axis.
float angleY = 0.0; // Angle for rotation around Y-axis.

// Function to draw a disk with a central hole.
void drawDiskWithHole(float cx, float cy, float cz, float outerRadius, float innerRadius, int numSlices)
{
    glBegin(GL_TRIANGLE_STRIP);
    for (int i = 0; i <= numSlices; i++)
    {
        float theta = 2.0 * PI * static_cast<float>(i) / static_cast<float>(numSlices);
        float x = outerRadius * cos(theta);
        float y = outerRadius * sin(theta);
        glVertex3f(cx + x, cy + y, cz);
        glVertex3f(cx + innerRadius * cos(theta), cy + innerRadius * sin(theta), cz);
    }
    glEnd();
}

// Initialization routine.
void setup(void)
{
    glClearColor(1.0, 1.0, 1.0, 0.0);
}

// Drawing routine.
void drawScene(void)
{
    glClear(GL_COLOR_BUFFER_BIT);

    glLoadIdentity();
    gluLookAt(0.0, 0.0, 30.0 - (A[2] + B[2]) / 2.0, 0.0, 0.0, -(A[2] + B[2]) / 2.0, 0.0, 1.0, 0.0);

    glRotatef(angleX, 1.0, 0.0, 0.0); // Rotate around X-axis.
    glRotatef(angleY, 0.0, 1.0, 0.0); // Rotate around Y-axis.

    glColor3f(0.0, 0.0, 1.0); // Blue color.

    // Calculate the outer radius based on the distance between A and B.
    float outerRadius = sqrt(pow(A[0] - B[0], 2) + pow(A[1] - B[1], 2) + pow(A[2] - B[2], 2));

    // Calculate the inner radius based on the size of the hole.
    float innerRadius = sqrt(pow(outerRadius, 2) - pow(outerRadius / 2.0, 2));

    // Draw the disk with a hole.
    drawDiskWithHole(A[0] - (A[0] + B[0]) / 2.0, A[1] - (A[1] + B[1]) / 2.0, A[2] - (A[2] + B[2]) / 2.0, outerRadius, innerRadius, 100);

    glutSwapBuffers();
}

// Timer function to control the rotation speed.
void timer(int value)
{
    angleX += 1.0; // Increment angle around X-axis.
    angleY += 1.0; // Increment angle around Y-axis.

    if (angleX > 360.0)
        angleX -= 360.0;

    if (angleY > 360.0)
        angleY -= 360.0;

    glutPostRedisplay();
    glutTimerFunc(10, timer, 0);
}

// OpenGL window reshape routine.
void reshape(int w, int h)
{
    glViewport(0, 0, (GLsizei)w, (GLsizei)h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60.0, (float)w / (float)h, 1.0, 100.0);
    glMatrixMode(GL_MODELVIEW);
}

// Main routine.
int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(500, 500);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("disk_with_hole_rotating.cpp");
    setup();
    glutDisplayFunc(drawScene);
    glutReshapeFunc(reshape);
    glutTimerFunc(10, timer, 0);
    glutMainLoop();

    return 0;
}