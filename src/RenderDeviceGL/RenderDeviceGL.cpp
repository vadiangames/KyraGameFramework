
#include <KyraGameFramework/RenderDeviceGL/RenderDeviceGL.hpp>

namespace kyra {
	
	KYRA_RENDERDEVICEGL_API RenderDeviceGL::RenderDeviceGL() {
		
	}
		
	KYRA_RENDERDEVICEGL_API RenderDeviceGL::~RenderDeviceGL() {
		if(m_DeviceContext) {
			ReleaseDC(m_WindowHandle, m_DeviceContext);
			m_DeviceContext = NULL;
		}
		if(m_RenderContext) {
			wglDeleteContext(m_RenderContext);
		}		
	}
	
	bool KYRA_RENDERDEVICEGL_API RenderDeviceGL::setPixelFormat(HDC hdc) {
			
		PIXELFORMATDESCRIPTOR pfd = {
			sizeof(PIXELFORMATDESCRIPTOR),
			1,
			PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL |PFD_DOUBLEBUFFER,
			32,
			0,0,0,0,0,0,
			0,
			0,
			0,
			0,0,0,0,
			24,
			8,
			PFD_MAIN_PLANE,
			0,
			0,0,0
		};
			
		int pixelFormat = ChoosePixelFormat(hdc, &pfd);
		if(pixelFormat == 0) {
			return false;
		}
		
		if(!SetPixelFormat(m_DeviceContext, pixelFormat, &pfd)) {
			return false;
		}
			
		return true;
	}
	
	bool KYRA_RENDERDEVICEGL_API RenderDeviceGL::create(IWindow& window) {
			
		m_WindowHandle = reinterpret_cast<HWND>(window.getHandle());
		m_DeviceContext = GetDC(m_WindowHandle);
			
		if(!setPixelFormat(m_DeviceContext)) {
			return false;
		}
			
		m_RenderContext = wglCreateContext(m_DeviceContext);
		if(!m_RenderContext) {
			return false;
		}
		
		wglMakeCurrent(m_DeviceContext, m_RenderContext);
	
		return true;
	}

	void KYRA_RENDERDEVICEGL_API RenderDeviceGL::clear() {
		glClear(GL_COLOR_BUFFER_BIT);
	}
		
	void KYRA_RENDERDEVICEGL_API RenderDeviceGL::display()  {
		SwapBuffers(m_DeviceContext);
	}
	
	void KYRA_RENDERDEVICEGL_API RenderDeviceGL::draw(IVertexBuffer& buffer, IProgram& program, IVertexLayout& layout) {
		buffer.bind();
		layout.bind();
		program.use();
		glDrawArrays(GL_TRIANGLES,0,3);
	}
	
}