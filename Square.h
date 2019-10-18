#pragma once
#include "Shapes.h"

// ------- CLASE HIJA / CUADRADO -----------------------------
class Square : public Shapes {

	// ----- ATRIBUTOS PERTENECIENTES A CUADRADO -------------
private:
	float side;
	Vertex vertices[4];

public:
	Square() {
		setOrigin(0, 0);
		setColor(1.0, 1.0, 1.0);
		setLineWidth(1);
		setSide(5);
		setNoVertices(4);
		calculateVertex();
	}

	Square(float x, float y) {
		setOrigin(x, y);
		setColor(1.0, 1.0, 1.0);
		setLineWidth(1);
		setSide(5);
		setNoVertices(4);
		calculateVertex();
	}

	Square(float x, float y, float s) {
		setOrigin(x, y);
		setColor(1.0, 1.0, 1.0);
		setLineWidth(1);
		setSide(s);
		setNoVertices(4);
		calculateVertex();
	}

	Square(float x, float y, float s, float r, float g, float b) {
		setOrigin(x, y);
		setColor(r, g, b);
		setLineWidth(1);
		setSide(s);
		setNoVertices(4);
		calculateVertex();
	}

	Square(float x, float y, float s, float r, float g, float b, int lwidth) {
		setOrigin(x, y);
		setColor(r, g, b);
		setLineWidth(lwidth);
		setSide(s);
		setNoVertices(4);
		calculateVertex();
	}

	Square(const Square& square) {
		Vertex pos = square.getOrigin();
		setOrigin(pos.getX(), pos.getY());
		Color col = square.getColor();
		setColor(col.getR(), col.getG(), col.getB());
		setLineWidth(square.getLineWidth());
		setSide(square.getSide());
		setNoVertices(4);
		calculateVertex();
	};

	void setSide(float s) {
		if (s > 0) { side = s; }
		else { side = 5; }
		area = calculateArea();
		perimeter = calculatePerimeter();
	}

	float getSide() const { return side; }

	double calculateArea() { return (side * side); }
	double calculatePerimeter() { return (4 * side); }

	void calculateVertex() {
		Vertex aux_pos = getOrigin();
		float x1 = aux_pos.getX() - (getSide() / 2), y1 = aux_pos.getY() - (getSide() / 2);
		float x2 = aux_pos.getX() + (getSide() / 2), y2 = aux_pos.getY() + (getSide() / 2);
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
		setSide(factor * getSide());
		calculateVertex();
	}

	void rotateShape(float _x, float _y, double _theta) {
		for (int i = 0; i < NoVertices; i++)
		{
			vertices[i].rotateVertex(_x, _y, _theta);
		}
	}
};