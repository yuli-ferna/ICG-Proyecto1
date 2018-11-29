#include "CurveB.h"

CCurveB::CCurveB()
{
	mVertices = new float*[4];
	for (int i = 0; i < 4; ++i)
		mVertices[i] = new float[2];

	mType = BCURVE;
}

CCurveB::~CCurveB()
{
	for (int i = 0; i < 4; ++i)
		delete[] mVertices[i];
}

void CCurveB::setNumP(int a)
{
}

int CCurveB::getNumP()
{
	return 0;
}

void CCurveB::display()
{
	for (int i = 0; i < 4; i++)
	{
		pair p;
		p.x = mVertices[i][0];
		p.y = mVertices[i][1];
		punto.push_back(p);
	}
	glColor3fv(mColor);
	int puntosN = punto.size();
	glBegin(GL_POINTS);
	for (int jj = 0; jj < puntosN; jj++)
	{
		glVertex2i(punto[jj].x, punto[jj].y);
	}

	glEnd();

}

void CCurveB::boundingBox()
{

}

void CCurveB::pintarContorno(int x0, int y0, int x1, int y1, float mColor[3]) {

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
void CCurveB::drawLineC0a45(int x0, int y0, int x1, int y1, float color[3]) {
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
void CCurveB::drawLineC45a90(int x0, int y0, int x1, int y1, float color[3]) {
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


void CCurveB::casteljau(vector<pair> points) {
	vector<pair> C;
	int length = points.size();
	int numeroVertices = points.size();
	double paso = 0.1;
	float *VertXY1;
	glBegin(GL_LINE_STRIP);
	for (double tt = 0.0; tt < 1.0; tt+= paso)
	{
		C = points;
		for (int rr = 0; rr < (numeroVertices - 1); rr++)
		{
			for (int ii = 0; ii < length; ii++)
			{
				C[ii].x = float((1.0 - tt) * C[ii].x) + float(tt * C[ii + 1].x);
				C[ii].y = float((1.0 - tt) * C[ii].y) + float(tt * C[ii + 1].y);
			}
		}
		VertXY1[0] = C[0].x;
		VertXY1[1] = C[0].y;
		glVertex2fv(VertXY1);
	}
	glEnd();
}
