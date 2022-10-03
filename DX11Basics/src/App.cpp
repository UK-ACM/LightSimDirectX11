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
		DoFrame();
	}

}

void App::DoFrame() {
	const float t = timer.Peek();
	std::ostringstream oss;
	oss << "Time elapsed: " << std::fixed << std::setprecision(1) << t << "s";
	//wnd.SetTitle(oss.str());
}