#pragma once
#include "Figure.h"

class CCircle : public CFigure
{
public:
	CCircle();
	~CCircle();
	void draw8Points(int cx, int cy, int rx, int ry);
	void display();
	void draw4Points(int cx, int cy, int r);
};
