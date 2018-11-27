#pragma once
#include "Figure.h"
class CCurveB : public CFigure
{
public:
	CCurveB();
	~CCurveB();
	void display();
	void casteljau();
};
