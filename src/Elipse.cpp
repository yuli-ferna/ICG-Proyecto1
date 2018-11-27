#include "Elipse.h"
#include <stdlib.h>
CElipse::CElipse()
{
	mVertices = new float*[2];
	for (int i = 0; i < 2; ++i)
		mVertices[i] = new float[2];

	mType = ELIPSE;
}

CElipse::~CElipse()
{
	for (int i = 0; i < 2; ++i)
		delete[] mVertices[i];
}

void CElipse::display()
{
	//glColor3fv(mColor);
	int cx, cy, x, y, a, b, bx;
	cx = mVertices[0][0];
	cy = mVertices[0][1];
	x = mVertices[1][0];
	y = mVertices[1][1];
	
	int dx, dy;
	dx = abs(x - cx);
	dy = abs(y - cy);

	int r = dy;
	a = dx; //El y se mantiene
	b = dy; //Tiene que ser una altura
	drawElipse(cx, cy, a, b, r);

}


void CElipse::drawElipse(int cx, int cy, int a, int b, int r) {
	int x, y, d, aCuadrado, bCuadrado;
	bool fill = true;
	x = 0;
	y = b;
	aCuadrado = a * a;
	bCuadrado = b * b;
	d = b * ((b << 2) - (aCuadrado << 2)) + aCuadrado;
	//Modalidad 1
	draw4Points(x, y, cx, cy, false);
	while (bCuadrado  * ((x + 1) << 1) < aCuadrado *((y << 1) - 1)) {

		if (d < 0)
			d = d + ((bCuadrado *((x << 1) + 3)) << 2);
		else {
			d = d + ((bCuadrado *((x << 1) + 3) + aCuadrado *(-(y << 1) + 2)) << 2);
			y = y - 1;
		}
		x = x + 1;

		draw4Points(x, y, cx, cy, fill);
	}

	//Modalidad 2
	d = bCuadrado *(((x*x) << 2) + (x << 2) + 1) + aCuadrado *(((y*y) << 2) - (y << 3) + 4) - ((aCuadrado * bCuadrado) << 2) ;
	while (y > 0) {

		if (d < 0) {

			d = d + ((bCuadrado *((x + 2) << 1) + aCuadrado *(-(y << 1) + 3)) << 2);
			x = x + 1;
		}
		else {
			d = d + (aCuadrado *(-(y << 1) + 3) << 2);

		}
		y = y - 1;
		draw4Points(x, y, cx, cy, fill);
	}


}

void CElipse::draw4Points(int x, int y, int cx, int cy, bool fill)
{
	if (fill)
	{
		/* no tiene fallo de los dos pixeles
		drawLine(cx - x, cy + y, cx + x + 1);
		drawLine(cx - x, cy - y, cx + x + 1);*/
		drawLine(cx - x, cy + y - 1, cx + x + 1);
		drawLine(cx - x, cy - y + 1, cx + x + 1);
	}
	PutPixel(cx + x, cy + y, mColor);
	PutPixel(cx + x, cy - y, mColor);
	PutPixel(cx - x, cy + y, mColor);
	PutPixel(cx - x, cy - y, mColor);
	
}

void CElipse::drawLine(int xmin, int y, int xmax)
{
	for (int i = xmin; i < xmax; i++)
	{
		PutPixel(i, y, mRColor);
	}
}

void CElipse::PutPixel(int x, int y, float color[3])
{
	glColor3fv(color);

	glBegin(GL_POINTS);
	glVertex2i(x, y);
	glEnd();
}