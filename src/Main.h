#include "../headers/glfw3.h"
#include <vector>

#define MIN(a,b) (((a)<(b))?(a):(b))
#define MAX(a,b) (((a)>(b))?(a):(b))

struct pair
{
	int x, y;
};

void pick(int x, int y);

void updateUserInterface();

void display();

void reshape(GLFWwindow *window, int width, int height);

void keyInput(GLFWwindow *window, int key, int scancode, int action, int mods);

void mouseButton(GLFWwindow* window, int button, int action, int mods);

void cursorPos(GLFWwindow* window, double x, double y);

void charInput(GLFWwindow* window, unsigned int scanChar);

void destroy();

bool initGlfw();

bool initUserInterface();

//void swapF(CFigure* a, CFigure* b);

//void eliminar(int picked);

int main(void);