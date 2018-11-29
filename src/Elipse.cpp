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

void CElipse::boundingBox()
{
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
	
	pintarContorno(a + cx + 2, b + cy + 2, -a + cx - 2, -b + cy - 2, mColor);
	
}

void CElipse::pintarContorno(int x0, int y0, int x1, int y1, float mColor[3]) {

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
void CElipse::drawLineC0a45(int x0, int y0, int x1, int y1, float color[3]) {
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
void CElipse::drawLineC45a90(int x0, int y0, int x1, int y1, float color[3]) {
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


void CElipse::drawElipse(int cx, int cy, int a, int b, int r) {
	int x, y, d, aCuadrado, bCuadrado;

	x = 0;
	y = b;
	aCuadrado = a * a;
	bCuadrado = b * b;
	d = b * ((b << 2) - (aCuadrado << 2)) + aCuadrado;
	//Modalidad 1
	draw4Points(x, y, cx, cy);
	while (bCuadrado  * ((x + 1) << 1) < aCuadrado *((y << 1) - 1)) {

		if (d < 0)
			d = d + ((bCuadrado *((x << 1) + 3)) << 2);
		else {
			d = d + ((bCuadrado *((x << 1) + 3) + aCuadrado *(-(y << 1) + 2)) << 2);
			y = y - 1;
		}
		x = x + 1;

		draw4Points(x, y, cx, cy);
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
		draw4Points(x, y, cx, cy);
	}


}

void CElipse::draw4Points(int x, int y, int cx, int cy)
{
	if (relleno)
	{
		/* 
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