#include "Line.h"
#include <math.h>
#define MIN(a,b) (((a)<(b))?(a):(b))
#define MAX(a,b) (((a)>(b))?(a):(b))

CLine::CLine()
{
	mVertices = new float*[2];
	for (int i = 0; i < 2; ++i)
		mVertices[i] = new float[2];

	mType = LINE;
}

CLine::~CLine()
{
	for (int i = 0; i < 2; ++i)
		delete[] mVertices[i];
}


void CLine::display()
{
	glColor3fv(mColor);

	int x0, y0, x1, y1;
	x0 = mVertices[0][0];
	y0 = mVertices[0][1];
	x1 = mVertices[1][0];
	y1 = mVertices[1][1];
	drawLine(x0, y0, x1, y1);
	
}

void CLine::boundingBox()
{
	glColor3fv(mColor);

	int x0, y0, x1, y1;
	x0 = mVertices[0][0];
	y0 = mVertices[0][1];
	x1 = mVertices[1][0];
	y1 = mVertices[1][1];
	int xm, ym;
	getMedio(xm, ym);
	glPointSize(4.0);
	glBegin(GL_POINTS);
		glVertex2i(x0, y0);
		glVertex2i(xm, ym);
		glVertex2i(x1, y1);
	glEnd();
	glPointSize(1.0);

}

void CLine::getMedio(int &mx, int &my) 
{
	int x0, y0, x1, y1;
	x0 = mVertices[0][0];
	y0 = mVertices[0][1];
	x1 = mVertices[1][0];
	y1 = mVertices[1][1];
	
	int dx, dy;
	dx = abs(x0 - x1);
	dy = abs(y0 - y1);
	int xmin = MIN(x0, x1);
	int ymin = MIN(y0, y1);
	
	mx = (dx / 2) + xmin;
	my = (dy / 2) + ymin;

}

void CLine::move(int xNew, int yNew)
{
	int x0, y0, x1, y1;
	x0 = mVertices[0][0];
	y0 = mVertices[0][1];
	x1 = mVertices[1][0];
	y1 = mVertices[1][1];

	int puntoRestarX;
	int puntoRestarY;
	getMedio(puntoRestarX, puntoRestarY);
	xNew = (xNew - puntoRestarX);
	yNew = (yNew - puntoRestarY);
	mVertices[0][0] = x0 + xNew;
	mVertices[0][1] = y0 + yNew;
	mVertices[1][0] = x1 + xNew ;
	mVertices[1][1] = y1 + yNew ;

}

void CLine::PutPixel(int x, int y, float mColor[3])
{
	glColor3fv(mColor);

	glBegin(GL_POINTS);
	glVertex2i(x, y);
	glEnd();
}

//Principales
//0 a 45
void CLine::drawLineC0a45(int x0, int y0, int x1, int y1) {
	int dx, dy, x, y, d, incrE, incrNE;

	glBegin(GL_POINTS);

	//Delta x y y
	dx = x1 - x0;
	dy = y1 - y0;

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
void CLine::drawLineC45a90(int x0, int y0, int x1, int y1) {
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
void CLine::drawLineC270a315(int x0, int y0, int x1, int y1) {
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
void CLine::drawLineC315a360(int x0, int y0, int x1, int y1) {
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

void CLine::drawLine(int x0, int y0, int x1, int y1) {
	
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