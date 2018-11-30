#pragma once
#include "Figure.h"
#include <vector>
using std::vector;


class CCurveB : public CFigure
{
	struct pair
	{
		float x, y;
	};
	vector<pair> punto;
	int numP;
	float xmax = -1, ymax = -1, xmin = INT_MAX, ymin = INT_MAX;
	float colorL[3] = { 1.0,0.0,0.0 };
public:
	//CCurveB();
	CCurveB(int NV);
	~CCurveB();
	void setNumP(int a);
	int getNumP();
	void setMax(int x, int y);
	float getMaxX();
	float getMaxY();
	void setMin(int x, int y);
	float getMinX();
	float getMinY();
	void display();
	void boundingBox();
	void move(int xNew, int yNew);
	void getMedio(int & mx, int & my);
	void pintarContorno(int x0, int y0, int x1, int y1);
	void resetMaxMin();
	void casteljau(vector<pair> points);
	void drawLineC0a45(int x0, int y0, int x1, int y1);
	void drawLineC45a90(int x0, int y0, int x1, int y1);
	void drawLineC270a315(int x0, int y0, int x1, int y1);
	void drawLineC315a360(int x0, int y0, int x1, int y1);
	void drawLine(int x0, int y0, int x1, int y1);
};
