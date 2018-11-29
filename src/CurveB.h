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
	void casteljau(vector<pair> points);
};
