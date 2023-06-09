/*
20 - Repita o exercício anterior usando as operações matriciais da OpenGL.
*/

// Como compilar: g++ 20.cpp -o 20 -lstdc++ -lGL -lglut -lGLU
// Para executar: ./20

// Certifique de que todas as bibliotecas estejam instaladas

#include <GL/glut.h>
#include <math.h>

// Tamanho da janela de exibição
int window_width = 800;
int window_height = 800;

// Parâmetros do caminho circular
float circle_radius = 300.0;
float circle_speed = 0.01; // Sentido horário
float circle_angle = 0.0;

// Parâmetros da rotação do quadrado
float square_rotation_angle = 0.0;
float square_rotation_speed = circle_speed * 25; // Uma revolução por quarto de caminho

// Parâmetros do pulso do quadrado
float square_pulse_scale = 1.0;
float square_pulse_min_scale = 0.5;
float square_pulse_max_scale = 1.0;
float square_pulse_step = 0.005;
bool square_pulse_increasing = true;

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
    glTranslatef(x, y, 0.0);

    // Cria a matriz de transformação de rotação
    glRotatef(square_rotation_angle, 0.0, 0.0, -1.0);

    // Aplica o pulso do quadrado
    glScalef(square_pulse_scale, square_pulse_scale, 1.0);

    // Desenha o quadrado
    glBegin(GL_QUADS);
    glVertex2f(-50.0, -50.0);
    glVertex2f(50.0, -50.0);
    glVertex2f(50.0, 50.0);
    glVertex2f(-50.0, 50.0);
    glEnd();

    // Atualiza o ângulo do quadrado para fazer o movimento circular
    circle_angle += circle_speed;

    // Atualiza o ângulo de rotação do quadrado
    square_rotation_angle += square_rotation_speed;

    // Atualiza o pulso do quadrado
    if (square_pulse_increasing) {
        square_pulse_scale += square_pulse_step;
        if (square_pulse_scale >= square_pulse_max_scale)
            square_pulse_increasing = false;
    } else {
        square_pulse_scale -= square_pulse_step;
        if (square_pulse_scale <= square_pulse_min_scale)
            square_pulse_increasing = true;
    }

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
