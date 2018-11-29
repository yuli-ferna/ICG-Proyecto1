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
	bool relleno, boundB;
	int mType;

public:
	CFigure();
	virtual ~CFigure();
	void setVertex(int id, float x, float y);
	void setColor(float r, float g, float b);
	void setRColor(float r, float g, float b);
	void setRelleno(bool r);
	virtual void display() = 0;
	virtual void boundingBox() = 0;
	int getType();
	void setBoundingBox(bool bb);
	bool getBoundingBox();
	bool getRelleno();
	float* getVertex(int id);
	float* getColor();
	float* getRColor();
	void swap(int &a, int &b);

};