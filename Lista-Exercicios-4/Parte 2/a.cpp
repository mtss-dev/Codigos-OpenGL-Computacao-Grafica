#include <math.h>
#include <iostream>
#include <GL/glut.h>

using namespace std;

#define PI 3.14159265358979324

// Globals.
static int p = 30;                                         // Number of radial divisions.
static int q = 1;                                          // Number of height divisions.
static float *vertices = nullptr;                          // Vertex array of the mapped sample on the cone.
static float Xangle = 150.0, Yangle = 60.0, Zangle = 60.0; // Angles to rotate the cone.

// Functions to map the grid vertex (u_i,v_j) to the mesh vertex (f(u_i,v_j), g(u_i,v_j), h(u_i,v_j)) on the cone.
float f(int i, int j)
{
    float angle = (-1 + 2 * static_cast<float>(i) / p) * PI;
    float radius = 1.0 - static_cast<float>(j) / q;
    return (radius * cos(angle));
}

float g(int i, int j)
{
    float angle = (-1 + 2 * static_cast<float>(i) / p) * PI;
    float radius = 1.0 - static_cast<float>(j) / q;
    return (radius * sin(angle));
}

float h(int i, int j)
{
    return (-1 + 2 * static_cast<float>(j) / q);
}

// Routine to fill the vertex array with coordinates of the mapped sample points.
void fillVertexArray(void)
{
    int k = 0;
    for (int j = 0; j <= q; j++)
    {
        for (int i = 0; i <= p; i++)
        {
            vertices[k++] = f(i, j);
            vertices[k++] = g(i, j);
            vertices[k++] = h(i, j);
        }
    }
}

// Initialization routine.
void setup(void)
{
    glEnableClientState(GL_VERTEX_ARRAY);

    glClearColor(1.0, 1.0, 1.0, 0.0);
}

// Drawing routine.
void drawScene(void)
{
    vertices = new float[3 * (p + 1) * (q + 1)]; // Dynamic array allocation with new value of p and q.

    glVertexPointer(3, GL_FLOAT, 0, vertices);
    glClear(GL_COLOR_BUFFER_BIT);

    glLoadIdentity();
    gluLookAt(0.0, 0.0, 4.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);

    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    glColor3f(0.0, 0.0, 0.0);

    // Rotate scene.
    glRotatef(Zangle, 0.0, 0.0, 1.0);
    glRotatef(Yangle, 0.0, 1.0, 0.0);
    glRotatef(Xangle, 1.0, 0.0, 0.0);

    // Fill the vertex array.
    fillVertexArray();

    // Make the approximating triangular mesh.
    for (int j = 0; j < q; j++)
    {
        glBegin(GL_TRIANGLE_STRIP);
        for (int i = 0; i <= p; i++)
        {
            glArrayElement((j + 1) * (p + 1) + i);
            glArrayElement(j * (p + 1) + i);
        }
        glEnd();
    }

    glutSwapBuffers();
    delete[] vertices;
}

// OpenGL window reshape routine.
void resize(int w, int h)
{
    glViewport(0, 0, (GLsizei)w, (GLsizei)h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60.0, (float)w / (float)h, 1.0, 50.0);
    glMatrixMode(GL_MODELVIEW);
}

// Keyboard input processing routine.
void keyInput(unsigned char key, int x, int y)
{
    switch (key)
    {
    case 27:
        exit(0);
        break;
    case 'x':
        Xangle += 5.0;
        if (Xangle > 360.0)
            Xangle -= 360.0;
        glutPostRedisplay();
        break;
    case 'X':
        Xangle -= 5.0;
        if (Xangle < 0.0)
            Xangle += 360.0;
        glutPostRedisplay();
        break;
    case 'y':
        Yangle += 5.0;
        if (Yangle > 360.0)
            Yangle -= 360.0;
        glutPostRedisplay();
        break;
    case 'Y':
        Yangle -= 5.0;
        if (Yangle < 0.0)
            Yangle += 360.0;
        glutPostRedisplay();
        break;
    case 'z':
        Zangle += 5.0;
        if (Zangle > 360.0)
            Zangle -= 360.0;
        glutPostRedisplay();
        break;
    case 'Z':
        Zangle -= 5.0;
        if (Zangle < 0.0)
            Zangle += 360.0;
        glutPostRedisplay();
        break;
    default:
        break;
    }
}

// Callback routine for non-ASCII key entry.
void specialKeyInput(int key, int x, int y)
{
    if (key == GLUT_KEY_LEFT)
    {
        if (p > 3)
            p -= 1;
    }
    if (key == GLUT_KEY_RIGHT)
    {
        p += 1;
    }
    if (key == GLUT_KEY_DOWN)
    {
        if (q > 1)
            q -= 1;
    }
    if (key == GLUT_KEY_UP)
    {
        q += 1;
    }

    glutPostRedisplay();
}

// Routine to output interaction instructions to the C++ window.
void printInteraction(void)
{
    cout << "Interaction:" << endl;
    cout << "Press left/right arrow keys to increase/decrease the number of radial divisions." << endl
         << "Press up/down arrow keys to increase/decrease the number of height divisions." << endl
         << "Press x, X, y, Y, z, Z to rotate the cone." << endl;
}

// Main routine.
int main(int argc, char **argv)
{
    printInteraction();
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(500, 500);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Superficie A");
    setup();
    glutDisplayFunc(drawScene);
    glutReshapeFunc(resize);
    glutKeyboardFunc(keyInput);
    glutSpecialFunc(specialKeyInput);
    glutMainLoop();

    return 0;
}
