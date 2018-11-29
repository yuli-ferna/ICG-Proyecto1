#pragma once

#include "../headers/AntTweakBar.h"
#include <iostream>
#include <string>

using std::string;

//Singleton user interface class

class CUserInterface
{
private:
	static CUserInterface * mInterface; //Holds the instance of the class
	TwBar *mUserInterface;
	float mFigureColor[3];
	float mFigureRColor[3];
	string mFigureType;
	bool fill;

public:
	///Method to obtain the only instance of the calls
	static CUserInterface * Instance();
	~CUserInterface();
	void reshape();
	void show();
	void hide();
	void setFigureColor(float *color);
	void setFigureRColor(float *color);
	void setFigureType(string type);
	void setFill(bool f);
	bool getFill();
	float* getFigureColor();
	float* getFigureRColor();


private:
	///Private constructor
	CUserInterface(); 
};