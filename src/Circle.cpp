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
	
	dx = abs(x0 - x1);
	dy = abs(y0 - y1);
	int r = dx;
	x = 0;
	y = r;   
	int d = 1 - r;
	if (dy > dx)
	{
		r = dy;
		y = r;
	}

	draw4Points(x0, y0, r);
	while (y > x) {
		
		if (d < 0)
		{
			d += (x << 1) + 3;
		}
		else {
			d += ((x - y) << 1) + 5;
			y += - 1;
		}
		x += 1;
		draw8Points(x0, y0, x, y);

	}

}

void CCircle::draw4Points(int cx, int cy, int r)
{
	
	glBegin(GL_POINTS);
	glVertex2i(cx, cy + r);
	glVertex2i(cx + r, cy);
	glVertex2i(cx, cy - r);
	glVertex2i(cx - r, cy);
	glEnd();
}

void CCircle::draw8Points(int cx, int cy, int rx, int ry)
{
	glBegin(GL_POINTS);
	glVertex2i(cx + rx, cy + ry);
	glVertex2i(cx + rx, cy - ry);
	glVertex2i(cx - rx, cy + ry);
	glVertex2i(cx - rx, cy - ry);
	glVertex2i(cx + ry, cy + rx);
	glVertex2i(cx + ry, cy - rx);
	glVertex2i(cx - ry, cy + rx);
	glVertex2i(cx - ry, cy - rx);
	glEnd();
}
