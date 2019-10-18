#pragma once
#include <cmath>
const double PI = 3.14159265;

class Vertex {
private:
	float x;
	float y;

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

	// Transformaciones

	void moveVertex(float _x, float _y) {
		x = x + _x;
		y = y + _y;
	}

	void scaleVertex(float _x, float _y) {
		x = x * _x;
		y = y * _y;
	}

	void rotateVertex(float x_pivot, float y_pivot, float _theta) {
		float temp_x = x, temp_y = y;
		_theta = _theta * PI / 180;
		x = x_pivot + (temp_x - x_pivot) * cos(_theta)
			- (temp_y - y_pivot) * sin(_theta);
		y = y_pivot + (temp_x - x_pivot) * sin(_theta)
			+ (temp_y - y_pivot) * cos(_theta);
	}
};