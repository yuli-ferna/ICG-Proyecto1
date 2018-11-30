#pragma once
#include "Figure.h"

class CElipse : public CFigure
{
public:
	CElipse();
	~CElipse();
	void display();
	void boundingBox();
	void move(int xNew, int yNew);
	void getMedio(int & mx, int & my);
	void pintarContorno(int x0, int y0, int x1, int y1, float mColor[3]);
	void drawLineC0a45(int x0, int y0, int x1, int y1, float color[3]);
	void drawLineC45a90(int x0, int y0, int x1, int y1, float color[3]);
	void drawElipse(int cx, int cy, int a, int b, int r);
	void draw4Points(int x, int y, int cx, int cy);
	void drawLine(int xmin, int y, int xmax);
	void PutPixel(int x, int y, float color[3]);
};

