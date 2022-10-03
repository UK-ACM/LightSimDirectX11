#pragma once
#include "Window.h"
#include "WhalenTimer.h"

class App {
public:
	App();

	int Run();
private:
	void DoFrame();

private:
	Window wnd;
	WhalenTimer timer;
};