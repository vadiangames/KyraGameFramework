#ifndef KYRAGAMEFRAMEWORK_WINDOW_IWINDOW_HPP
#define KYRAGAMEFRAMEWORK_WINDOW_IWINDOW_HPP

#include <KyraGameFramework/Window/DLL.hpp>
#include <KyraGameFramework/Window/SystemEventDispatcher.hpp>
#include <string>

namespace kyra {
	
	//! Contains all settings for window creation
	typedef struct {
		uint32_t width; ///< The width of the window
		uint32_t height; ///< The height of the window
		std::wstring title; ///< The title of the window
	}WindowSettings;
	
	typedef struct {
		uint32_t x;	///< X coordinate of the rectangle
		uint32_t y; ///< Y ccordinate of the rectangle
		uint32_t width; ///< Width of the rectangle
		uint32_t height; ///< Height of the rectangle
	}Rect;
	
	//! Abstract class for window implementations
	class KYRA_WINDOW_API IWindow : public SystemEventDispatcher {
				
		public:
		//! Default constructor
		IWindow();
		
		//! Default destructor
		virtual ~IWindow();
		
		/** Creates the window
			\param windowSettings The settings who are used for window creation
			\return true if the window is created succesfully */
		virtual bool create(const WindowSettings& windowSettings) = 0;
		
		/** Checks if the window is open
			\return true if the window is open */
		virtual bool isOpen() const = 0;
		
		/** Processes the system-events */
		virtual void processEvents() = 0;
		
		/** Closes the window */
		virtual void close() = 0;
		
		/** Return the window-handle */
		virtual size_t getHandle() const = 0;
		
		virtual Rect getWindowRect() const = 0;
		
		virtual Rect getClientRect() const = 0;
		
		/// \todo Returns the height of the titleBar
		// virtual float getTitleBarWidth() const = 0;
		
	};
	
}

#endif