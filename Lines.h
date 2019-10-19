/* 
 * GRAFICACION
 * INTEGRANTES: 
 * IVAN FRANCO DELGADO
 * JESUS EDUARDO SOSA DIAZ
 * JOSUE TORRES AVALOS
 */
#pragma once
#include "Vertex.h"

/*
 * CLASE QUE PERMITE CREAR UN OBJETO DE
 * TIPO LINEA QUE ALMACENA SU PUNTO INICIAL
 * PUNTO FINAL Y COLOR DE LINEA
 */
class Lines {
	
	// ATRIBUTOS
private:
	Vertex pointInitial;
	Vertex pointFinal;
	Color color;
	
	// CONSTRUCTOR Y METODOS
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

	// METODO PARA DIBUJAR LINEA
	void drawLine() {
		Color aux_color = getColor();
		glColor3f(aux_color.getR(), aux_color.getG(), aux_color.getB());
		glBegin(GL_LINES);
		glVertex2f(pointInitial.getX(),pointInitial.getY()); // COORDENADAS DE LA LINEA
		glVertex2f(pointFinal.getX(), pointFinal.getY());
		glEnd();
		glFlush(); // HACE QUE SE MUESTRE EN LA PANTALLA
	}
};
