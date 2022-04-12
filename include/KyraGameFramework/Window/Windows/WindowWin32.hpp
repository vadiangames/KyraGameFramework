#ifndef KYRAGAMEFRAMEWORK_WINDOW_WINDOWS_WINDOWWIN32_HPP
#define KYRAGAMEFRAMEWORK_WINDOW_WINDOWS_WINDOWWIN32_HPP

#include <KyraGameFramework/Window/IWindow.hpp>
#include <windows.h>

namespace kyra {
	
	//! Window-Implementation for the Windows operating system
	class KYRA_WINDOW_API WindowWin32 : public IWindow {
		
		HWND m_WindowHandle;
		
		//! Callback for the system-events, sends event to the registered SystemEventListeners
		static LRESULT CALLBACK windowProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
				
		//! Registers the window class
		bool registerWindowClass();

		public:
		//! Default constructor
		WindowWin32();
		
		//! Default destructor
		virtual ~WindowWin32();
		
		/** Creates the window
			\param windowSettings The settings who are used for window creation
			\return true if the window is created succesfully */
		virtual bool create(const WindowSettings& windowSettings) final;
		
		/** Checks if the window is open
			\return true if the window is open */
		virtual bool isOpen() const final;
		
		/** Processes the system-events */
		virtual void processEvents() final;
		
		/** Closes the window */
		virtual void close() final;

	};
	
	typedef WindowWin32 Window;
	
}

#endif