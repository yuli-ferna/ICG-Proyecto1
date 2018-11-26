#pragma once
#include "Figure.h"

class CCircle : public CFigure
{
public:
	CCircle();
	~CCircle();
	void draw8Points(int cx, int cy, int rx, int ry);
	void display();
	void drawCircle(int x0, int y0, int x, int y, int r);
	void draw4Points(int cx, int cy, int r);
};
