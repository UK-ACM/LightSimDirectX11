#include "App.h"
#include <sstream>

App::App()
	: wnd(800, 600, "The fattest window ever")
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
	wnd.Gfx().ClearBuffer(0.2f, 0.2f, 0.2f);
	wnd.Gfx().DrawTestTriangle(timer.Peek(), (wnd.mouse.GetPosX()-400.0f) / 400.0f, -(wnd.mouse.GetPosY()-300.0f) / 300.0f);
	wnd.Gfx().DrawTestTriangle(-timer.Peek(), 0, 0);
	wnd.Gfx().EndFrame();
}