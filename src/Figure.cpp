#include "Figure.h"
#include <math.h>

CFigure::CFigure()
{
	mColor[0] = mColor[1] = mColor[2] = 0.0f;
	mRColor[0] = mRColor[1] = mRColor[2] = 0.7f;
}

CFigure::~CFigure()
{
	delete[] mVertices;
}

void CFigure::setVertex(int id, float x, float y)
{
	mVertices[id][0] = x;
	mVertices[id][1] = y;
}

/*vertices triangulo y bezier*/
void CFigure::setVertice(float x, float y)
{
	pairF a;
	a.x = x;
	a.y = y;
	vVertices.push_back(a);
}

void CFigure::setColor(float r, float g, float b)
{
	mColor[0] = r;
	mColor[1] = g;
	mColor[2] = b;
}

void CFigure::setRColor(float r, float g, float b)
{
	mRColor[0] = r;
	mRColor[1] = g;
	mRColor[2] = b;
}

void CFigure::setRelleno(bool r)
{
	relleno = r;
}

int CFigure::getType()
{
	return mType;
}

void CFigure::setBoundingBox(bool bb)
{
	boundB = bb;
}

bool CFigure::getBoundingBox()
{
	return boundB;
}

bool CFigure::getRelleno()
{
	return relleno;
}

float* CFigure::getVertex(int id)
{
	return mVertices[id];
}

float* CFigure::getColor()
{
	return mColor;
}

float * CFigure::getRColor()
{
	return mRColor;
}

void CFigure::getMedio(float &mx, float &my)
{
	int x0, y0, x1, y1;
	x0 = mVertices[0][0];
	y0 = mVertices[0][1];
	x1 = mVertices[1][0];
	y1 = mVertices[1][1];

	int dx, dy;
	dx = abs(x0 - x1);
	dy = abs(y0 - y1);
	int xmin = MIN(x0, x1);
	int ymin = MIN(y0, y1);

	mx = (dx / 2) + xmin;
	my = (dy / 2) + ymin;

}

void CFigure::swap(int & a, int & b)
{
	int c = a;
	a = b;
	b = c;
}
