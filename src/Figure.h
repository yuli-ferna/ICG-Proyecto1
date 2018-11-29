#pragma once

#include "../headers/glfw3.h"

enum FigureType
{
	NONE,
	LINE,
	QUAD,
	CIRCLE,
	TRIANGLE,
	ELIPSE,
	BCURVE,
};

class CFigure
{
protected:
	float **mVertices, mColor[3], mRColor[3];
	bool relleno;
	int mType;

public:
	CFigure();
	virtual ~CFigure();
	void setVertex(int id, float x, float y);
	void setColor(float r, float g, float b);
	void setRColor(float r, float g, float b);
	void setRelleno(bool r);
	virtual void display() = 0;
	int getType();
	virtual void setBoundingBox(bool bb) = 0;
	bool getRelleno();
	float* getVertex(int id);
	float* getColor();
	float* getRColor();
	void swap(int &a, int &b);

};