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
