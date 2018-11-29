#include "Circle.h"
#include <stdio.h>
#include <stdlib.h>

CCircle::CCircle()
{
	boundB = false;
	mVertices = new float*[2];
	for (int i = 0; i < 2; ++i)
		mVertices[i] = new float[2];

	mType = CIRCLE;
}

CCircle::~CCircle()
{
	for (int i = 0; i < 2; ++i)
		delete[] mVertices[i];
}

void CCircle::display()
{
	glColor3fv(mColor);
	int x0, y0, x1, y1, x, y, dx, dy;
	x0 = mVertices[0][0];
	y0 = mVertices[0][1];
	x1 = mVertices[1][0];
	y1 = mVertices[1][1];

	dx = abs(x0 - x1);
	dy = abs(y0 - y1);
	int r = dx;
	x = 0;
	y = r;   
	if (dy > dx)
	{
		r = dy;
		y = r;
	}
	drawCircle(x0, y0, x, y, r);
	

}

void CCircle::drawCircle(int x0, int y0, int x, int y, int r)
{
	int d = 1 - r;

	if (relleno)
	{
		//Linea del medio (caso borde)
		drawLine(x0 - r, y0, x0 + r);
	}
	draw8Points(x0, y0, x, y);

	while (y > x) {

		if (d < 0)
		{
			d += (x << 1) + 3;
		}
		else {
			d += ((x - y) << 1) + 5;
			y += -1;
		}
		x += 1;
		draw8Points(x0, y0, x, y);

	}
}

void CCircle::draw8Points(int cx, int cy, int rx, int ry)
{
	
	if (relleno) 
	{
		drawLine(cx -rx, cy + ry - 1, cx + rx + 1);
		drawLine(cx -ry + 1, cy + rx , cx + ry );
		drawLine(cx -ry + 1, cy - rx , cx + ry );
		drawLine(cx -rx, cy - ry + 1, cx + rx + 1);
	}
	PutPixel(cx + rx, cy + ry, mColor);
	PutPixel(cx + rx, cy - ry, mColor);
	PutPixel(cx - rx, cy + ry, mColor);
	PutPixel(cx - rx, cy - ry, mColor);
	PutPixel(cx + ry, cy + rx, mColor);
	PutPixel(cx + ry, cy - rx, mColor);
	PutPixel(cx - ry, cy + rx, mColor);
	PutPixel(cx - ry, cy - rx, mColor);
}
void CCircle::drawLine(int xmin, int y, int xmax)
{
	for (int i = xmin; i < xmax; i++)
	{
		PutPixel(i, y, mRColor);
	}
}

void CCircle::PutPixel(int x, int y, float color[3])
{
	glColor3fv(color);

	glBegin(GL_POINTS);
	glVertex2i(x, y);
	glEnd();
}