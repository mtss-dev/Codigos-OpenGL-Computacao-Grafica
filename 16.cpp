/*
16 - Repita o exercício anterior usando as operações matriciais da OpenGL.
*/

// Como compilar: g++ 16.cpp -o 16 -lstdc++ -lGL -lglut -lGLU
// Para executar: ./16

// Certifique de que todas as bibliotecas estejam instaladas

#include <GL/freeglut.h>
#include <math.h>

// Tamanho da janela de exibição
int window_width = 800;
int window_height = 800;

// Parâmetros do caminho circular
float circle_radius = 300.0;
float circle_speed = 0.01; // Sentido horário
float circle_angle = 0.0;

// Função para desenhar o quadrado
void drawSquare() {
    glClear(GL_COLOR_BUFFER_BIT);
    glLoadIdentity();

    // Define a cor do quadrado para preto
    glColor3f(0.0, 0.0, 0.0);

    // Calcula as coordenadas do quadrado no caminho circular
    float x = circle_radius * cos(circle_angle);
    float y = circle_radius * -sin(circle_angle);

    // Cria a matriz de transformação de translação
    GLfloat translation_matrix[] = {
        1.0, 0.0, 0.0, 0.0,
        0.0, 1.0, 0.0, 0.0,
        0.0, 0.0, 1.0, 0.0,
        x, y, 0.0, 1.0
    };

    // Aplica a matriz de translação
    glMultMatrixf(translation_matrix);

    // Desenha o quadrado
    glBegin(GL_QUADS);
    glVertex2f(-50.0, -50.0);
    glVertex2f(50.0, -50.0);
    glVertex2f(50.0, 50.0);
    glVertex2f(-50.0, 50.0);
    glEnd();

    // Atualiza o ângulo do quadrado para fazer o movimento circular
    circle_angle += circle_speed;

    glFlush();
    glutSwapBuffers();
}

// Função para atualizar o tamanho da janela
void reshape(int width, int height) {
    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-window_width / 2, window_width / 2, -window_height / 2, window_height / 2);
    glMatrixMode(GL_MODELVIEW);
}

// Função para lidar com eventos de teclado
void keyboard(unsigned char key, int x, int y) {
    if (key == 27) // Tecla Esc
        exit(0);
}

// Função para atualizar a cena a cada quadro
void update(int value) {
    glutPostRedisplay();
    glutTimerFunc(16, update, 0); // Aproximadamente 60 quadros por segundo (1000ms / 60)
}

// Função principal
int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
    glutInitWindowSize(window_width, window_height);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Caminho Circular");
    glClearColor(1.0, 1.0, 1.0, 1.0);
    glutDisplayFunc(drawSquare);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(keyboard);
    glutTimerFunc(0, update, 0);
    glutMainLoop();
    return 0;
}
