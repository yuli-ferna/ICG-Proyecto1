#include "Triangle.h"
#include <stdio.h>

CTriangle::CTriangle()
{
	mVertices = new float*[3];
	for (int i = 0; i < 3; ++i)
		mVertices[i] = new float[2];

	mType = TRIANGLE;
}

CTriangle::~CTriangle()
{
	for (int i = 0; i < 3; ++i)
		delete[] mVertices[i];
}

void CTriangle::display()
{
	glColor3fv(mColor);
	int x0, y0, x1, y1, x2, y2;
	x0 = mVertices[0][0];
	y0 = mVertices[0][1];
	x1 = mVertices[1][0];
	y1 = mVertices[1][1];
	x2 = mVertices[2][0];
	y2 = mVertices[2][1];

	drawLine(x0, y0, x1, y1);
	drawLine(x1, y1, x2, y2);
	drawLine(x2, y2, x0, y0);
	

}

void CTriangle::boundingBox()
{
	int x0, y0, x1, y1, x2, y2;
	x0 = mVertices[0][0];
	y0 = mVertices[0][1];
	x1 = mVertices[1][0];
	y1 = mVertices[1][1];
	x2 = mVertices[2][0];
	y2 = mVertices[2][1];

	rellenoCuadrado(x0 - 2, y0 - 2, x0 + 2, y0 + 2);
	rellenoCuadrado(x1 - 2, y1 - 2, x1 + 2, y1 + 2);
	rellenoCuadrado(x2 - 2, y2 - 2, x2 + 2, y2 + 2);

}

void CTriangle::rellenoCuadrado(int x0, int y0, int x1, int y1) {

	int xmin, xmax, ymin, ymax, it;
	xmin = x0;
	xmax = x1;
	ymin = y0;
	ymax = y1;

	if (x0 > x1)
	{
		xmax = x0;
		xmin = x1;

	}
	if (y0 > y1)
	{
		ymax = y0;
		ymin = y1;
	}
	glColor3fv(mColor);

	//Colorear dos primeras lineas
	drawLineC0a45(xmin, ymin, xmax, ymin);
	drawLineC0a45(xmin, ymax, xmax, ymax);
	it = ymin + 1;

	for (int i = it; i < ymax; i++)
	{
		PutPixel(xmin, i, mColor);
		drawLineC0a45(xmin + 1, i, xmax - 1, i);
		PutPixel(xmax, i, mColor);

	}


}

void CTriangle::PutPixel(int x, int y, float mColor[3])
{
	glColor3fv(mColor);

	glBegin(GL_POINTS);
	glVertex2i(x, y);
	glEnd();
}

//Principales
//0 a 45
void CTriangle::drawLineC0a45(int x0, int y0, int x1, int y1) {
	int dx, dy, x, y, d, incrE, incrNE;

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

//45 a 90
void CTriangle::drawLineC45a90(int x0, int y0, int x1, int y1) {
	int dx, dy, x, y, d, incrE, incrNE, limite;

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
	d = dx - (dy << 1);
	//Incremento en ...
	incrE = -(dy << 1);
	incrNE = ((dx - dy) << 1);

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

//270 a 315
void CTriangle::drawLineC270a315(int x0, int y0, int x1, int y1) {
	int dx, dy, x, y, d, incrE, incrNE, limite;

	glBegin(GL_POINTS);

	//Asigno las coordenadas del primer punto CAMBIO
	x = x0;
	y = y0;

	//Delta x y y CAMBIO swap dy dx
	dx = x1 - x0;
	dy = y1 - y0;

	swap(dx, dy);

	//multiplicar dx por -1
	d = -dx - (dy << 1);
	//Incremento en ...
	incrE = -(dy << 1);
	incrNE = ((-dx - dy) << 1);

	//Dibuja primer punto
	glVertex2i(x0, y0);

	//EL LIMITE CAMBIA
	while (y1 < y) {
		//Pintar noreste
		if (d <= 0) {
			d += incrNE;
			x += 1;
		}
		//Pintar este
		else {
			d += incrE;
		}
		y += -1;
		glVertex2i(x, y);
	}


	glEnd();
}

//315 a 360
void CTriangle::drawLineC315a360(int x0, int y0, int x1, int y1) {
	int dx, dy, x, y, d, incrE, incrNE, limite;

	glBegin(GL_POINTS);
	//Limite del ciclo que pintara los puntos
	limite = x1;

	//Asigno las coordenadas del primer punto CAMBIO
	x = x0;
	y = y0;

	//Delta x y y CAMBIO swap dy dx
	dx = x1 - x0;
	dy = y1 - y0;


	//Función paramétrica de la recta
	//Se le multiplica dos para evitar división
	d = dx + (dy << 1);
	//Incremento en ...
	incrE = (dy << 1);
	incrNE = ((dx + dy) << 1);

	//Dibuja primer punto
	glVertex2i(x0, y0);

	//EL LIMITE CAMBIA
	while (x < x1) {
		//Pintar noreste
		if (d <= 0) {
			d = d + incrNE;
			y = y - 1;
		}
		//Pintar este
		else {
			d = d + incrE;
		}
		x = x + 1;
		//Por optimizar
		glVertex2i(x, y);
	}


	glEnd();
}

void CTriangle::drawLine(int x0, int y0, int x1, int y1) {

	int dx, dy;
	dx = x1 - x0;
	dy = y1 - y0;

	if (y0 <= y1)
	{
		if (dx >= 0) {
			if (dy <= dx)
				drawLineC0a45(x0, y0, x1, y1);
			else
			{
				drawLineC45a90(x0, y0, x1, y1);
			}
		}
		else {
			if (-dx <= dy)
				//Por simetría
				drawLineC270a315(x1, y1, x0, y0);
			else
			{
				//Por simetría
				drawLineC315a360(x1, y1, x0, y0);
			}
		}

	}
	else {
		if (dx >= 0)
		{
			if (dx <= -dy)
				drawLineC270a315(x0, y0, x1, y1);

			else
			{
				drawLineC315a360(x0, y0, x1, y1);
			}
		}
		else {
			if (-dx <= -dy)
				//Por simetría
				drawLineC45a90(x1, y1, x0, y0);
			else
			{
				//Por simetría
				drawLineC0a45(x1, y1, x0, y0);
			}
		}
	}


}
