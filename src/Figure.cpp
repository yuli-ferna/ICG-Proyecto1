#include "Figure.h"

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

void CFigure::setColor(float r, float g, float b)
{
	mColor[0] = r;
	mColor[1] = g;
	mColor[2] = b;
}
/*
void CFigure::swapF(CFigure* a, CFigure* b)
{
	CFigure * c = a;
	a = b;
	b = c;
}

void CFigure::eliminar(int picked)
{
	int nFig = figures.size();
	for (int ii = picked; ii < nFig + 1; ii++)
	{
		swapF(figures[ii], figures[ii + 1]);
	}
	figures.pop_back();
	picked = -1;
}*/

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


void CFigure::swap(int & a, int & b)
{
	int c = a;
	a = b;
	b = c;
}
