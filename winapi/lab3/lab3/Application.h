#ifndef APPLICATION_H
#define APPLICATION_H

#include <Windows.h>

class Application {
	HINSTANCE hInst;
	MSG msg;
public:
	Application(HINSTANCE hInstance);
	int Run();
};

#endif
