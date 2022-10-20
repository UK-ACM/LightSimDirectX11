#pragma once
#include "Window.h"
#include "WhalenTimer.h"
#include "ImguiManager.h"
#include "Camera.h"
#include "PointLight.h"

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
	ImguiManager imgui;
	Window wnd;
	WhalenTimer timer;
	Camera cam;
	PointLight light;
	std::vector<std::unique_ptr<class Drawable>> drawables;
	static constexpr size_t nDrawables = 180;
	float speed_factor = 1.0f;
};
