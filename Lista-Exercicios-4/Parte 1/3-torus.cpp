#include <math.h>
#include <iostream>
#include <GL/glut.h>

#define PI 3.14159265358979324
#define MAJOR_RADIUS 10.0
#define MINOR_RADIUS 3.0

using namespace std;

// Globais.
static int gridColumns = 6; // Número de colunas da grade.
static int gridRows = 4; // Número de linhas da grade.
static float *vertices = NULL; // Array de vértices do toro.
static float Xangle = 150.0, Yangle = 0.0, Zangle = 0.0; // Ângulos para rotacionar o toro.

// Funções para mapear o vértice da grade (u_i, v_j) para o vértice da malha (f(u_i,v_j), g(u_i,v_j), h(u_i,v_j)) no toro.
float f(int i, int j)
{
   return ( ( MAJOR_RADIUS + MINOR_RADIUS * cos( (-1 + 2*(float)j/gridRows) * PI ) ) * cos( (-1 + 2*(float)i/gridColumns) * PI ) );
}

float g(int i, int j)
{
   return ( ( MAJOR_RADIUS + MINOR_RADIUS * cos( (-1 + 2*(float)j/gridRows) * PI ) ) * sin( (-1 + 2*(float)i/gridColumns) * PI ) );
}

float h(int i, int j)
{
   return ( MINOR_RADIUS * sin( (-1 + 2*(float)j/gridRows) * PI ) );
}

// Função para preencher o array de vértices com as coordenadas dos pontos mapeados.
void fillVertexArray(void)
{
   int i, j, k;

   k = 0;
   for (j = 0; j <= gridRows; j++)
      for (i = 0; i <= gridColumns; i++)
      {
         vertices[k++] = f(i,j);
         vertices[k++] = g(i,j);
         vertices[k++] = h(i,j);
      }
}

// Função de inicialização.
void setup(void)
{
   glEnableClientState(GL_VERTEX_ARRAY);

   glClearColor(1.0, 1.0, 1.0, 0.0);
}

// Função de desenho.
void drawScene(void)
{
   int  i, j;
   vertices = new float[3*(gridColumns+1)*(gridRows+1)]; // Alocação dinâmica do array com o novo valor de gridColumns e gridRows.

   glVertexPointer(3, GL_FLOAT, 0, vertices);
   glClear(GL_COLOR_BUFFER_BIT);

   glLoadIdentity();
   gluLookAt (0.0, 0.0, 30.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);

   glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

   glColor3f(0.0, 0.0, 0.0);

   // Rotacionar a cena.
   glRotatef(Zangle, 0.0, 0.0, 1.0);
   glRotatef(Yangle, 0.0, 1.0, 0.0);
   glRotatef(Xangle, 1.0, 0.0, 0.0);

   // Preencher o array de vértices.
   fillVertexArray();

   // Criar a malha triangular aproximada.
   for(j = 0; j < gridRows; j++)
   {
      glBegin(GL_TRIANGLE_STRIP);
      for(i = 0; i <= gridColumns; i++)
      {
         glArrayElement( (j+1)*(gridColumns+1) + i );
         glArrayElement( j*(gridColumns+1) + i );
	  }
      glEnd();
   }

   glutSwapBuffers();
}

// Função de redimensionamento da janela OpenGL.
void resize(int w, int h)
{
   glViewport(0, 0, (GLsizei)w, (GLsizei)h);
   glMatrixMode(GL_PROJECTION);
   glLoadIdentity();
   gluPerspective(60.0, (float)w/(float)h, 1.0, 50.0);
   glMatrixMode(GL_MODELVIEW);

}

// Função de entrada do teclado.
void keyInput(unsigned char key, int x, int y)
{
   switch(key) 
   {
      case 27:
         exit(0);
         break;
      case 'x':
         Xangle += 5.0;
		 if (Xangle > 360.0) Xangle -= 360.0;
         glutPostRedisplay();
         break;
      case 'X':
         Xangle -= 5.0;
		 if (Xangle < 0.0) Xangle += 360.0;
         glutPostRedisplay();
         break;
      case 'y':
         Yangle += 5.0;
		 if (Yangle > 360.0) Yangle -= 360.0;
         glutPostRedisplay();
         break;
      case 'Y':
         Yangle -= 5.0;
		 if (Yangle < 0.0) Yangle += 360.0;
         glutPostRedisplay();
         break;
      case 'z':
         Zangle += 5.0;
		 if (Zangle > 360.0) Zangle -= 360.0;
         glutPostRedisplay();
         break;
      case 'Z':
         Zangle -= 5.0;
		 if (Zangle < 0.0) Zangle += 360.0;
         glutPostRedisplay();
         break;
      default:
         break;
   }
}

// Função de entrada de tecla especial.
void specialKeyInput(int key, int x, int y)
{
   if (key == GLUT_KEY_LEFT) if (gridColumns > 3) gridColumns -= 1;
   if (key == GLUT_KEY_RIGHT) gridColumns += 1;
   if (key == GLUT_KEY_DOWN) if (gridRows > 3) gridRows -= 1;
   if (key == GLUT_KEY_UP) gridRows += 1;

   glutPostRedisplay();
}

// Função para exibir as instruções de interação na janela do programa.
void printInteraction(void)
{
   cout << "Interaction:" << endl;
   cout << "Press left/right arrow keys to increase/decrease the number of grid columns." << endl
        << "Press up/down arrow keys to increase/decrease the number of grid rows." << endl
        << "Press x, X, y, Y, z, Z to turn the torus." << endl;
}

// Função principal.
int main(int argc, char **argv) 
{
   printInteraction();
   glutInit(&argc, argv);
   glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
   glutInitWindowSize(500, 500);
   glutInitWindowPosition(100, 100);
   glutCreateWindow("Torus");
   setup();
   glutDisplayFunc(drawScene);
   glutReshapeFunc(resize);
   glutKeyboardFunc(keyInput);
   glutSpecialFunc(specialKeyInput);
   glutMainLoop();

   return 0;
}
