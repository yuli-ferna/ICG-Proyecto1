#include "Main.h"
#include "Line.h"
#include "Quad.h"
#include "Triangle.h"
#include "Circle.h"
#include "Elipse.h"
#include "CurveB.h"
#include "UserInterface.h"

using std::vector;

GLFWwindow *gWindow;
int gWidth, gHeight;
bool gPress;
CUserInterface * userInterface;
vector <CFigure *> figures;
FigureType figureSelected;

int picked;
int nLinea = 0, nPunto = 0;

vector< pair > puntosC;
float ptox, ptoy, ptox2, ptoy2;

void pick(int x, int y)
{
	
	picked = -1;
	userInterface->hide();

	for (unsigned int i = 0; i < figures.size(); i++)
	{
		float *v1 = figures[i]->getVertex(0);
		float *v2 = figures[i]->getVertex(1);
		float max[2];
		float min[2];

		// This should be precalculated

		max[0] = MAX(v1[0], v2[0]);
		max[1] = MAX(v1[1], v2[1]);

		min[0] = MIN(v1[0], v2[0]);
		min[1] = MIN(v1[1], v2[1]);

		if (x >= min[0] && x <= max[0] && y >= min[1] && y <= max[1])
		{
			//Seleccionar
			picked = i;

			userInterface->setFigureColor(figures[picked]->getColor());
			userInterface->setFigureRColor(figures[picked]->getRColor());
			userInterface->show();
			
			int type = figures[picked]->getType();

			if (type == LINE)
				userInterface->setFigureType("Line");
			else if (type == CIRCLE)
				userInterface->setFigureType("Circle");
			else if (type == TRIANGLE)
				userInterface->setFigureType("Triangle");
			else if (type == ELIPSE)
				userInterface->setFigureType("Elipse");
			else if (type == BCURVE)
				userInterface->setFigureType("Bezier Curve");
			else
				userInterface->setFigureType("Quad");

			break;
		}
	}
}

void updateUserInterface()
{
	if (picked > -1)
	{
		float * color = userInterface->getFigureColor();
		float * colorR = userInterface->getFigureRColor();
		bool rell = userInterface->getFill();
		figures[picked]->setColor(color[0], color[1], color[2]);
		figures[picked]->setRColor(colorR[0], colorR[1], colorR[2]);
		figures[picked]->setRelleno(rell);
	}
}

void display()
{
	glClearColor(1.0f, 1.0f, 1.0f, 1.0);
	glClear(GL_COLOR_BUFFER_BIT);

	for (unsigned int i = 0; i < figures.size(); i++)
		figures[i]->display();

	if (picked > -1)
	{
		figures[picked]->boundingBox();
	}
}

void reshape(GLFWwindow *window, int width, int height)
{
	gWidth = width;
	gHeight = height;

	glViewport(0, 0, gWidth, gHeight);

	userInterface->reshape();

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	glOrtho(0, gWidth, 0, gHeight, -1.0f, 1.0f);
}





void keyInput(GLFWwindow *window, int key, int scancode, int action, int mods)
{
	if (TwEventKeyGLFW(key, action))
		return;

	if (action == GLFW_PRESS)
	{
		switch (key)
		{
		case GLFW_KEY_ESCAPE:
			glfwSetWindowShouldClose(window, GL_TRUE);
			break;

		case GLFW_KEY_P:
			figureSelected = NONE;
			userInterface->hide();
			break;

		case GLFW_KEY_L:
			figureSelected = LINE;
			userInterface->hide();
			break;

		case GLFW_KEY_Q:
			figureSelected = QUAD;
			userInterface->hide();
			break;

		case GLFW_KEY_C:
			figureSelected = CIRCLE;
			userInterface->hide();
			break;

		case GLFW_KEY_T:
			figureSelected = TRIANGLE;
			userInterface->hide();
			break;

		case GLFW_KEY_E:
			figureSelected = ELIPSE;
			userInterface->hide();
			break;

		case GLFW_KEY_B:
			figureSelected = BCURVE;
			userInterface->hide();
			break;
		case GLFW_KEY_X:
			if (picked > -1)
			{


				for (int i = picked; i < figures.size() + 1; i++)
				{
					CFigure *aux = figures[i];
					figures[i] = figures[i + 1];
					figures[i + 1] = aux;
				}
				picked = -1;
				figures.pop_back();

			}
			break;

		}

	}
}



void mouseButton(GLFWwindow* window, int button, int action, int mods)
{
	if (TwEventMouseButtonGLFW(button, action))
		return;

	
	double x, y;
	glfwGetCursorPos(gWindow, &x, &y);
	if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS && !gPress)
	{
		float ax = float(x);
		float ay = gHeight - float(y);
		

		if (figureSelected == NONE)
			pick(int(ax), int(ay));
		else if (figureSelected == LINE)
		{
			CLine *line = new CLine();
			line->setVertex(0, ax, ay);
			line->setVertex(1, ax, ay);
			figures.push_back(line);

			gPress = true;
		}
		else if (figureSelected == CIRCLE)
		{
			CCircle *circle = new CCircle();
			circle->setVertex(0, ax, ay);
			circle->setVertex(1, ax, ay);
			figures.push_back(circle);

			gPress = true;
		}
		else if (figureSelected == TRIANGLE)
		{
			if (nLinea == 0) {
				ptox = ax;
				ptoy = ay;
				nLinea++;
			}
			else if(nLinea == 1)
			{
				ptox2 = ax;
				ptoy2 = ay;
				nLinea++;

			}
			else
			{
				CTriangle *triangle = new CTriangle();
				triangle->setVertex(0, ptox, ptoy);
				triangle->setVertex(1,ptox2, ptoy2);
				triangle->setVertex(2, ax, ay);
				figures.push_back(triangle);
				nLinea = 0;
				gPress = true;

			}
		}
		else if (figureSelected == BCURVE)
		{
			if (nPunto < 3) {
				pair aux;
				aux.x = ax;
				aux.y = ay;
				puntosC.push_back(aux);
				nPunto++;

			}
			else
			{
				CCurveB *curve = new CCurveB();
				int length = puntosC.size();
				for (int ii = 0; ii < length; ii++)
				{
					curve->setVertex(ii, puntosC[ii].x, puntosC[ii].y);
				}
				curve->setVertex(length, ax, ay);
				figures.push_back(curve);
				nPunto = 0;
				puntosC.clear();
				gPress = false;

			}
		}
		else if (figureSelected == ELIPSE)
		{
			CElipse *elipse = new CElipse();
			elipse->setVertex(0, ax, ay);
			elipse->setVertex(1, ax, ay);
			figures.push_back(elipse);
			gPress = true;

		}
		else
		{
			CQuad *quad = new CQuad();
			quad->setVertex(0, ax, ay);
			quad->setVertex(1, ax, ay);
			figures.push_back(quad);

			gPress = true;
		}
	}

	if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_RELEASE)
		gPress = false;
}

void cursorPos(GLFWwindow* window, double x, double y)
{
	if (TwEventMousePosGLFW(int(x), int(y)))
		return;

	if (gPress && (figureSelected == TRIANGLE))
	{
		float ax = float(x);
		float ay = gHeight - float(y);

		figures.back()->setVertex(2, ax, ay);
	}
	else if (gPress && (figureSelected == BCURVE))
	{
		float ax = float(x);
		float ay = gHeight - float(y);

		figures.back()->setVertex(3, ax, ay);
	}
	else if (gPress)
	{
		float ax = float(x);
		float ay = gHeight - float(y);

		figures.back()->setVertex(1, ax, ay);

	}

}

void charInput(GLFWwindow* window, unsigned int scanChar)
{
	if (TwEventCharGLFW(scanChar, GLFW_PRESS))
		return;
}

void destroy()
{
	for (unsigned int i = 0; i < figures.size(); i++)
		delete figures[i];

	delete userInterface;

	TwTerminate();
	glfwDestroyWindow(gWindow);
	glfwTerminate();
}

bool initGlfw()
{
	if (!glfwInit())
		return false;

	gWindow = glfwCreateWindow(gWidth, gHeight, "Paint arrechísimo", NULL, NULL);

	if (!gWindow)
	{
		glfwTerminate();
		return false;
	}

	glfwMakeContextCurrent(gWindow);

	const GLFWvidmode * vidMode = glfwGetVideoMode(glfwGetPrimaryMonitor());
	glfwSetWindowPos(gWindow, (vidMode->width - gWidth) >> 1, (vidMode->height - gHeight) >> 1);

	glfwSetWindowSizeCallback(gWindow, reshape);
	glfwSetKeyCallback(gWindow, keyInput);
	glfwSetMouseButtonCallback(gWindow, mouseButton);
	glfwSetCursorPosCallback(gWindow, cursorPos);
	glfwSetCharCallback(gWindow, charInput);

	return true;
}

bool initUserInterface()
{
	if (!TwInit(TW_OPENGL, NULL))
		return false;

	userInterface = CUserInterface::Instance();

	return true;
}

int main(void)
{
	gWidth = 1200;
	gHeight = 680;
	gPress = false;
	figureSelected = LINE;
	picked = -1;

	if (!initGlfw() || !initUserInterface())
		return EXIT_FAILURE;

	reshape(gWindow, gWidth, gHeight);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	while (!glfwWindowShouldClose(gWindow))
	{
		display();

		TwDraw();

		updateUserInterface();

		glfwSwapBuffers(gWindow);

		glfwPollEvents();
	}

	destroy();

	return EXIT_SUCCESS;
}