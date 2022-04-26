
#include <KyraGameFramework/GLExtensionLoader/GLExtensionLoader.hpp>
#include <KyraGameFramework/RenderDeviceGL/RenderDeviceGL.hpp>
#include <KyraGameFramework/RenderDeviceGL/VertexBuffer.hpp>
#include <KyraGameFramework/RenderDeviceGL/Program.hpp>
#include <KyraGameFramework/RenderDeviceGL/VertexLayout.hpp>

namespace kyra {
	
	KYRA_RENDERDEVICEGL_API RenderDeviceGL::RenderDeviceGL() : VAO(NULL), m_WindowHandle(NULL), m_DeviceContext(NULL) {
		
	}
		
	KYRA_RENDERDEVICEGL_API RenderDeviceGL::~RenderDeviceGL() {
		if(VAO) {
			GL_CHECK(glDeleteVertexArrays(1, &VAO));
		}
		
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
		
		
		if(kyra::GLExtensionLoader::init() == false) {
			std::cout << "[ERROR] GLExtensionLoader::init() failed" << std::endl;
		}
		
		std::cout << "Legacy context created" << std::endl;
		
		/*const int pixelFormatAttribList[] = {
			WGL_DRAW_TO_WINDOW_ARB, GL_TRUE,
			WGL_SUPPORT_OPENGL_ARB, GL_TRUE,
			WGL_PIXEL_TYPE_ARB, GL_TRUE,
			WGL_COLOR_BITS_ARB,32,
			WGL_DEPTH_BITS_ARB,24,
			WGL_STENCIL_BITS_ARB,8,
			0
		};*/
		
		//TODO Check OpenGL Version
		
		std::cout << "Create Context-attributes" << std::endl;
		int attributes[] = {
			WGL_CONTEXT_MAJOR_VERSION_ARB, 3,
			WGL_CONTEXT_MINOR_VERSION_ARB, 3,
			WGL_CONTEXT_FLAGS_ARB,WGL_CONTEXT_CORE_PROFILE_BIT_ARB,
			0
		};
		
		std::cout << "wglCreateContextAttribsARB: "  << wglCreateContextAttribsARB << std::endl;
		
		std::cout << "Create modern context" << std::endl;
		HGLRC modernContext =  wglCreateContextAttribsARB( m_DeviceContext, 0, attributes);
		std::cout << "New context " << modernContext <<  std::endl;
		
		if(modernContext) {
			wglMakeCurrent(NULL,NULL);
			wglDeleteContext(m_RenderContext);
			m_RenderContext = modernContext;
			wglMakeCurrent(m_DeviceContext, m_RenderContext);
			std::cout << "Switch to modern context" << std::endl;
		}
			
		GL_CHECK(glViewport(0, 0, window.getWidth(), window.getHeight()));
		GL_CHECK(glEnable(GL_BLEND));
		GL_CHECK(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));
		GL_CHECK(glGenVertexArrays(1, &VAO));
		GL_CHECK(glBindVertexArray(VAO));
		
		return true;
	}
	
	
	IVertexBuffer::Ptr KYRA_RENDERDEVICEGL_API RenderDeviceGL::createVertexBuffer() {
		return IVertexBuffer::Ptr(new VertexBuffer());
	}
	
	IProgram::Ptr KYRA_RENDERDEVICEGL_API RenderDeviceGL::createProgram() {
		return IProgram::Ptr(new Program());
	}
	
	IVertexLayout::Ptr KYRA_RENDERDEVICEGL_API RenderDeviceGL::createVertexLayout() {
		return IVertexLayout::Ptr(new VertexLayout());
	}

	void KYRA_RENDERDEVICEGL_API RenderDeviceGL::clear() {
		glClear(GL_COLOR_BUFFER_BIT);
	}
		
	void KYRA_RENDERDEVICEGL_API RenderDeviceGL::display()  {
		SwapBuffers(m_DeviceContext);
	}
	
	IProgram::Ptr KYRA_RENDERDEVICEGL_API RenderDeviceGL::createProgramFromFile( const std::string& id, const std::filesystem::path& vertexShader, const std::filesystem::path& fragmentShader ) {
		if(m_ProgramMap.find(id) == m_ProgramMap.end()) {
			IProgram::Ptr program = IProgram::Ptr(new Program());
			program->linkFromFile(vertexShader,fragmentShader);
			m_ProgramMap[id] = program;
		}
		return m_ProgramMap[id];
	}
	
	IProgram::Ptr KYRA_RENDERDEVICEGL_API RenderDeviceGL::createProgramFromMemory(const std::string& id, const std::string& vertexShader, const std::string& fragmentShader ) {
		if(m_ProgramMap.find(id) == m_ProgramMap.end()) {
			IProgram::Ptr program = IProgram::Ptr(new Program());
			program->linkFromMemory(vertexShader,fragmentShader);
			m_ProgramMap[id] = program;
		}
		return m_ProgramMap[id];		
	}
		
	IProgram::Ptr KYRA_RENDERDEVICEGL_API RenderDeviceGL::createInternalProgramFromFile(InternalProgramType type, const std::filesystem::path& vertexShader, const std::filesystem::path& fragmentShader ) {
		if(m_InternalProgramMap.find(type) == m_InternalProgramMap.end()) {
			IProgram::Ptr program = IProgram::Ptr(new Program());
			program->linkFromFile(vertexShader,fragmentShader);
			m_InternalProgramMap[type] = program;
		}
		return m_InternalProgramMap[type];

	}
	
	IProgram::Ptr KYRA_RENDERDEVICEGL_API RenderDeviceGL::createInternalProgramFromMemory(InternalProgramType type, const std::string& vertexShader, const std::string& fragmentShader ) {
		if(m_InternalProgramMap.find(type) == m_InternalProgramMap.end()) {
			IProgram::Ptr program = IProgram::Ptr(new Program());
			program->linkFromMemory(vertexShader,fragmentShader);
			m_InternalProgramMap[type] = program;
		}
		return m_InternalProgramMap[type];
	}
	
	IProgram::Ptr KYRA_RENDERDEVICEGL_API RenderDeviceGL::getProgram(const std::string& id) {
		if(m_ProgramMap.find(id) == m_ProgramMap.end()) {
			std::cout << "[WARN] Can not find program " << id << std::endl;
			return IProgram::Ptr(nullptr);
		}
		return m_ProgramMap[id];
	}
	
	IProgram::Ptr KYRA_RENDERDEVICEGL_API RenderDeviceGL::getInternalProgram(InternalProgramType type) {
		if(m_InternalProgramMap.find(type) == m_InternalProgramMap.end()) {
			if(type == InternalProgramType::SPRITE) {
				std::cout << "[WARN] Can not find internal program SPRITE" << std::endl;
			} else if(type == InternalProgramType::TEXT) {
				std::cout << "[WARN] Can not find internal program TEXT" << std::endl;
			}
			return IProgram::Ptr(nullptr);
		}
		return m_InternalProgramMap[type];
	}
		
	
	void KYRA_RENDERDEVICEGL_API RenderDeviceGL::draw(IVertexBuffer& buffer, IProgram& program, IVertexLayout& layout) {
		buffer.bind();
		layout.bind();
		program.use();
		if(buffer.getPrimitiveType() == PrimitiveType::TRIANGLES) {
			glDrawArrays(GL_TRIANGLES,0,buffer.getElementCount());
		} else {
			std::cout << "[ERROR] Unsupported primitive type" << std::endl;
		}
	}
	
	
	void KYRA_RENDERDEVICEGL_API RenderDeviceGL::draw(IVertexBuffer::Ptr buffer, IProgram::Ptr program, IVertexLayout::Ptr layout) {
		if(!buffer) {
			std::cout << "[WARN] VertexBuffer is not initialized!" << std::endl;
		}
		if(!program) {
			std::cout << "[WARN] Program is not initialized!" << std::endl;
		}
		if(!layout) {
			std::cout << "[WARN] VertexLayout is not initialized!" << std::endl;
		}
		draw(*buffer,*program,*layout);
	}
	
	void  KYRA_RENDERDEVICEGL_API RenderDeviceGL::draw(IDrawable& drawable) {
		drawable.draw(*this);
	}
	
	void  KYRA_RENDERDEVICEGL_API RenderDeviceGL::draw(IDrawable::Ptr drawable) {
		drawable->draw(*this);
	}
	
}