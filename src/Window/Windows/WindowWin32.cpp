
#include <KyraGameFramework/Window/Windows/WindowWin32.hpp>
#include <iostream>
#include <windowsx.h>

namespace kyra {
	
	KYRA_WINDOW_API WindowWin32::WindowWin32() : m_WindowHandle(NULL) {
	
	}
		
	KYRA_WINDOW_API WindowWin32::~WindowWin32() {
			
		if(m_WindowHandle) {
			DestroyWindow(m_WindowHandle);
		}
		
		UnregisterClassW(L"KYRA_WINDOW_CLASS", GetModuleHandle(NULL) );
	}
	
	LRESULT CALLBACK KYRA_WINDOW_API WindowWin32::windowProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) {
		
			SystemEventDispatcher* dispatcher = reinterpret_cast<SystemEventDispatcher*>(GetWindowLongPtr( hWnd, GWLP_USERDATA));
			if(dispatcher) {
				switch(msg) {
					case WM_CLOSE:
						dispatcher->sendOnCloseEvent();
					return 0;
					case WM_SIZE:
						dispatcher->sendOnResizeEvent(LOWORD(lParam),HIWORD(lParam));
					return 0;
					case WM_KILLFOCUS:
						dispatcher->sendOnFocusLostEvent();
					return 0;
					case WM_SETFOCUS:
						dispatcher->sendOnFocusGainedEvent();
					return 0;
					case WM_KEYUP:
						dispatcher->sendOnKeyReleasedEvent(wParam);
					return 0;
					case WM_KEYDOWN:
						dispatcher->sendOnKeyPressedEvent(wParam);
					return 0;
					case WM_MOUSEMOVE:
						dispatcher->sendOnMouseMovedEvent(GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam));
					return 0;
				}
			}
			return DefWindowProcW(hWnd, msg, wParam, lParam);
	}
		
	
	bool KYRA_WINDOW_API WindowWin32::registerWindowClass() {
			
		WNDCLASSEXW wcex;
		ZeroMemory(&wcex, sizeof(WNDCLASSEXW));
		wcex.cbSize = sizeof(WNDCLASSEXW);
		wcex.style  = CS_HREDRAW | CS_VREDRAW;
		wcex.hInstance = GetModuleHandle(NULL);
		wcex.lpfnWndProc = WindowWin32::windowProc;
		wcex.lpszClassName = L"KYRA_WINDOW_CLASS";
		
		if(!RegisterClassExW(&wcex)) {
			return false;
		}
		
		return true;
	}

		
	bool KYRA_WINDOW_API WindowWin32::create(const WindowSettings& windowSettings) {
		if(!registerWindowClass()) {
			return false;
		}
		
		int width = windowSettings.width;
		int height = windowSettings.height;
		
		//Adjust the window size ( Solves the rendering behind title-bar-problem )
		RECT rect;
		rect.left = 0;
		rect.right = windowSettings.width;
		rect.top = 0;
		rect.bottom = windowSettings.height;
		AdjustWindowRect(&rect, WS_OVERLAPPEDWINDOW, false);
		width = (rect.right - rect.left);
		height = (rect.bottom - rect.top);
			
		m_WindowHandle = CreateWindowW( L"KYRA_WINDOW_CLASS", 
										windowSettings.title.c_str(),
										WS_OVERLAPPEDWINDOW,
										CW_USEDEFAULT, 
										CW_USEDEFAULT, 
										width, 
										height, 
										NULL,
										NULL, 
										GetModuleHandle(NULL), 
										NULL);
	
		if(!m_WindowHandle) {
			return false;
		}
		
		SetWindowLongPtr( m_WindowHandle, GWLP_USERDATA, reinterpret_cast<LONG_PTR>( this ) );
		UpdateWindow(m_WindowHandle);
		ShowWindow(m_WindowHandle, SW_SHOW);

		return true;
	}
		
	bool KYRA_WINDOW_API WindowWin32::isOpen() const {
		return IsWindow(m_WindowHandle);
	}
		
	void KYRA_WINDOW_API WindowWin32::processEvents() {
		MSG msg;
		while(PeekMessageW(&msg, m_WindowHandle, 0,0, PM_REMOVE)) {
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}
		
	void KYRA_WINDOW_API WindowWin32::close() {
		DestroyWindow(m_WindowHandle);
		m_WindowHandle = NULL;
	}
	
	void* KYRA_WINDOW_API WindowWin32::getHandle() const {
		return reinterpret_cast<void*>(m_WindowHandle);
	}
	
		
	Rect KYRA_WINDOW_API WindowWin32::getWindowRect() const {
		RECT window_rectangle;
		GetWindowRect(m_WindowHandle, &window_rectangle);
		Rect rectangle;
		rectangle.x = window_rectangle.top;
		rectangle.y = window_rectangle.left;
		rectangle.width = window_rectangle.right - window_rectangle.left;
		rectangle.height = window_rectangle.bottom - window_rectangle.top; 
		return rectangle;
	}
		
	Rect KYRA_WINDOW_API WindowWin32::getClientRect() const {
		RECT window_rect;
		GetWindowRect(m_WindowHandle, &window_rect);
		RECT client_rectangle;
		GetClientRect(m_WindowHandle, &client_rectangle);
		Rect rectangle;
		rectangle.x = client_rectangle.left;
		rectangle.y = (window_rect.bottom - window_rect.top) - client_rectangle.bottom;
		rectangle.width =  client_rectangle.right - client_rectangle.left;
		rectangle.height =client_rectangle.bottom - client_rectangle.top; 
		return rectangle;		
	}
	
	
}