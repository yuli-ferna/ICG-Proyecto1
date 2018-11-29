#include "UserInterface.h"
#include <iostream>
using namespace std;

extern int gWidth, gHeight;

// Global static pointer used to ensure a single instance of the class.
CUserInterface * CUserInterface::mInterface = NULL;

/**
* Creates an instance of the class
*
* @return the instance of this class
*/
CUserInterface * CUserInterface::Instance() 
{
	if (!mInterface)   // Only allow one instance of class to be generated.
		 mInterface = new CUserInterface();
 
   return mInterface;
}

CUserInterface::CUserInterface()
{
	mUserInterface = TwNewBar("Figure");

	TwDefine("Figure refresh = '0.0001f'");
	TwDefine("Figure resizable = false");
	TwDefine("Figure fontresizable = false");
	TwDefine("Figure movable = false");
	TwDefine("Figure visible = false");
	TwDefine("Figure position = '20 20'");
	TwDefine("Figure size = '220 320'");

	TwAddVarRO(mUserInterface, "meshType", TW_TYPE_STDSTRING, &mFigureType, "label='Type' readonly=true");
	TwAddVarRW(mUserInterface, "color", TW_TYPE_COLOR3F, &mFigureColor[0], "label = 'Color'");
	
	
	TwAddSeparator(mUserInterface, "sep1", NULL);
	TwAddVarRW(mUserInterface, "colorR", TW_TYPE_COLOR3F, &mFigureRColor[0], "label = 'Color Relleno'");
	TwAddSeparator(mUserInterface, "sep2", NULL);
	TwAddVarRW(mUserInterface, "relleno", TW_TYPE_BOOLCPP, &fill, "label = 'Relleno'");
	
}

CUserInterface::~CUserInterface()
{
}

void CUserInterface::reshape()
{
	TwWindowSize(gWidth, gHeight);
}

void CUserInterface::show()
{
	TwDefine("Figure visible = true");
}

void CUserInterface::hide()
{
	TwDefine("Figure visible = false");
}

void CUserInterface::setFigureColor(float *color)
{
	mFigureColor[0] = color[0];
	mFigureColor[1] = color[1];
	mFigureColor[2] = color[2];
}

void CUserInterface::setFigureRColor(float * color)
{
	mFigureRColor[0] = color[0];
	mFigureRColor[1] = color[1];
	mFigureRColor[2] = color[2];
}

void CUserInterface::setFigureType(string type)
{
	mFigureType = type;
}

void CUserInterface::setFill(bool f)
{
	fill = f;
}

bool CUserInterface::getFill()
{
	return fill;
}

float* CUserInterface::getFigureColor()
{
	return mFigureColor;
}

float * CUserInterface::getFigureRColor()
{
	return mFigureRColor;
}
