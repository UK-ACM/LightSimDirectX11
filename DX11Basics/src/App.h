#pragma once
#include "Window.h"
#include "WhalenTimer.h"

class App {
public:
	App(int width, int height);
	~App();

	// main loop for both the window and DirectX code. Calls DoFrame()
	int Run();
private:
	// execute a single frame
	void DoFrame();

private:
	Window wnd;
	WhalenTimer timer;
	std::vector<std::unique_ptr<class Drawable>> drawables;
	static constexpr size_t nDrawables = 180;
};
