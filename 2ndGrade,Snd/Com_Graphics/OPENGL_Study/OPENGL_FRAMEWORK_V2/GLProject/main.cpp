#include <iostream>
#include <ctime>
#include <gl\glut.h>
#include "GLFramework.h"

using namespace std;

namespace {
	CGLFramework framework;
};

int main(int argc, char* argv[]) 
{
	srand(unsigned(time(NULL)));

	// framework initialize
	framework.Initialize();

	// callback function set
	framework.SetReshapeFunc		([] (int w, int h)						 {framework.Reshape(w, h); });
	framework.SetDrawFunc			([] ()									 {framework.drawScene(); });
	framework.SetTimerFunc			([] (int val)							 {framework.Timer(val); });
	framework.SetInputKeyboardFunc	([]	(unsigned char key,int x,int y)		 {framework.InputKeyboard(key,x,y); });
	framework.SetInputMouseFunc		([]	(int button,int state, int x, int y) {framework.InputMouse(button,state, x, y); });


	// framework run
	framework.Run();

	return 0;
}
