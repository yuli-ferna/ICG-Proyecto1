#include "Quad.h"
#include "Line.h"

CQuad::CQuad()
{
	mVertices = new float*[2];
	for (int i = 0; i < 2; ++i)
		mVertices[i] = new float[2];

	mType = QUAD;
}

CQuad::~CQuad()
{
	for (int i = 0; i < 2; ++i)
		delete[] mVertices[i];
}

void CQuad::display()
{
	int x0, y0, x1, y1, dx, dy, caso = 1;
	x0 = mVertices[0][0];
	y0 = mVertices[0][1];
	x1 = mVertices[1][0];
	y1 = mVertices[1][1];

	//pintarContorno(x0, y0, x1, y1, mColor);
	//glColor3fv(mRColor);

	rellenoCuadrado(x0, y0, x1, y1, mColor, mRColor);

	
}

void CQuad::rellenoCuadrado(int x0, int y0, int x1, int y1, float mColor[3], float fillColor[3]) {

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

	//Colorear dos primeras lineas
	drawLineC0a45(xmin, ymin, xmax, ymin, mColor);
	drawLineC0a45(xmin, ymax, xmax, ymax, mColor);
	it = ymin + 1;

	for (int i = it; i < ymax; i++)
	{
		PutPixel(xmin, i, mColor);
		drawLineC0a45(xmin + 1, i, xmax - 1, i, fillColor);
		PutPixel(xmax, i, mColor);

	}


}

void CQuad::pintarContorno(int x0, int y0, int x1, int y1, float mColor[3]) {

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
void CQuad::drawLineC0a45(int x0, int y0, int x1, int y1, float color[3]) {
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
void CQuad::drawLineC45a90(int x0, int y0, int x1, int y1, float color[3]) {
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

void CQuad::PutPixel(int x, int y, float mColor[3])
{
	glColor3fv(mColor);

	glBegin(GL_POINTS);
	glVertex2i(x, y);
	glEnd();
}