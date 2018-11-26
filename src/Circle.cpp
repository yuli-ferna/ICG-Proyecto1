#include "Circle.h"
#include <stdio.h>
#include <stdlib.h>

CCircle::CCircle()
{
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
	//printf("%d\n", x0);
	bool fill = true;
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
	drawCircle(x0, y0, x, y, r, true);
	

}

void CCircle::drawCircle(int x0, int y0, int x, int y, int r, bool fill)
{
	int d = 1 - r;

	draw4Points(x0, y0, r);
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
		draw8Points(x0, y0, x, y, fill);

	}
}

void CCircle::draw4Points(int cx, int cy, int r)
{
	
	PutPixel(cx, cy + r, mColor);
	PutPixel(cx + r, cy, mColor);
	PutPixel(cx, cy - r, mColor);
	PutPixel(cx - r, cy, mColor);

}

void CCircle::draw8Points(int cx, int cy, int rx, int ry, bool fill)
{
	/**/
	if (fill) 
	{
		drawLine(cx -rx + 1, cy + ry, cx + rx - 1);
		drawLine(cx -ry + 1, cy + rx, cx + ry - 1);
		drawLine(cx -ry + 1, cy + -rx, cx + ry - 1);
		drawLine(cx -rx + 1, cy + -ry, cx + rx - 1);
	}*/
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