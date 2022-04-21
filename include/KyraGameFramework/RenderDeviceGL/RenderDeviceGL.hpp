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
		
		
		virtual IVertexBuffer::Ptr createVertexBuffer() final;
		virtual IProgram::Ptr createProgram() final;
		virtual IVertexLayout::Ptr createVertexLayout() final;
		
		virtual bool create(IWindow& window) final;
		virtual void clear() final;
		virtual void display() final;
		
		void draw(IVertexBuffer& buffer, IProgram& program, IVertexLayout& layout) final;
		void draw(IVertexBuffer::Ptr buffer, IProgram::Ptr program, IVertexLayout::Ptr layout);
		void draw(IDrawable& drawable) final;
		void draw(IDrawable::Ptr drawable) final;
	};

}

#endif