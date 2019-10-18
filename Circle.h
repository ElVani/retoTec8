#pragma once
#include "Shapes.h"

class Circle : public Shapes {
private:
	float radius;
	float diameter;
	const double PI = 3.141592;

public:
	Circle() {
		setOrigin(0, 0);
		setColor(1.0, 1.0, 1.0);
		setLineWidth(1);
		setRadius(25);

	}

	Circle(float x, float y) {
		setOrigin(x, y);
		setColor(1.0, 1.0, 1.0);
		setLineWidth(1);
		setRadius(25);
	}

	Circle(float x, float y, float rad) {
		setOrigin(x, y);
		setColor(1.0, 1.0, 1.0);
		setLineWidth(1);
		setRadius(rad);
	}

	Circle(float x, float y, float rad, float r, float g, float b) {
		setOrigin(x, y);
		setColor(r, g, b);
		setLineWidth(1);
		setRadius(rad);
	}

	Circle(float x, float y, float rad, float r, float g, float b, int lwidth) {
		setOrigin(x, y);
		setColor(r, g, b);
		setLineWidth(lwidth);
		setRadius(rad);
	}

	Circle(const Circle& circle) {
		Vertex pos = circle.getOrigin();
		setOrigin(pos.getX(), pos.getY());
		Color col = circle.getColor();
		setColor(col.getR(), col.getG(), col.getB());
		setLineWidth(circle.getLineWidth());
		setRadius(circle.getRadius());
	};

	void setRadius(float rad) {
		if (rad > 0) { radius = rad; }
		else { radius = 50; }
		diameter = getRadius() * 2;
		area = calculateArea();
		perimeter = calculatePerimeter();
	}

	float getRadius() const { return radius; }
	float getDiameter() const { return diameter; }

	double calculateArea() { return (PI * (pow(radius, 2))); }
	double calculatePerimeter() { return (2 * PI * radius); }

	void drawShape() {
		Color aux_color = getColor();
		glColor3f(aux_color.getR(), aux_color.getG(), aux_color.getB());
		Vertex aux_pos;
		aux_pos.setX(0);
		aux_pos.setY(getRadius());
		glPointSize(getLineWidth());
		float midpoint = 1 - radius;
		circlePlotPoints(origin.getX(), origin.getY(), aux_pos);
		while (aux_pos.getX() < aux_pos.getY())
		{
			aux_pos.setX(aux_pos.getX() + 1);
			if (midpoint < 0)
			{
				midpoint += 2 * aux_pos.getX() + 1;
			}
			else
			{
				//int newY = aux_pos.getY() - 1;
				aux_pos.setY(aux_pos.getY() - 1);
				midpoint += 2 * (aux_pos.getX() - aux_pos.getY()) + 1;
			}
			circlePlotPoints(origin.getX(), origin.getY(), aux_pos);
		}
	}

	void circlePlotPoints(int x, int y, Vertex aux_pos) {
		glBegin(GL_POINTS);
		glVertex2i(x + aux_pos.getX(), y + aux_pos.getY());
		glVertex2i(x - aux_pos.getX(), y + aux_pos.getY());
		glVertex2i(x + aux_pos.getX(), y - aux_pos.getY());
		glVertex2i(x - aux_pos.getX(), y - aux_pos.getY());

		glVertex2i(x + aux_pos.getY(), y + aux_pos.getX());
		glVertex2i(x - aux_pos.getY(), y + aux_pos.getX());
		glVertex2i(x + aux_pos.getY(), y - aux_pos.getX());
		glVertex2i(x - aux_pos.getY(), y - aux_pos.getX());

		glEnd();
	}

	void drawShapeTrig() {
		Color aux_color = getColor();
		glColor3f(aux_color.getR(), aux_color.getG(), aux_color.getB());
		Vertex aux_pos = getOrigin();
		glLineWidth(getLineWidth());
		int circle_points = 360;
		glBegin(GL_LINE_LOOP);
		for (int i = 0; i < circle_points; i++)
		{
			float angle = 2 * PI * float(i) / circle_points;
			glVertex2f(aux_pos.getX() + getRadius() * cos(angle), aux_pos.getY() + getRadius() * sin(angle));
		}
		glEnd();
	}

	void moveShape(float _x, float _y) {
		origin.moveVertex(_x, _y);
	}

	void scaleShape(float factor) {
		setRadius(factor * getRadius());
	}
	/*
	void rotateShape(float _x, float _y, double _theta) {
		
	}*/
};
