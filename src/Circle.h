#pragma once
#include "Figure.h"

class CCircle : public CFigure
{
public:
	CCircle();
	~CCircle();
	void PutPixel(int x, int y, float color[3]);
	void boundingBox();
	void pintarContorno(int x0, int y0, int x1, int y1, float mColor[3]);
	void drawLineC0a45(int x0, int y0, int x1, int y1, float color[3]);
	void drawLineC45a90(int x0, int y0, int x1, int y1, float color[3]);
	void display();
	void drawCircle(int x0, int y0, int x, int y, int r);
	void draw8Points(int cx, int cy, int rx, int ry);
	void drawLine(int xmin, int y, int xmax);
};
