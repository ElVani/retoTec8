/* 
 * GRAFICACION
 * INTEGRANTES: 
 * IVAN FRANCO DELGADO
 * JESUS EDUARDO SOSA DIAZ
 * JOSUE TORRES AVALOS
 */

#pragma once
#include <cmath>
const double PI = 3.14159265;

/* 
 * CLASE VERTEX QUE SIRVE PARA ALMACENAR LOS PUNTOS X E Y
 */
class Vertex {
	
	// ATRIBUTOS
private:
	float x;
	float y;

	// CONSTRUCTOR Y METODOS
public:
	
	Vertex() {
		x = 0;
		y = 0;
	}

	Vertex(float _x, float _y) {
		x = _x;
		y = _y;
	}

	float getX() {
		return x;
	}

	float getY() {
		return y;
	}

	void setX(float _x) {
		x = _x;
	}

	void setY(float _y) {
		y = _y;
	}

	// TRANSFORMACIONES

	// MOVER VERTICE, AGREGA LA CANTIDAD A TRASLADAR
	void moveVertex(float _x, float _y) {
		x = x + _x;
		y = y + _y;
	}

	// ESCALAR VERTICE, MULTIPLICA POR LA CANTIDAD A ESCALAR
	void scaleVertex(float _x, float _y) {
		x = x * _x;
		y = y * _y;
	}

	// ROTAR VERTICE, UTILIZA UN PUNTO PIVOTE Y MULTIPLICA EL X E Y POR
	// UNA TRANSFORMACION LINEAL
	void rotateVertex(float x_pivot, float y_pivot, float _theta) {
		float temp_x = x, temp_y = y;
		_theta = _theta * PI / 180;
		x = x_pivot + (temp_x - x_pivot) * cos(_theta)
			- (temp_y - y_pivot) * sin(_theta);
		y = y_pivot + (temp_x - x_pivot) * sin(_theta)
			+ (temp_y - y_pivot) * cos(_theta);
	}
};
