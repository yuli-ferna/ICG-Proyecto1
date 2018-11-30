#include "CurveB.h"

CCurveB::CCurveB(int NV)
{
	setNumP(NV);
	mVertices = new float*[NV];
	for (int i = 0; i < NV; ++i)
		mVertices[i] = new float[2];

	mType = BCURVE;
}

CCurveB::~CCurveB()
{
	for (int i = 0; i < getNumP(); ++i)
		delete[] mVertices[i];
}

void CCurveB::setNumP(int a)
{
	numP = a;
}

int CCurveB::getNumP()
{
	return numP;
}

void CCurveB::setMax(int x, int y)
{
	if (xmax < x)
	{
		xmax = x;
	}
	if (ymax < y)
	{
		ymax = y;
	}
}

float CCurveB::getMaxX()
{
	return xmax;
}

float CCurveB::getMaxY()
{
	return ymax;
}

void CCurveB::setMin(int x, int y)
{
	if (x < xmin)
	{
		xmin = x;
	}
	if (y < ymin)
	{
		ymin = y;
	}
}

float CCurveB::getMinX()
{
	return xmin;
}

float CCurveB::getMinY()
{
	return ymin;
}

void CCurveB::display()
{
	for (int i = 0; i < getNumP(); i++)
	{
		pair p;
		p.x = mVertices[i][0];
		p.y = mVertices[i][1];
		punto.push_back(p);
	}

	glColor3fv(mColor);
	int puntosN = punto.size();
	glPointSize(4.0);
	glBegin(GL_POINTS);
	
	for (int jj = 0; jj < puntosN; jj++)
	{
		glVertex2i(punto[jj].x, punto[jj].y);
	}

	glEnd();
	glPointSize(1.0);
	glColor3fv(colorL);

	for (int ii = 0; ii < puntosN-1; ii++)
	{
		drawLine(punto[ii].x, punto[ii].y, punto[ii + 1].x, punto[ii + 1].y);
	}
	glColor3fv(mColor);

	casteljau(punto);
	punto.clear();
}

void CCurveB::boundingBox()
{
	glColor3fv(colorL);
	pintarContorno(getMaxX(), getMaxY(), getMinX(), getMinY());
	int mx, my;
	getMedio(mx, my);
	glPointSize(4.0);
	glBegin(GL_POINTS);
	glVertex2i(mx, my);
	glEnd();
	glPointSize(1.0);
}

void CCurveB::move(int xNew, int yNew)
{
	int xmax = getMaxX();
	int ymax = getMaxY();
	int xmin = getMinX();
	int ymin = getMinY();

	int puntoRestarX;
	int puntoRestarY;
	getMedio(puntoRestarX, puntoRestarY);
	xNew = (xNew - puntoRestarX);
	yNew = (yNew - puntoRestarY);
	int length = getNumP();
	
	for (int ii = 0; ii < length; ii++)
	{
		mVertices[ii][0] = mVertices[ii][0] + xNew;
		mVertices[ii][1] = mVertices[ii][1] + yNew;
		setMax(mVertices[ii][0], mVertices[ii][1]);
		setMin(mVertices[ii][0], mVertices[ii][1]);
	}

	resetMaxMin();
}

void CCurveB::getMedio(int &mx, int &my)
{
	int xmax = getMaxX();
	int ymax = getMaxY();
	int xmin = getMinX();
	int ymin = getMinY();

	int dx = abs(xmax - xmin);
	int dy = abs(ymax - ymin);
	
	mx = (dx / 2) + xmin;
	my = (dy / 2) + ymin;

}

void CCurveB::pintarContorno(int x0, int y0, int x1, int y1) 
{

	if (x0 <= x1)
	{
		drawLineC0a45(x0, y0, x1, y0);
		drawLineC0a45(x0, y1, x1, y1);
		if (y0 <= y1)
		{

			drawLineC45a90(x0, y0, x0, y1);
			drawLineC45a90(x1, y0, x1, y1);

		}
		else
		{
			drawLineC45a90(x0, y1, x0, y0);
			drawLineC45a90(x1, y1, x1, y0);

		}
	}
	else
	{
		drawLineC0a45(x1, y0, x0, y0);
		drawLineC0a45(x1, y1, x0, y1);
		if (y0 <= y1)
		{

			drawLineC45a90(x0, y0, x0, y1);
			drawLineC45a90(x1, y0, x1, y1);

		}
		else
		{
			drawLineC45a90(x0, y1, x0, y0);
			drawLineC45a90(x1, y1, x1, y0);

		}
	}
}

void CCurveB::resetMaxMin()
{
	xmax = -1;
	ymax = -1; 
	xmin = INT_MAX; 
	ymin = INT_MAX;
}

void CCurveB::casteljau(vector<pair> points) {
	vector<pair> C;
	int length = points.size();
	int numeroVertices = points.size();
	double paso = 0.001;
	float VertXY1[2];
	glBegin(GL_LINE_STRIP);
	C = points;

	for (double tt = 0.0; tt < 1.0; tt+= paso)
	{
		for (int rr = 0; rr < (numeroVertices - 1); rr++)
		{
			for (int ii = 0; ii < (length - 1) - rr; ii++)
			{
				C[ii].x = float((1.0 - tt) * C[ii].x) + float(tt * C[ii + 1].x);
				C[ii].y = float((1.0 - tt) * C[ii].y) + float(tt * C[ii + 1].y);
			}
		}
		VertXY1[0] = C[0].x;
		VertXY1[1] = C[0].y;
		setMax(VertXY1[0], VertXY1[1]);
		setMin(VertXY1[0], VertXY1[1]);
		glVertex2fv(VertXY1);
	}
	glEnd();
}


//Dibujar lineas

//0 a 45
void CCurveB::drawLineC0a45(int x0, int y0, int x1, int y1) {
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
void CCurveB::drawLineC45a90(int x0, int y0, int x1, int y1) {
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
void CCurveB::drawLineC270a315(int x0, int y0, int x1, int y1) {
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
void CCurveB::drawLineC315a360(int x0, int y0, int x1, int y1) {
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

void CCurveB::drawLine(int x0, int y0, int x1, int y1) {

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