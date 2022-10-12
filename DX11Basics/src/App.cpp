#include "App.h"
#include <sstream>

App::App()
	: wnd(640, 480, "Donkey Fart Box")
{}

// run one loop of message processing
int App::Run() {
	while (true) {
		if (const auto ecode = Window::ProcessMessages()) {
			return ecode.value();
		}
		Sleep(1); // temporary fix for buggy window when setting title repeatedly: REMOVE when not needed
		DoFrame();
	}

}

void App::DoFrame() {
	const float c = sin(timer.Peek()) / 2.0f + 0.5f;
	wnd.Gfx().ClearBuffer(c, c, 1.0f);
	wnd.Gfx().DrawTestTriangle();
	wnd.Gfx().EndFrame();
}