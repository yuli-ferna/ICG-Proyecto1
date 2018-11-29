#pragma once

#include "Figure.h"

class CQuad : public CFigure
{
	bool boundB;
	public:
		CQuad();
		~CQuad();
		void display();
		void boundingBox();
		void rellenoCuadrado(int x0, int y0, int x1, int y1, float mColor[3], float mRColor[3]);
		void pintarContorno(int x0, int y0, int x1, int y1, float mColor[3]);
		void drawLineC0a45(int x0, int y0, int x1, int y1, float color[3]);
		void drawLineC45a90(int x0, int y0, int x1, int y1, float color[3]);
		void PutPixel(int x, int y, float mColor[3]);
};

