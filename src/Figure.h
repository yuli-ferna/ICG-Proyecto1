#pragma once

#include "../headers/glfw3.h"

#include <vector>
using std::vector;

#define MIN(a,b) (((a)<(b))?(a):(b))
#define MAX(a,b) (((a)>(b))?(a):(b))

enum FigureType
{
	NONE,
	LINE,
	QUAD,
	CIRCLE,
	TRIANGLE,
	ELIPSE,
	BCURVE,
	TRASLADAR,
};

class CFigure
{
protected:
	float **mVertices, mColor[3], mRColor[3];
	bool relleno, boundB;
	int mType;
	struct pairF
	{
		float x, y;
	};
	vector<pairF> vVertices;
public:
	CFigure();
	virtual ~CFigure();
	void setVertex(int id, float x, float y);
	void setVertice(float x, float y);
	void setColor(float r, float g, float b);
	void setRColor(float r, float g, float b);
	void setRelleno(bool r);
	virtual void display() = 0;
	virtual void move(int xNew, int yNew) = 0;
	virtual void boundingBox() = 0;
	int getType();
	void setBoundingBox(bool bb);
	bool getBoundingBox();
	bool getRelleno();
	float* getVertex(int id);
	float* getColor();
	float* getRColor();
	void getMedio(float & mx, float & my);
	void swap(int &a, int &b);

};