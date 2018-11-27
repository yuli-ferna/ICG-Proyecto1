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

	//draw4Points(x0, y0, r);
	draw8Points(x0, y0, x, y, false);

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
	
	if (fill) 
	{
		drawLine(cx -rx, cy + ry-1, cx + rx+1);
		drawLine(cx -ry+1, cy + rx , cx + ry );
		drawLine(cx -ry+1, cy - rx , cx + ry );
		drawLine(cx -rx, cy - ry+1, cx + rx+1);
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

void CCircle::drawLineC0a45(int x0, int y0, int x1, int y1) {
	int dx, dy, x, y, d, incrE, incrNE;
	glColor3fv(mRColor);
	glBegin(GL_POINTS);

	//Delta x y y
	dx = x1 - x0;
	dy = y1 - y0;

	if (dy > dx) {

	}

	//Función paramétrica de la recta
	//Se le multiplica dos para evitar división
	d = dx - (dy << 1);
	//Incremento en ...
	incrE = -(dy << 1);
	incrNE = ((dx - dy) << 1);

	//Asigno las coordenadas del primer punto
	x = x0;
	y = y0;

	//Dibuja primer punto
	glVertex2i(x0, y0);
	while (x < x1) {
		//Pintar noreste
		if (d <= 0) {
			d = d + incrNE;
			y = y + 1;
		}
		//Pintar este
		else {
			d = d + incrE;
		}
		x = x + 1;
		glVertex2i(x, y);
	}


	glEnd();
}
