#include <GL/glut.h> // importa la libreria de glut
#include "Vertex.h"
#include "Shapes.h"
#include "Circle.h"
#include "Rectangle.h"
#include "Square.h"

#define HEIGHT 720
#define BORDER 200

void initializer(void);
void lineSegment(void);
void userInterface(void);
void keyInput(unsigned char, int, int);
void mouseControl(int, int, int, int);

static long font = (long)GLUT_BITMAP_TIMES_ROMAN_24;
bool active = false;
bool fillPoints = false;
int draw = -1;
int clics = 0;
Vertex points[2];
Rectangle recGlobal;

int main(int argc, char *argv[]) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(1280, 720); // Establece el tamao de la ventana
	glutCreateWindow("PainTec");
	initializer();
	glutDisplayFunc(userInterface);
	glutKeyboardFunc(keyInput);
	glutMouseFunc(mouseControl);

	glutMainLoop(); // genera un loop para que continue
	return 0;
}

void writeBitmapString(void *font, const char *string)
{
	const char *c;
	for (c = string; *c != '\0'; c++) glutBitmapCharacter(font, *c);
}

void keyInput(unsigned char key, int x, int y)
{
	switch (key)
	{
	case 27: // esc key
		exit(0);
	case 108: // l which stands for line
		active = true;
		draw = 1;
		break;
	case 114: // r which stands for rectangle
		active = true;
		draw = 2;
		break;
	case 115: // s which stands for square
		active = true;
		draw = 3;
		break;
	case 99: // c which stands for circle
		active = true;
		draw = 4;
		break;
	case 100: // d which stands for default
		active = false;
		fillPoints = false;
		draw = -1;
		clics = 0;
		glutPostRedisplay();
		break;
	default:
		break;
	}
}

void mouseControl(int button, int state, int x, int y)
{
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN && active == true && fillPoints == false)
	{
		points[clics].setX(x);
		points[clics].setY(y);
		if (clics < 2)
		{
			clics++;
		}
		if (clics >= 2)
		{
			fillPoints = true;
			glutPostRedisplay();
		}
	}
}

void initializer(void) {
	glClearColor(1.0, 1.0, 1.0, 0.0); // establece el color de la ventana
	glMatrixMode(GL_PROJECTION);
	gluOrtho2D(-200.0, 1080.0, 0.0, 720.0); // especificamos que la imagen ser en 2D
}

void lineSegment(void) {
	glColor3f(1.0, 0.0, 0.0); // el color rgb de la linea a dibujar
	glBegin(GL_LINES);
	glVertex2f(points[0].getX() - BORDER, HEIGHT - points[0].getY()); // coordenadas de las lineas
	glVertex2f(points[1].getX() - BORDER, HEIGHT - points[1].getY());
	glEnd();
	glFlush(); // hace que se muestre en la pantalla
}

void menuOptions(void) {
	glColor3f(0.0, 0.0, 0.0);
	glRasterPos2f(-180, 680);
	writeBitmapString((void*)font, "Press L to Draw a Line!");

	glColor3f(0.0, 0.0, 0.0);
	glRasterPos2f(-180, 650);
	writeBitmapString((void*)font, "Press R to Draw a Rectangle!");

	glColor3f(0.0, 0.0, 0.0);
	glRasterPos2f(-180, 620);
	writeBitmapString((void*)font, "Press S to Draw a Square!");

	glColor3f(0.0, 0.0, 0.0);
	glRasterPos2f(-180, 590);
	writeBitmapString((void*)font, "Press C to Draw a Circle!");

	glColor3f(0.0, 0.0, 0.0);
	glRasterPos2f(-180, 560);
	writeBitmapString((void*)font, "Press D to Default");
}

void userInterface(void)
{
	if (draw < 0)
	{
		glClear(GL_COLOR_BUFFER_BIT);
	}

	menuOptions();

	if (active && fillPoints)
	{
		switch (draw)
		{
		case 1:
			lineSegment();
			glColor3f(0.0, 0.0, 0.0);
			glRasterPos2f(-180, 460);
			writeBitmapString((void*)font, "Line!");
			active = false;
			fillPoints = false;
			clics = 0;
			break;
		case 2:
		{
			/*
			float x0 = ((points[0].getX() - BORDER) + (points[1].getX() - BORDER)) / 2;
			float y0 = (HEIGHT - points[0].getY()) + (HEIGHT - points[1].getY()) / 2;
			Rectangle rec(x0, y0, 100, 50);
			recGlobal = rec;
			rec.drawShapeFill();
			glColor3f(0.0, 0.0, 0.0);
			glRasterPos2f(-180, 460);
			writeBitmapString((void*)font, "Rectangle!");
			active = false;
			fillPoints = false;
			clics = 0;*/
			break;
		}
		case 3:
			break;
		}
	}


	glutSwapBuffers();
	glFlush();
}