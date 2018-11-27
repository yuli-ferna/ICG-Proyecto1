#pragma once
#include "Figure.h"

class CCircle : public CFigure
{
public:
	CCircle();
	~CCircle();
	void PutPixel(int x, int y, float color[3]);
	void drawLineC0a45(int x0, int y0, int x1, int y1);
	void display();
	void drawCircle(int x0, int y0, int x, int y, int r, bool fill);
	void draw8Points(int cx, int cy, int rx, int ry, bool fill);
	void drawLine(int xmin, int y, int xmax);
	void draw4Points(int cx, int cy, int r);
};
