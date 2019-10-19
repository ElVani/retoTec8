#pragma once
#include "Vertex.h"

class Lines {
private:
	Vertex pointInitial;
	Vertex pointFinal;
	Color color;
public:
	Lines(Vertex a, Vertex b, float r, float g, float bl) {
		pointInitial = a;
		pointFinal = b;
		setColor(r, g, bl);
	}

	Vertex getPointInitial() {
		return pointInitial;
	}

	Vertex getPointFinal() {
		return pointFinal;
	}

	Color getColor() const { return color; }

	void setPointInitial(Vertex a) {
		pointInitial = a;
	}

	void setPointFinal(Vertex b) {
		pointInitial = b;
	}

	void setColor(float r, float g, float b) {
		color.setR(r);
		color.setG(g);
		color.setB(b);
	}

	void drawLine() {
		Color aux_color = getColor();
		glColor3f(aux_color.getR(), aux_color.getG(), aux_color.getB());
		glBegin(GL_LINES);
		glVertex2f(pointInitial.getX(),pointInitial.getY()); // coordenadas de las lineas
		glVertex2f(pointFinal.getX(), pointFinal.getY());
		glEnd();
		glFlush(); // hace que se muestre en la pantalla
	}
};