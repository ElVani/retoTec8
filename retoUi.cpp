#include <GL/glut.h> // importa la libreria de glut
#include "Vertex.h"
#include "Shapes.h"
#include "Circle.h"
#include "Rectangle.h"
#include "Square.h"
#include "Lines.h"
#include <string>
#include <list>
#include <iterator>

#define HEIGHT 720
#define WIDTH 1280

void initializer(void);
void clearShape(float);
void userInterface(void);
void keyInput(unsigned char, int, int);
void specialKeyInput(int, int, int);
void mouseControl(int, int, int, int);

static long font = (long)GLUT_BITMAP_TIMES_ROMAN_10;
bool used = false;
bool active = false;
bool fillPoints = false;
int draw = -1;
int clics = 0;
int resize = 0;
Vertex points[2];
std::list<Lines> lines;
std::list<Rectangle> rectangles;
std::list<Square> squares;
std::list<Circle> circles;
//Rectangle recGlobal;
//Square sqGlobal;
//Circle cirGlobal;
std::string message = "Select a command";
int position[5] = { 0,0,0,0 ,0};

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
		message = "Command active: Line";
		active = true;
		draw = 1;
		glutPostRedisplay();
		break;
	case 114: // r which stands for rectangle
		message = "Command active: Rectangle";
		active = true;
		draw = 2;
		glutPostRedisplay();
		break;
	case 115: // s which stands for square
		message = "Command active: Square";
		active = true;
		draw = 3;
		glutPostRedisplay();
		break;
	case 99: // c which stands for circle
		message = "Command active: Circle";
		active = true;
		draw = 4;
		glutPostRedisplay();
		break;
	case 100: // d which stands for default
		message = "Select a command";
		active = false;
		fillPoints = false;
		draw = -1;
		clics = 0;
		used = false;
		for (size_t i = 0; i < 5; i++)
		{
			position[i] = 0;
		}
		rectangles.clear();
		squares.clear();
		circles.clear();
		lines.clear();
		glutPostRedisplay();
		break;
	default:
		break;
	}
}

void specialKeyInput(int key, int x, int y)
{
	if (draw > 0)
	{
		if (key == GLUT_KEY_LEFT)
		{
			if (position[draw] - 1 >= 0)
			{
				position[draw]--;
			}
			return;
		}
		if (key == GLUT_KEY_RIGHT)
		{
			switch (draw)
			{
			case 1: {
				if (position[draw] + 1 <= (int)lines.size())
				{
					position[draw]++;
				}
				break;
			}
			case 2: {
				if (position[draw] + 1 <= (int)rectangles.size())
				{
					position[draw]++;
				}
				break;
			}
			case 3: {
				if (position[draw] + 1 <= (int)squares.size())
				{
					position[draw]++;
				}
				break;
			}
			case 4: {
				if (position[draw] + 1 <= (int)circles.size())
				{
					position[draw]++;
				}
				break;
			}
			}
			return;
		}
	}
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
			used = true;
			message = "Select a command";
			glutPostRedisplay();
		}
	}
}

void initializer(void) {
	glClearColor(1.0, 1.0, 1.0, 0.0); // establece el color de la ventana
	glMatrixMode(GL_PROJECTION);
	gluOrtho2D(0.0, WIDTH, 0.0, HEIGHT); // especificamos que la imagen ser en 2D
}


void clearShape(float distance) {
	switch (draw)
	{
	case 1: {

		break;
	}
	case 2: {
		if (rectangles.empty() == false)
		{
			std::list<Rectangle>::iterator it = rectangles.begin();
			std::advance(it, position[draw]);
			(*it).setBase((*it).getBase() + distance);
			(*it).setHeight((*it).getHeight() + distance);
			(*it).calculateVertex();
			glutPostRedisplay();
		}
		break;
	}
	case 3: {
		if (squares.empty() == false)
		{
			std::list<Square>::iterator it = squares.begin();
			std::advance(it, position[draw]);
			(*it).setSide((*it).getSide() + distance);
			(*it).calculateVertex();
			glutPostRedisplay();
		}
		break;
	}
	case 4: {
		if (circles.empty() == false)
		{
			std::list<Circle>::iterator it = circles.begin();
			std::advance(it, position[draw]);
			(*it).setRadius((*it).getRadius() + distance);
			glutPostRedisplay();
		}
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

	glRasterPos2f(10, 660);
	writeBitmapString((void*)font, "Press R to Draw a Rectangle!");

	glRasterPos2f(10, 640);
	writeBitmapString((void*)font, "Press S to Draw a Square!");

	glRasterPos2f(10, 620);
	writeBitmapString((void*)font, "Press C to Draw a Circle!");

	glRasterPos2f(10, 600);
	writeBitmapString((void*)font, "Press D to Default the Screen");

	glRasterPos2f(500, 20);
	writeBitmapString((void*)font, message.c_str());
}

void userInterface(void)
{
	glClear(GL_COLOR_BUFFER_BIT);

	menuOptions();

	if (used)
	{
		if (rectangles.empty() == false)
		{
			for (Rectangle &rec : rectangles) {
				rec.drawShapeFill();
			}
		}
		if (squares.empty() == false)
		{
			for (Square &sq : squares) {
				sq.drawShapeFill();
			}
		}
		if (circles.empty() == false)
		{
			for (Circle &cir : circles) {
				cir.drawShapeTrig();
			}
		}
		if (lines.empty() == false)
		{
			for (Lines &li : lines) {
				li.drawLine();
			}
		}
	}
	if (active && fillPoints)
	{
		switch (draw)
		{
		case 1:
		{
			Vertex a(points[0].getX(), HEIGHT - points[0].getY()); // coordenadas de las lineas
			Vertex b(points[1].getX(), HEIGHT - points[1].getY());
			Lines line(a, b, 0.0, 0.0, 1.0);
			lines.push_back(line);
			line.drawLine();
			message = "Select a command";
			active = false;
			fillPoints = false;
			clics = 0;
			draw = 0;
			break;
		}
		case 2:
		{	
			float x0 = points[0].getX(), x1 = points[1].getX();
			float y0 = HEIGHT - points[0].getY(), y1 = HEIGHT - points[1].getY();
			float base = x1 - x0;
			float height = y1 - y0;
			float xOrigin = x0 + (base / 2);
			float yOrigin = y0 + (height / 2);
			Rectangle rec(xOrigin, yOrigin, base, height, 0.0, 1.0, 0.0);
			rectangles.push_back(rec);
			rec.drawShapeFill();
			active = false;
			fillPoints = false;
			clics = 0;
			draw = 0;
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
			squares.push_back(sq);
			sq.drawShapeFill();
			active = false;
			fillPoints = false;
			clics = 0;
			draw = 0;
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
			circles.push_back(cir);
			cir.drawShapeTrig();
			active = false;
			fillPoints = false;
			clics = 0;
			draw = 0;
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