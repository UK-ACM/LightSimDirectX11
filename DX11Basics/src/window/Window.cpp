#include "Window.h"
#include "WindowsExceptionMacros.h"
#include <sstream>
#include "imgui_impl_win32.h"

Window::WindowClass Window::WindowClass::wndClass;

Window::WindowClass::WindowClass() noexcept 
	// instatiates the instance handle without needing to pass an arg
	: hInst(GetModuleHandle(nullptr))
{
	// register window class
	WNDCLASSEX windowClass = { 0 };
	windowClass.cbSize = sizeof(windowClass);
	// this style gives each window their own device context
	windowClass.style = CS_OWNDC;
	windowClass.lpfnWndProc = HandleMsgSetup; // using default windows settings
	windowClass.cbClsExtra = 0;
	windowClass.cbWndExtra = 0;
	windowClass.hInstance = GetInstance();
	windowClass.hIcon = nullptr;
	windowClass.hCursor = nullptr;
	windowClass.hbrBackground = nullptr;
	windowClass.lpszMenuName = nullptr;
	windowClass.lpszClassName = GetName(); // long str of our windows class name to be used later
	windowClass.hIconSm = nullptr;
	RegisterClassEx(&windowClass);
}

Window::WindowClass::~WindowClass() {
	UnregisterClass(GetName(), GetInstance());
}

const char* Window::WindowClass::GetName() noexcept {
	return wndClassName;
}

HINSTANCE Window::WindowClass::GetInstance() noexcept {
	return wndClass.hInst;
}

Window::Window(int width, int height, const char* name)  
	: width(width), height(height)
{
	// adjusts rect var to be the desired size of the client region given the client instead of the entire window region
	RECT wr;
	wr.left = 100;
	wr.right = wr.left + width;
	wr.top = 100;
	wr.bottom = wr.top + height;
	if (!AdjustWindowRect(&wr, WS_CAPTION | WS_MINIMIZEBOX | WS_SYSMENU, FALSE)) {
		throw WHWND_LAST_EXCEPT();
	};

	// exception testing
	//throw WHWND_EXCEPT(ERROR_ARENA_TRASHED);

	hWnd = CreateWindow(
		WindowClass::GetName(), name,
		WS_CAPTION | WS_MINIMIZEBOX | WS_SYSMENU,
		CW_USEDEFAULT, CW_USEDEFAULT, wr.right - wr.left, wr.bottom - wr.top,
		nullptr, nullptr, WindowClass::GetInstance(), this
	);

	if (hWnd == nullptr) {
		throw WHWND_LAST_EXCEPT();
	}

	// display window once created, default as hidden
	ShowWindow(hWnd, SW_SHOWDEFAULT);

	ImGui_ImplWin32_Init(hWnd);

	// create Graphics object
	pGfx = std::make_unique<Graphics>(hWnd, width, height);
}

Window::~Window() {
	ImGui_ImplWin32_Shutdown();
	DestroyWindow(hWnd);
}

void Window::SetTitle(const std::string& title) {
	if (!SetWindowText(hWnd, title.c_str())) {
		throw WHWND_LAST_EXCEPT();
	}

}

std::optional<int> Window::ProcessMessages() {
	MSG message;
	while (PeekMessage(&message, nullptr, 0, 0, PM_REMOVE)) // retrieves the next message. If zero means quit and -1 mean error. All else is a message to handle
	{
		if (message.message == WM_QUIT)
			return (int)message.wParam;
		// execute the message
		TranslateMessage(&message);
		DispatchMessage(&message);
	}

	return {};
}

LRESULT CALLBACK Window::HandleMsgSetup(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) noexcept {
	if (msg == WM_NCCREATE) {
		// extract ptr into a window class
		const CREATESTRUCTW* const pCreate = reinterpret_cast<CREATESTRUCTW*>(lParam);
		Window* const pWnd = static_cast<Window*>(pCreate->lpCreateParams);

		// store WINAPI user data as window ptr
		SetWindowLongPtr(hWnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(pWnd));

		// set message proc to normal handler now that setup is done
		SetWindowLongPtr(hWnd, GWLP_WNDPROC, reinterpret_cast<LONG_PTR>(&Window::HandleMsgThunk));

		// forward message to internal class handler
		return pWnd->HandleMsg(hWnd, msg, wParam, lParam);

	}
	return DefWindowProc(hWnd, msg, wParam, lParam);
}

LRESULT CALLBACK Window::HandleMsgThunk(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) noexcept {
	// retrieve the user data which contains our member function to handle msgs
	Window* const pWnd = reinterpret_cast<Window*>(GetWindowLongPtr(hWnd, GWLP_USERDATA));
	return pWnd->HandleMsg(hWnd, msg, wParam, lParam);
}

LRESULT Window::HandleMsg(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) noexcept {
	if (ImGui_ImplWin32_WndProcHandler(hWnd, msg, wParam, lParam)) {
		return true;
	}
	const auto& imio = ImGui::GetIO();

	// special message handling aside from default procedure
	switch (msg) {
	// quit application when closing a window.
	case WM_CLOSE:
		PostQuitMessage(0); // create the quit message
		return 0;
		break;

	// clear keyboard state when losing focus on the window
	case WM_KILLFOCUS:
		kbd.ClearState();
		break;

	// Keyboard checking
	case WM_SYSKEYDOWN: // track the alt and F10 keys
	case WM_KEYDOWN:
		if (imio.WantCaptureKeyboard) break;
		if (!(lParam & 0x40000000) || kbd.AutorepeatIsEnabled()) { // only updates is autorepeat is enabled or bit 30 is not set (bit that is 1 if last message was same key)
			kbd.OnKeyPressed(static_cast<unsigned char>(wParam));
		}
		break;
	case WM_SYSKEYUP:
	case WM_KEYUP:
		if (imio.WantCaptureKeyboard) break;
		kbd.OnKeyReleased(static_cast<unsigned char>(wParam));
		break;
	case WM_CHAR:
		if (imio.WantCaptureKeyboard) break;
		kbd.OnChar(static_cast<unsigned char>(wParam));
		break;

	// Mouse Checking Messages
	case WM_MOUSEMOVE: {
		if (imio.WantCaptureKeyboard) break;
		const POINTS pt = MAKEPOINTS(lParam);
		//check if mouse is in client region
		if (pt.x >= 0 && pt.x < width && pt.y >= 0 && pt.y < height) {
			mouse.OnMouseMove(pt.x, pt.y);
			if (!mouse.IsInWindow()) {
				SetCapture(hWnd);
				mouse.OnMouseEnter();
			}
		}
		// mouse is not in client window, maintain capture
		else {
			if (wParam & (MK_LBUTTON | MK_RBUTTON)) {
				mouse.OnMouseMove(pt.x, pt.y);
			}
			else {
				ReleaseCapture();
				mouse.OnMouseLeave();
			}
		}
		
		break;
	}
	case WM_LBUTTONDOWN: {
		if (imio.WantCaptureKeyboard) break;
		const POINTS pt = MAKEPOINTS(lParam);
		mouse.OnLeftPressed(pt.x, pt.y);
		break; 
	}
		
	case WM_RBUTTONDOWN: {
		if (imio.WantCaptureKeyboard) break;
		const POINTS pt = MAKEPOINTS(lParam);
		mouse.OnRightPressed(pt.x, pt.y);
		break;
	}
		
	case WM_LBUTTONUP: {
		if (imio.WantCaptureKeyboard) break;
		const POINTS pt = MAKEPOINTS(lParam);
		mouse.OnLeftReleased(pt.x, pt.y);
		break;
	}
		
	case WM_RBUTTONUP: {
		if (imio.WantCaptureKeyboard) break;
		const POINTS pt = MAKEPOINTS(lParam);
		mouse.OnRightReleased(pt.x, pt.y);
		break;
	}
		
	case WM_MOUSEWHEEL: {
		if (imio.WantCaptureKeyboard) break;
		const POINTS pt = MAKEPOINTS(lParam);
		// get the wheel delta and send to mouse to calculate how many multiples of 120 have occured 
		mouse.OnWheelDelta(pt.x, pt.y, GET_WHEEL_DELTA_WPARAM(wParam));
		break;
	}
		
	}
	return DefWindowProc(hWnd, msg, wParam, lParam);
}

Window::HrException::HrException(int line, const char* file, HRESULT hr) noexcept
	: Exception(line, file), hr(hr)
{}

const char* Window::HrException::what() const noexcept  {
	std::ostringstream oss;
	oss << GetType() << std::endl 
		<< "[Error Code] " << GetErrorCode() << std::endl
		<< "[Description] " << GetErrorString() << std::endl
		<< GetOriginString();
	whatBuffer = oss.str();
	return whatBuffer.c_str();
}

const char* Window::HrException::GetType() const noexcept  {
	return "Whalen Window Exception";
}

std::string Window::Exception::TranslateErrorCode(HRESULT hr) noexcept {
	char* pMsgBuf = nullptr;
	DWORD nMsgLen = FormatMessage(
		FORMAT_MESSAGE_ALLOCATE_BUFFER |
		FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
		nullptr, hr, MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
		reinterpret_cast<LPSTR>(&pMsgBuf), 0, nullptr
	);
	if (nMsgLen == 0) {
		return "Unidentified error code";
	}
	std::string errorString = pMsgBuf;
	LocalFree(pMsgBuf);
	return errorString;
}

HRESULT Window::HrException::GetErrorCode() const noexcept {
	return hr;
}

std::string Window::HrException::GetErrorString() const noexcept {
	return TranslateErrorCode(hr);
}

Graphics& Window::Gfx() {
	if (!pGfx) throw WHWND_NOGFX_EXCEPT();
	return *pGfx;
}

const char* Window::NoGfxException::GetType() const noexcept
{
	return "Whalen No Graphics Exception";
}
