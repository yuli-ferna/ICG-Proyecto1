#pragma once
#include "Figure.h"

class CElipse : public CFigure
{
public:
	CElipse();
	~CElipse();
	void display();
	void drawElipse(int cx, int cy, int a, int b, int r);
	void draw4Points(int x, int y, int cx, int cy);
};

