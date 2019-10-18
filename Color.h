#pragma once

class Color {
private:
	float colorR;
	float colorG;
	float colorB;

public:
	Color() {
		colorR = 1.0;
		colorG = 1.0;
		colorB = 1.0;
	}

	Color(float _r, float _g, float _b) {
		setR(_r);
		setG(_g);
		setB(_b);
	}

	float getR() {
		return colorR;
	}

	float getG() {
		return colorG;
	}

	float getB() {
		return colorB;
	}

	void setR(float _r) {
		if (_r >= 0 && _r <= 1) {
			colorR = _r;
		}
		else
		{
			colorR = 1.0;
		}
	}

	void setG(float _g) {
		if (_g >= 0 && _g <= 1) {
			colorG = _g;
		}
		else
		{
			colorG = 1.0;
		}
	}

	void setB(float _b) {
		if (_b >= 0 && _b <= 1) {
			colorB = _b;
		}
		else
		{
			colorB = 1.0;
		}
	}
};
