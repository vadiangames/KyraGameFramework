#ifndef KYRAGAMEFRAMEWORK_RENDERDEVICEGL_RENDERDEVICEGL_HPP
#define KYRAGAMEFRAMEWORK_RENDERDEVICEGL_RENDERDEVICEGL_HPP

#include <KyraGameFramework/RenderDeviceGL/DLL.hpp>
#include <KyraGameFramework/AbstractRenderDevice/IRenderDevice.hpp>

#include <windows.h>
#include <GL/gl.h>
#include <GL/glext.h>
#include <GL/wgl.h>
#include <GL/wglext.h>

namespace kyra {

	class KYRA_RENDERDEVICEGL_API RenderDeviceGL : public IRenderDevice {
		
		HWND m_WindowHandle;
		HDC m_DeviceContext;
		HGLRC m_RenderContext;
		
		bool setPixelFormat(HDC hdc);
		
		public:
		RenderDeviceGL();
		virtual ~RenderDeviceGL();
		
		virtual bool create(IWindow& window);
		virtual void clear();
		virtual void display();
	};

}

#endif