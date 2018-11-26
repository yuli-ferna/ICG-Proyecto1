#pragma once
#include "Figure.h"
class CTriangle : public CFigure
{
	public:
	CTriangle();
	~CTriangle();
	void display();
	void drawLineC0a45(int x0, int y0, int x1, int y1);
	void drawLineC45a90(int x0, int y0, int x1, int y1);
	void drawLineC270a315(int x0, int y0, int x1, int y1);
	void drawLineC315a360(int x0, int y0, int x1, int y1);
	void drawLine(int x0, int y0, int x1, int y1);
};

