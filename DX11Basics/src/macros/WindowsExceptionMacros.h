#pragma once
#include "Window.h"

#define WHWND_EXCEPT(hr) Window::HrException(__LINE__, __FILE__, hr)
#define WHWND_NOGFX_EXCEPT() Window::NoGfxException(__LINE__, __FILE__)
#define WHWND_LAST_EXCEPT() Window::HrException(__LINE__, __FILE__, GetLastError())