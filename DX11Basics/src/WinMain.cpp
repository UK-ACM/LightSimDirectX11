#include "App.h"

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
		// creates an App with given size and runs the main application loop
		return App{1200, 800}.Run();
		
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