#ifndef SHAPES_H
#define SHAPES_H
#pragma once
#include <cmath>
#include <GL/glut.h>
#include "Vertex.h"
#include "Color.h"

// ------- CLASE PRINCIPAL ----------------------------------
class Shapes
{
	// ----- ATRIBUTOS DE LAS FIGURAS -----------------------
protected:
	Vertex origin;
	Color color;
	int NoVertices;
	int lineWidth;
	double area;
	double perimeter;

	// ----- GETTERS & SETTERS -------------------------------
	// ALGUNAS SON VIRTUALES DEBIDO A QUE SERAN IMPLEMENTADAS
	// EN LA CLASE HIJA --------------------------------------
public:

	void setOrigin(float _x, float _y) {
		origin.setX(_x);
		origin.setY(_y);
	}

	void setColor(float r, float g, float b) {
		color.setR(r);
		color.setG(g);
		color.setB(b);
	}

	void setLineWidth(int width) {
		if (width > 0) lineWidth = width;
		else lineWidth = 1;
	}

	void setNoVertices(int _NoVertices) {
		NoVertices = _NoVertices;
	}

	int getNoVertices() {
		return NoVertices;
	}

	Vertex getOrigin() const { return origin; }
	Color getColor() const { return color; }
	int getLineWidth() const { return lineWidth; }
	double getArea() const { return area; }
	double getPerimeter() const { return perimeter; }

	// --- METODOS DE LAS FIGURAS ------------------------
	virtual double calculateArea() = 0;
	virtual double calculatePerimeter() = 0;
	virtual void drawShape() = 0;
};
#endif // !SHAPES_H