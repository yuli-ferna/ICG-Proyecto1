#pragma once
#include "Figure.h"
class CTriangle : public CFigure
{
	public:
	CTriangle();
	~CTriangle();
	void display();
	void scanLine(int x0, int x1, int x2, int y0, int y1, int y2);
	void intersection(int x0, int y0, int x1, int y1, int x2, int y2, int yy, int & xmin, int & xmax);
	void getMedio(int & mx, int & my);
	void move(int xNew, int yNew);
	int MAX3(int a, int b, int c);
	int MIN3(int a, int b, int c);
	void scanLine();
	void boundingBox();
	void pintarContorno(int x0, int y0, int x1, int y1);
	void PutPixel(int x, int y, float mColor[3]);
	void drawLineC0a45(int x0, int y0, int x1, int y1);
	void drawLineC45a90(int x0, int y0, int x1, int y1);
	void drawLineC270a315(int x0, int y0, int x1, int y1);
	void drawLineC315a360(int x0, int y0, int x1, int y1);
	void drawLine(int x0, int y0, int x1, int y1);
};

