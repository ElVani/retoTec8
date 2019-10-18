#pragma once
#include "Shapes.h"

// ------- CLASE HIJA / RECTANGULO ---------------------------
class Rectangle : public Shapes {

	// ----- ATRIBUTOS PERTENECIENTES A RECTANGULO -----------
private:
	float base;
	float height;
	Vertex vertices[4];

public:
	// ------- CONSTRUCTORES SOBRECARGADOS -----------------------
	// DE CREARSE EL OBJETO VACIO, AUTOMATICAMENTE SON ASIGNADOS
	// LOS VALORES FALTANTES, DEL MISMO MODO CON LOS OTROS 
	// CONSTRUCTORES QUE NO SE ENVIAN LOS PARAMETROS COMPLETOS ---
	Rectangle() {
		setOrigin(0, 0);
		setColor(1.0, 1.0, 1.0);
		setLineWidth(1);
		setBase(50);
		setHeight(25);
		setNoVertices(4);
		calculateVertex();
	}

	Rectangle(float x, float y) {
		setOrigin(x, y);
		setColor(1.0, 1.0, 1.0);
		setLineWidth(1);
		setBase(50);
		setHeight(25);
		setNoVertices(4);
		calculateVertex();
	}

	Rectangle(float x, float y, float ba, float h) {
		setOrigin(x, y);
		setColor(1.0, 1.0, 1.0);
		setLineWidth(1);
		setBase(ba);
		setHeight(h);
		setNoVertices(4);
		calculateVertex();
	}

	Rectangle(float x, float y, float ba, float h, float r, float g, float b) {
		setOrigin(x, y);
		setColor(r, g, b);
		setLineWidth(1);
		setBase(ba);
		setHeight(h);
		setNoVertices(4);
		calculateVertex();
	}

	Rectangle(float x, float y, float ba, float h, float r, float g, float b, int lwidth) {
		setOrigin(x, y);
		setColor(r, g, b);
		setLineWidth(lwidth);
		setBase(ba);
		setHeight(h);
		setNoVertices(4);
		calculateVertex();
	}

	Rectangle(const Rectangle& rectangle) {
		Vertex pos = rectangle.getOrigin();
		setOrigin(pos.getX(), pos.getY());
		Color col = rectangle.getColor();
		setColor(col.getR(), col.getG(), col.getB());
		setLineWidth(rectangle.getLineWidth());
		setBase(rectangle.getBase());
		setHeight(rectangle.getHeight());
		setNoVertices(4);
		calculateVertex();
	};

	// ------- METODOS IMPLEMENTADOS DE LOS SETTERS --------------
	// SI ALGUNOS VALORES IMPORTANTES QUE PUDIESEN AFECTAR EL
	// FUNCIONAMIENTO DEL SET NO CONOCEN LOS REQUISITOS
	// NECESARIOS, SON ASIGNADOS VALORES PREDEFINIDOS ------------
	void setBase(float b) {
		if (b > 0) { base = b; }
		else { base = 50; }
		area = calculateArea();
		perimeter = calculatePerimeter();
	}

	void setHeight(float h) {
		if (h > 0) { height = h; }
		else { height = 25; }
		area = calculateArea();
		perimeter = calculatePerimeter();
	}

	float getBase() const { return base; }
	float getHeight() const { return height; }

	double calculateArea() { return (base * height); }
	double calculatePerimeter() { return (2 * (base + height)); }

	void calculateVertex() {
		Vertex aux_pos = getOrigin();
		float x1 = aux_pos.getX() - (getBase() / 2), y1 = aux_pos.getY() - (getHeight() / 2);
		float x2 = aux_pos.getX() + (getBase() / 2), y2 = aux_pos.getY() + (getHeight() / 2);
		setVertices(x1, y1, x2, y2);
	}

	void setVertices(float x1, float y1, float x2, float y2) {
		vertices[0].setX(x1), vertices[0].setY(y1); // vertice 1
		vertices[1].setX(x1), vertices[1].setY(y2); // vertice 2
		vertices[2].setX(x2), vertices[2].setY(y2); // vertice 3
		vertices[3].setX(x2), vertices[3].setY(y1); // vertice 4
	}

	void drawShape() {
		Color aux_color = getColor();
		glColor3f(aux_color.getR(), aux_color.getG(), aux_color.getB());
		glLineWidth(getLineWidth());
		glBegin(GL_LINE_LOOP);
		for (int i = 0; i < NoVertices; i++)
		{
			glVertex2i(vertices[i].getX(), vertices[i].getY());
		}
		glEnd();
	}

	void drawShapeFill() {
		Color aux_color = getColor();
		glColor3f(aux_color.getR(), aux_color.getG(), aux_color.getB());
		glLineWidth(getLineWidth());
		glBegin(GL_POLYGON);
		for (int i = 0; i < NoVertices; i++)
		{
			glVertex2i(vertices[i].getX(), vertices[i].getY());
		}
		glEnd();
	}

	void moveShape(float _x, float _y) {
		origin.moveVertex(_x, _y);
		calculateVertex();
	}

	void scaleShape(float factor) {
		setBase(factor * getBase());
		setHeight(factor * getHeight());
		calculateVertex();
	}
	
	void rotateShape(float _x, float _y, double _theta) {
		for (int i = 0; i < NoVertices; i++)
		{
			vertices[i].rotateVertex(_x, _y, _theta);
		}
	}
};