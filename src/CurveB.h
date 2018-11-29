#pragma once
#include "Figure.h"
#include <vector>
using std::vector;


class CCurveB : public CFigure
{
	struct pair
	{
		int x, y;
	};
	vector<pair> punto;
	int numP;

public:
	CCurveB();
	~CCurveB();
	void setNumP(int a);
	int getNumP();
	void display();
	void boundingBox();
	void pintarContorno(int x0, int y0, int x1, int y1, float mColor[3]);
	void drawLineC0a45(int x0, int y0, int x1, int y1, float color[3]);
	void drawLineC45a90(int x0, int y0, int x1, int y1, float color[3]);
	void casteljau(vector<pair> points);
};
