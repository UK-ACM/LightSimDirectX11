#pragma once
#include "Window.h"
#include "WhalenTimer.h"

class App {
public:
	App(int width, int height);
	~App();

	int Run();
private:
	void DoFrame();

private:
	Window wnd;
	WhalenTimer timer;
	std::vector<std::unique_ptr<class Drawable>> drawables;
	static constexpr size_t nDrawables = 180;
};
