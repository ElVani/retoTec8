/*
 * GRAFICACION - UNIDAD 2
 * RETO DE INTERACCION CON FIGURAS GEOMETRICAS
 * FUNCIONES DE EVENTOS DEL TECLADO
 * FUNCIONES DE EVENTOS DEL RATON
 * INTEGRANTES:
 * IVAN FRANCO DELGADO
 * JESUS EDUARDO SOSA DIAZ
 * JOSUE TORRES AVALOS
 */
#include <GL/glut.h> // IMPORTA LA LIBRERIA DE GLUT
#include "Vertex.h"
#include "Shapes.h"
#include "Circle.h"
#include "Rectangle.h"
#include "Square.h"
#include "Lines.h"
#include <string>
#include <list>
#include <iterator>

 // VALORES UTILIZADOS PARA EL TAMANO DE LA
 // PANTALLA DEFINIENDO ALTO Y ANCHO
#define HEIGHT 720
#define WIDTH 1280

// PROTOTIPOS DE FUNCIONES
void GoMenu(int value);
void initializer(void);
void clearShape(float);
void userInterface(void);
//void keyInput(unsigned char, int, int);
void specialKeyInput(int, int, int);
void mouseControl(int, int, int, int);
void showInstructions(void);

static long font = (long)GLUT_BITMAP_TIMES_ROMAN_10; // CONTIENE EL VALOR DEL TIPO DE FUENTE
bool used = false; // INDICA SI EL CANVAS HA SIDO UTILIZADO
bool active = false; // INDICA SI EXISTE UN COMANDO ACTIVO
bool fillPoints = false; // INDICA SI LOS DOS VERTICES A DIBUJAR HAN SIDO SELECCIONADOS
int draw = -1; // INDICA EL TIPO DE FIGURA QUE FUE SELECCIONADA
int clics = 0;
int resize = 0;
Vertex points[2]; // ALMACENA LOS DOS PUNTOS SELECCIONADOS POR EL USUARIO

// LISTAS DE OBJETOS A DIBUJAR
std::list<Lines> lines;
std::list<Rectangle> rectangles;
std::list<Square> squares;
std::list<Circle> circles;
std::string message = "Select a command"; // MENSAJE QUE SERA MOSTRADO SEGUN LA ACCION CORRESPONDIENTE
int position[5] = { 0, 0, 0, 0, 0 }; // AUXILIAR PARA LA SELECCION DE LOS ELEMENTOS DE LAS LISTAS

int main(int argc, char* argv[]) {
	glutInit(&argc, argv);

	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(WIDTH, HEIGHT); // ESTABLECE EL TAMANO DE LA VENTANA
	glutCreateWindow("PainTec");

	initializer(); // INICIALIZA LA VENTANA

	glutDisplayFunc(userInterface); // ACTUALIZA LA PANTALLA DE TRAZADO

	int sub1 = glutCreateMenu(GoMenu); // INICIALIZA UNA VARIABLE CREANDO UN MENU PARA QUE LAS OPCIONES DE LAS FIGURAS QUEDEN DENTRO DE UNA CATEGORIA

	glutAddMenuEntry("Line", 1); // CREA OPCION PARA DIBUJAR UNA LINEA
	glutAddMenuEntry("Rectangle", 2); // CREA OPCION PARA DIBUJAR UN RECTANGULO
	glutAddMenuEntry("Square", 3); // CREA OPCION PARA DIBUJAR UN CUADRADO
	glutAddMenuEntry("Circle", 4); // CREA OPCION PARA DIBUJAR UN CIRCULO

	glutCreateMenu(GoMenu); // CREA UN MENU UTILIZANDO LA FUNCION GO MENU

	glutAddMenuEntry("Instructions", 5); // CREA OPCION PARA MOSTRAR INSTRUCCIONES

	glutAddSubMenu("Shapes", sub1); // CREA UNA CATEGORIA QUE UTILIZA EL VALOR DE SUB1 COMO PARAMETRO PARA QUE DE ESTA OPCION SE DESPLIEGUEN LAS OPCIONES

	glutAddMenuEntry("Clear", 6); // CREA OPCION CLEAR QUE FUNCIONA PARA REESTABLECER LOS VALORES DE LA VENTANA

	glutAddMenuEntry("Exit", 7); // CREA OPCION EXIT PARA SALIR DEL PROGRAMA

	glutAttachMenu(GLUT_RIGHT_BUTTON); // SE ADJUNTA EL MENU AL BOTON DERECHO DEL MOUSE

	glutSpecialFunc(specialKeyInput); // CAPTURA LAS TECLAS ESPECIALES COMO LAS FLECHAS
	glutMouseFunc(mouseControl); // CAPTURA LOS CLICS

	glutMainLoop(); // GENERA EL LOOP

	return 0;
}

/*
 * FUNCION QUE TOMA EL VALOR DE LA FUENTE Y UNA CADENA COMO PARAMETRO
 * RECORRE LA CADENA CARACTER POR CARACTER HASTA QUE LLEGA AL PUNTO FINAL
 * IMPRIME EL CARACTER UTILIZANDO EL FONT
 */
void writeBitmapString(void* font, const char* string)
{
	const char* c;
	for (c = string; *c != '\0'; c++) glutBitmapCharacter(font, *c);
}
/*
* FUNCION PARA MOSTRAR LAS INSTRUCCIONES
*/
void showInstructions(void) {
	glRasterPos2f(10, 650);
	writeBitmapString((void*)font, "To draw a shape put two points with mouse left button");
	glRasterPos2f(10, 620);
	writeBitmapString((void*)font, "Line: point of beginning and point of end");
	glRasterPos2f(10, 590);
	writeBitmapString((void*)font, "Rectangle: Corner up/left and corner down/right");
	glRasterPos2f(10, 560);
	writeBitmapString((void*)font, "Square and Circle: Center and side");
	glRasterPos2f(10, 530);
	writeBitmapString((void*)font, "To resize shapes select one shape and press UP or DOWN to resize, to change of shape press LEFT or RIGHT");
	glFlush();
}
/*
* FUNCION PARA BORRAR LAS INSTRUCCIONES
*/
void clearInstructions() {
	glColor3f(1.0, 1.0, 1.0);
	glutDisplayFunc(showInstructions);
}
/*
* FUNCION QUE DETERMINA LAS ACCIONES DEL MENU ADJUNTO AL CLICK DERECHO DEL RATON
*/

void GoMenu(int value) {
	switch (value) {
	case 1: // COMANDO CORRESPONDIENTE A LA LINEA
		message = "Command active: Line";
		active = true;
		draw = 1;
		break;
	case 2: // COMANDO CORRESPONDIENTE AL RECTANGULO
		message = "Command active: Rectangle";
		active = true;
		draw = 2;
		break;
	case 3: // COMANDO CORRESPONDIENTE AL CUADRADO
		message = "Command active: Square";
		active = true;
		draw = 3;
		break;
		message = "Command active: Circle";
	case 4: // COMANDO CORRESPONDIENTE AL CIRCULO
		active = true;
		draw = 4;
		break;
	case 5: // SHOW THE INSTRUCTIONS
		glColor3f(0.0, 0.0, 0.0);
		glutDisplayFunc(showInstructions);
		glutPostRedisplay();
		break;
	case 6: // REESTABLECE LOS VALORES A SU VALOR INICIAL
		   // VACIA LAS LISTAS DE LAS FIGURAS
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
		clearInstructions();
		glutPostRedisplay();
		break;
		
	case 7:
		exit(0); // SALE INMEDIATAMENTE DEL PROGRAMA
		break;
	}
	glutPostRedisplay();
}

/*
 * FUNCION QUE CAPTURA LA TECLA ESPECIAL DEL TECLADO
 * Y ENTRA EN UNA SECUENCIA DE IF'S QUE DEPENDE
 * DE LA DIRECCION DE LA FLECHA PRESIONADA
 */
void specialKeyInput(int key, int x, int y)
{
	// DEBE ESTAR ACTIVO UN COMANDO Y DEPENDIENDO DEL MISMO
	// PERMITE ASIGNAR UN NUMERO DE POSICION PARA SER MODIFICADO
	if (draw > 0)
	{
		if (key == GLUT_KEY_LEFT) // TECLA IZQUIERDA
		{
			// NO PERMITE ASIGNAR UN NUMERO MENOR AL 0
			if (position[draw] - 1 >= 0)
			{
				position[draw]--;
			}
			return;
		}
		if (key == GLUT_KEY_RIGHT) // TECLA DERECHA
		{
			// ENTRA EN UN SWITCH QUE DEPENDIENDO DEL VALOR DE DRAW PERMITE
			// AUMENTAR EL VALOR DE LA POSICION EVITANDO QUE SEA ASIGNADO
			// UN NUMERO MAYOR AL DE LOS ELEMENTOS DE LA LISTA
			switch (draw)
			{
			case 1: {
				if (position[draw] + 1 < (int)lines.size())
				{
					position[draw]++;
				}
				break;
			}
			case 2: {
				if (position[draw] + 1 < (int)rectangles.size())
				{
					position[draw]++;
				}
				break;
			}
			case 3: {
				if (position[draw] + 1 < (int)squares.size())
				{
					position[draw]++;
				}
				break;
			}
			case 4: {
				if (position[draw] + 1 < (int)circles.size())
				{
					position[draw]++;
				}
				break;
			}
			}
			return;
		}
	}
	if (key == GLUT_KEY_UP) // TECLA ARRIBA
	{
		resize = 1; // VALOR 1 SIGNIFICA INCREMENTO		
	}
	if (key == GLUT_KEY_DOWN) // TECLA ABAJO
	{
		resize = 2; // VALOR 2 SIGNIFICA DECREMENTO
	}
	glutPostRedisplay(); // MANDA ACTUALIZAR LA PANTALLA
}

/*
 * FUNCION QUE CAPTURA LOS CLIC DEL RATON
 * DEPENDIENDO DEL BOTON PRESIONADO
 */
void mouseControl(int button, int state, int x, int y)
{
	// BOTON IZQUIERDO PRESIONADO, COMANDO ACTIVO Y SIN HABER SELECCIONADO LOS VERTICES DE LA FIGURA
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN && active == true && fillPoints == false)
	{
		points[clics].setX(x); // UTILIZA EL CONTADOR GLOBAL CLICS PARA ASIGNAR 
		points[clics].setY(y); // COORDENADA X E Y EN EL ARREGLO DE PUNTOS
		if (clics < 2)
		{
			clics++; // AUMENTA EL VALOR DE LA VARIABLE
		}

		// EL MAXIMO VALOR ES DOS, UNA VEZ ALCANZADO ESTE VALOR
		// ACTUALIZA LA PANTALLA PARA DIBUJAR LA FIGURA 
		if (clics >= 2)
		{
			fillPoints = true;
			used = true;
			message = "Select a command";
			glutPostRedisplay();
		}
	}
}

/*
 * INICIALIZA LA PANTALLA
 * ASIGNA EL COLOR BLANCO AL CANVAS
 * ESTABLECE EL TAMANO DE LA MANTA QUE CORRESPONDA AL TAMANO DE LA PANTALLA
 */
void initializer(void) {
	glClearColor(1.0, 1.0, 1.0, 0.0); // COLOR CANVAS
	glMatrixMode(GL_PROJECTION);
	gluOrtho2D(0.0, WIDTH, 0.0, HEIGHT); // TAMANO DE MANTA
}

/*
 * FUNCION DISENADA PARA AUMENTAR O REDUCIR EL TAMANO DE UNA FIGURA
 * GEOMETRICA, TOMA COMO PARAMETRO EL VALOR A REDUCIR O AUMENTAR
 * TOMA EL VALOR CORRESPONDIENTE A LA FIGURA A DIBUJAR
 * ENTRA EN UN SWITCH QUE PERMITE ACCEDER A LA LISTA DE OBJETOS
 */
void clearShape(float distance) {
	switch (draw)
	{
	case 1: {

		break;
	}
			/*
			 * SI LA LISTA DE OBJETOS TIENE AL MENOS UN ELEMENTO, ITERA SOBRE LA LISTA
			 * HASTA LLEGAR AL OBJETO EN EL INDICE DE LA VARIABLE POSICION (AUMENTADA /
			 * REDUCIDA CON TECLA IZQ/DER) MEDIANTE UN APUNTADOR PERMITE ACCEDER A LOS
			 * SETS Y GETS DEL OBJETO ESTABLECIENDO LOS NUEVOS VALORES ACTUALIZANDO SUS
			 * VERTICES Y PINTANDO DE NUEVO LA PANTALLA PARA REFLEJAR CAMBIOS
			 */
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

/*
 * INTERFAZ DE USUARIO O PANTALLA DONDE ES PINTADO TODO
 * CADA VEZ QUE ES LLAMADA, SE LIMPIA LA PANTALLA
 */
void userInterface(void)
{
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(0.0, 0.0, 0.0);
	glRasterPos2f(570, 680);
	writeBitmapString((void*)font, "Press mouse right button to show options");
	// SI YA EXISTIA ALGO DIBUJADO, ITERA SOBRE CADA LISTA
	// PARA VOLVER A PINTARLO MANTENIENDO ACTUALIZADO EL DIBUJO
	if (used)
	{
		if (rectangles.empty() == false)
		{
			for (Rectangle& rec : rectangles) {
				rec.drawShapeFill();
			}
		}
		if (squares.empty() == false)
		{
			for (Square& sq : squares) {
				sq.drawShapeFill();
			}
		}
		if (circles.empty() == false)
		{
			for (Circle& cir : circles) {
				cir.drawShapeTrig();
			}
		}
		if (lines.empty() == false)
		{
			for (Lines& li : lines) {
				li.drawLine();
			}
		}
	}

	// SI EXISTE UN COMANDO ACTIVO Y LOS DOS VERTICES HAN SIDO CAPTURADOS 
	// ENTONCES ENTRA EN UN SWITCH
	// CALCULA LOS PUNTOS INICIAL Y FINAL MEDIANTE EL ARREGLO DE VERTICES
	// CREA UN OBJETO DEL TIPO QUE LE CORRESPONDE Y LO AGREGA A LA LISTA
	if (active && fillPoints)
	{
		switch (draw)
		{
		case 1: // DIBUJA UNA LINEA
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
		case 2: // DIBUJA UN RECTANGULO
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
		case 3: // DIBUJA UN CUADRADO
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
		case 4: // DIBUJA UN CIRCULO
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

	// EN CASO DE TENER QUE AUMENTAR O REDUCIR EL TAMANO DE UNA FIGURA
	// ENTRA EN ESTA SECCION Y MANDA LLAMAR EL METODO PARA TRANSFORMARLA
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
