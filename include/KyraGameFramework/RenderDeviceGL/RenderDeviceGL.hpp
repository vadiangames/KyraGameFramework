#ifndef KYRAGAMEFRAMEWORK_RENDERDEVICEGL_RENDERDEVICEGL_HPP
#define KYRAGAMEFRAMEWORK_RENDERDEVICEGL_RENDERDEVICEGL_HPP


#include <KyraGameFramework/GLExtensionLoader/GLExtensionLoader.hpp>
#include <KyraGameFramework/RenderDeviceGL/DLL.hpp>
#include <KyraGameFramework/AbstractRenderDevice/IRenderDevice.hpp>

#include <windows.h>

namespace kyra {

	class KYRA_RENDERDEVICEGL_API RenderDeviceGL : public IRenderDevice {
		
		HWND m_WindowHandle;
		HDC m_DeviceContext;
		HGLRC m_RenderContext;
		
		bool setPixelFormat(HDC hdc);
		
		public:
		RenderDeviceGL();
		virtual ~RenderDeviceGL();
		
		virtual bool create(IWindow& window) final;
		virtual void clear() final;
		virtual void display() final;
		
		void draw(IVertexBuffer& buffer, IProgram& program, IVertexLayout& layout) final;
		void draw(IDrawable& drawable) final;
	};

}

#endif