#include "Window.h"
#include <sstream>

//Important!: This works if the specified subsystem is Windows, not Console like it usually is

// different from c++ main
int CALLBACK WinMain(
	// a handle to current application instance
	_In_ HINSTANCE hInstance,
	// used to have a handle to previous app, but is usually null now. LEGACY BS
	_In_opt_ HINSTANCE hPrevInstance,
	// cmd line string used as input
	_In_ LPSTR	  lpCmdLine,
	// controls how a window is shown on startup: minimized, shown, maximized, etc
	_In_ int	  nCmdShow )
{
	try {
		Window wnd(640, 480, "Donkey nuts");

		MSG message;
		BOOL gResult;
	
		while ((gResult = GetMessage(&message, nullptr, 0, 0)) > 0) // retrieves the next message. If zero means quit and -1 mean error. All else is a message to handle
		{
			// execute the message
			TranslateMessage(&message);
			DispatchMessage(&message);
			static int i = 0;
			while (!wnd.mouse.IsEmpty()) {
				const auto e = wnd.mouse.Read().value();
				switch (e.GetType()) {
				case Mouse::Event::Type::WheelUp :
					i++;
					{
						std::ostringstream oss;
						oss << "Up: " << i;
						wnd.SetTitle(oss.str());
					}
					break;
				case Mouse::Event::Type::WheelDown:
					i--;
					{
						std::ostringstream oss;
						oss << "Down: " << i;
						wnd.SetTitle(oss.str());
					}
					break;
				}


				
			}
		}

		if (gResult == 0) return int(message.wParam); // return postquitmessage code
		return -1; // error message
	}
	catch (const WhalenException& e) {
		MessageBox(nullptr, e.what(), e.GetType(), MB_OK | MB_ICONEXCLAMATION);
	}
	catch (const std::exception& e) {
		MessageBox(nullptr, e.what(), "Standard Exception", MB_OK | MB_ICONEXCLAMATION);
	}
	catch ( ... ) {
		MessageBox(nullptr, "No Details Available","Unkown Exception", MB_OK | MB_ICONEXCLAMATION);
	}
	return -1;
}