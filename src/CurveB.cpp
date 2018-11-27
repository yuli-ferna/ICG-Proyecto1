#include "CurveB.h"

CCurveB::CCurveB()
{
}

CCurveB::~CCurveB()
{
}

void CCurveB::display()
{
}
/*

vector<Puntos> C;
void CCurveB::casteljau() {
	glBegin(GL_LINE_STRIP);
	for (double tt = 0.0; tt < 1.0; tt+= paso)
	{
		C = ControlPoints;
		for (int rr = 0; rr < (numeroVertices - 1); rr++)
		{
			for (int ii = 0; ii < length; ii++)
			{
				C[ii].x = float((1.0 - tt) * C[i].x) + float(tt * C[ii + 1].x);
				C[ii].y = float((1.0 - tt) * C[i].y) + float(tt * C[ii + 1].y);
			}
		}
		VertXY1[0] = C[0].x;
		VertXY1[1] = C[0].y;
		glVertex2fv(VertXY1);
	}
	glEnd();
}
*/