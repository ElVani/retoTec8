#include <GL/glut.h> // importa la libreria de glut
#include "Vertex.h"
#include "Shapes.h"
#include "Circle.h"
#include "Rectangle.h"
#include "Square.h"
#include <string>

#define HEIGHT 720
#define WIDTH 1280

void initializer(void);
void lineSegment(void);
void clearShape(int);
void userInterface(void);
void keyInput(unsigned char, int, int);
void specialKeyInput(int, int, int);
void mouseControl(int, int, int, int);

static long font = (long)GLUT_BITMAP_TIMES_ROMAN_10;
bool active = false;
bool fillPoints = false;
int draw = -1;
int clics = 0;
int resize = 0;
Vertex points[2];
Rectangle recGlobal;
Square sqGlobal;
Circle cirGlobal;
std::string message = "Select a command";
std::string message2;

int main(int argc, char *argv[]) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(WIDTH, HEIGHT); // Establece el tamao de la ventana
	glutCreateWindow("PainTec");
	initializer();
	glutDisplayFunc(userInterface);
	glutKeyboardFunc(keyInput);
	glutSpecialFunc(specialKeyInput);
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
		message2 = message;
		message = "Command active: Line";
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

void specialKeyInput(int key, int x, int y)
{
	if (key == GLUT_KEY_UP)
	{
		resize = 1;
	}
	if (key == GLUT_KEY_DOWN)
	{
		resize = 2;
	}
	glutPostRedisplay();
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
	gluOrtho2D(0.0, WIDTH, 0.0, HEIGHT); // especificamos que la imagen ser en 2D
}

void lineSegment(void) {
	glColor3f(1.0, 0.0, 0.0); // el color rgb de la linea a dibujar
	glBegin(GL_LINES);
	glVertex2f(points[0].getX(), HEIGHT - points[0].getY()); // coordenadas de las lineas
	glVertex2f(points[1].getX(), HEIGHT - points[1].getY());
	glEnd();
	glFlush(); // hace que se muestre en la pantalla
}

void clearShape(int distance) {
	switch (draw)
	{
	case 1: {

		break;
	}
	case 2: {
		Rectangle rec = recGlobal;
		rec.setColor(1.0, 1.0, 1.0);
		rec.drawShapeFill();
		recGlobal.setBase(recGlobal.getBase() + distance);
		recGlobal.setHeight(recGlobal.getHeight() + distance);
		recGlobal.calculateVertex();
		recGlobal.drawShapeFill();
		break;
	}
	case 3: {
		Square sq = sqGlobal;
		sq.setColor(1.0, 1.0, 1.0);
		sq.drawShapeFill();
		sqGlobal.setSide(sqGlobal.getSide() + distance);
		sqGlobal.calculateVertex();
		sqGlobal.drawShapeFill();
		break;
	}
	case 4: {

		break;
	}
	default:
		break;
	}
	
}

void menuOptions(void) {
	glColor3f(0.0, 0.0, 0.0);
	glRasterPos2f(10, 680);
	writeBitmapString((void*)font, "Press L to Draw a Line!");

	glColor3f(0.0, 0.0, 0.0);
	glRasterPos2f(10, 650);
	writeBitmapString((void*)font, "Press R to Draw a Rectangle!");

	glColor3f(0.0, 0.0, 0.0);
	glRasterPos2f(10, 620);
	writeBitmapString((void*)font, "Press S to Draw a Square!");

	glColor3f(0.0, 0.0, 0.0);
	glRasterPos2f(10, 590);
	writeBitmapString((void*)font, "Press C to Draw a Circle!");

	glColor3f(0.0, 0.0, 0.0);
	glRasterPos2f(10, 560);
	writeBitmapString((void*)font, "Press D to Default");

	glColor3f(1.0, 1.0, 1.0);
	glRasterPos2f(0, 20);
	writeBitmapString((void*)font, message.c_str());

	glColor3f(0.0, 0.0, 0.0);
	glRasterPos2f(0, 20);
	writeBitmapString((void*)font, message2.c_str());
}

void userInterface(void)
{
	if (draw <= 0)
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
			message = "Select a command";
			active = false;
			fillPoints = false;
			clics = 0;
			break;
		case 2:
		{	
			
			float x0 = points[0].getX(), x1 = points[1].getX();
			float y0 = HEIGHT - points[0].getY(), y1 = HEIGHT - points[1].getY();
			float base = x1 - x0;
			float height = y1 - y0;
			
			float xOrigin = x0 + (base / 2);
			float yOrigin = y0 + (height / 2);
			Rectangle rec(xOrigin, yOrigin, base, height, 0.0, 1.0, 0.0);
			recGlobal = rec;
			rec.drawShapeFill();

			active = false;
			fillPoints = false;
			clics = 0;
			break;
		}
		case 3:
		{
			float x0 = points[0].getX(), x1 = points[1].getX();
			float y0 = HEIGHT - points[0].getY(), y1 = HEIGHT - points[1].getY();
			float side = (x1 - x0) * 2;
			if (side < 0)
			{
				side *= -1;
			}
			float xOrigin = x0;
			float yOrigin = y0;
			Square sq(xOrigin, yOrigin, side, 0.0, 1.0, 0.0);
			sqGlobal = sq;
			sq.drawShapeFill();

			active = false;
			fillPoints = false;
			clics = 0;

			break;
		}
		case 4:
		{
			float x0 = points[0].getX(), x1 = points[1].getX();
			float y0 = HEIGHT - points[0].getY(), y1 = HEIGHT - points[1].getY();
			float radius = x1 - x0;
			if (radius < 0)
			{
				radius *= -1;
			}
			float xOrigin = x0;
			float yOrigin = y0;
			Circle cir(xOrigin, yOrigin, radius, 0.0, 1.0, 0.0);
			cirGlobal = cir;
			cir.drawShapeTrig();
			active = false;
			fillPoints = false;
			clics = 0;

			break;
		}
		}
	}
	else
	{
		if (resize == 1)
		{
			clearShape(10);
			resize = 0;
		}
		if (resize == 2)
		{
			clearShape(-10);
			resize = 0;
		}
	}
	glutSwapBuffers();
	glFlush();
}