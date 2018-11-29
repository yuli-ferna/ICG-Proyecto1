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

void CCircle::boundingBox()
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
	pintarContorno(r + x0 + 2, r + y0 + 2, -r + x0 - 2, -r + y0 - 2, mColor);


}

void CCircle::pintarContorno(int x0, int y0, int x1, int y1, float mColor[3]) {

	if (x0 <= x1)
	{
		drawLineC0a45(x0, y0, x1, y0, mColor);
		drawLineC0a45(x0, y1, x1, y1, mColor);
		if (y0 <= y1)
		{

			drawLineC45a90(x0, y0, x0, y1, mColor);
			drawLineC45a90(x1, y0, x1, y1, mColor);

		}
		else
		{
			drawLineC45a90(x0, y1, x0, y0, mColor);
			drawLineC45a90(x1, y1, x1, y0, mColor);

		}
	}
	else
	{
		drawLineC0a45(x1, y0, x0, y0, mColor);
		drawLineC0a45(x1, y1, x0, y1, mColor);
		if (y0 <= y1)
		{

			drawLineC45a90(x0, y0, x0, y1, mColor);
			drawLineC45a90(x1, y0, x1, y1, mColor);

		}
		else
		{
			drawLineC45a90(x0, y1, x0, y0, mColor);
			drawLineC45a90(x1, y1, x1, y0, mColor);

		}
	}
}

//0 a 45
void CCircle::drawLineC0a45(int x0, int y0, int x1, int y1, float color[3]) {
	int dx, dy, x, y, d, incrE, incrNE;
	glColor3fv(color);

	glBegin(GL_POINTS);

	//Delta x y y
	dx = x1 - x0;
	dy = y1 - y0;

	if (dy > dx) {

	}

	//Función paramétrica de la recta
	//Se le multiplica dos para evitar división
	d = dx - 2 * dy;
	//Incremento en ...
	incrE = -2 * dy;
	incrNE = 2 * (dx - dy);

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

//45 a 90
void CCircle::drawLineC45a90(int x0, int y0, int x1, int y1, float color[3]) {
	int dx, dy, x, y, d, incrE, incrNE, limite;
	glColor3fv(color);

	glBegin(GL_POINTS);
	//Limite del ciclo que pintara los puntos
	limite = x1;

	//Asigno las coordenadas del primer punto CAMBIO
	x = x0;
	y = y0;

	//Delta x y y CAMBIO swap dy dx
	dx = x1 - x0;
	dy = y1 - y0;

	swap(dx, dy);

	//Función paramétrica de la recta
	//Se le multiplica dos para evitar división
	d = dx - 2 * dy;
	//Incremento en ...
	incrE = -2 * dy;
	incrNE = 2 * (dx - dy);

	//Dibuja primer punto
	glVertex2i(x0, y0);

	//EL LIMITE CAMBIA
	while (y < y1) {
		//Pintar noreste
		if (d <= 0) {
			d = d + incrNE;
			x = x + 1;
		}
		//Pintar este
		else {
			d = d + incrE;
		}
		y = y + 1;
		glVertex2i(x, y);
	}


	glEnd();
}
