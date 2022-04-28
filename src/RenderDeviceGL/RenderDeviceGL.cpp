
#include <KyraGameFramework/GLExtensionLoader/GLExtensionLoader.hpp>
#include <KyraGameFramework/RenderDeviceGL/RenderDeviceGL.hpp>
#include <KyraGameFramework/RenderDeviceGL/VertexBuffer.hpp>
#include <KyraGameFramework/RenderDeviceGL/Program.hpp>
#include <KyraGameFramework/RenderDeviceGL/Texture.hpp>
#include <KyraGameFramework/RenderDeviceGL/Sprite.hpp>
#include <KyraGameFramework/RenderDeviceGL/VertexLayout.hpp>

namespace kyra {
	
	KYRA_RENDERDEVICEGL_API RenderDeviceGL::RenderDeviceGL() :  m_WindowHandle(NULL), m_DeviceContext(NULL), VAO(0), m_Window(nullptr) {
		
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
			std::cout << "[ERROR] Can not choose pixelFormat" << std::endl;
			return false;
		}
		
		if(!SetPixelFormat(m_DeviceContext, pixelFormat, &pfd)) {
			std::cout << "[ERROR] Can not set pixelFormat" << std::endl;
			return false;
		}
			
		return true;
	}
	
	bool KYRA_RENDERDEVICEGL_API RenderDeviceGL::create(IWindow& window) {
			
		m_WindowHandle = reinterpret_cast<HWND>(window.getHandle());
		m_DeviceContext = GetDC(m_WindowHandle);
		m_Window = &window;
		
		if(!setPixelFormat(m_DeviceContext)) {
			return false;
		}
			
		m_RenderContext = wglCreateContext(m_DeviceContext);
		if(!m_RenderContext) {
			std::cout << "[ERROR] Can not create OpenGL-Context" << std::endl;
			return false;
		}
		
		wglMakeCurrent(m_DeviceContext, m_RenderContext);
		
		
		if(kyra::GLExtensionLoader::init() == false) {
			std::cout << "[ERROR] GLExtensionLoader::init() failed" << std::endl;
		}
		
		int attributes[] = {
			WGL_CONTEXT_MAJOR_VERSION_ARB, 3,
			WGL_CONTEXT_MINOR_VERSION_ARB, 3,
			WGL_CONTEXT_FLAGS_ARB,WGL_CONTEXT_CORE_PROFILE_BIT_ARB,
			0
		};
		
		HGLRC modernContext =  wglCreateContextAttribsARB( m_DeviceContext, 0, attributes);
		
		if(modernContext) {
			wglMakeCurrent(NULL,NULL);
			wglDeleteContext(m_RenderContext);
			m_RenderContext = modernContext;
			wglMakeCurrent(m_DeviceContext, m_RenderContext);
		}
		
		Rect clientRect = window.getClientRect();
		GL_CHECK(glViewport(clientRect.x, clientRect.y, clientRect.width, clientRect.height));
		GL_CHECK(glEnable(GL_BLEND));
		GL_CHECK(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));
		GL_CHECK(glGenVertexArrays(1, &VAO));
		GL_CHECK(glBindVertexArray(VAO));
		
		return true;
	}
	
	ISprite::Ptr KYRA_RENDERDEVICEGL_API RenderDeviceGL::createSprite(ITexture::Ptr texture) {
		ISprite::Ptr sprite = ISprite::Ptr(new Sprite());
		sprite->create(*this);
		sprite->setTexture(texture);
		return sprite;
	}
	
	ITexture::Ptr KYRA_RENDERDEVICEGL_API RenderDeviceGL::createTexture(const std::filesystem::path& path) {
		ITexture::Ptr texture = ITexture::Ptr(new Texture());
		texture->loadFromFile(path);
		return texture;
	}
	
	IVertexBuffer::Ptr KYRA_RENDERDEVICEGL_API RenderDeviceGL::createVertexBuffer() {
		return IVertexBuffer::Ptr(new VertexBuffer());
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
	
	IProgram::Ptr KYRA_RENDERDEVICEGL_API RenderDeviceGL::createProgramFromFile( const std::filesystem::path& vertexShader, const std::filesystem::path& fragmentShader ) {
		IProgram::Ptr program = IProgram::Ptr(new Program());
		program->linkFromFile(vertexShader,fragmentShader);
		return program;
	}
	
	IProgram::Ptr KYRA_RENDERDEVICEGL_API RenderDeviceGL::createProgramFromMemory( const std::string& vertexShader, const std::string& fragmentShader ) {
		IProgram::Ptr program = IProgram::Ptr(new Program());
		program->linkFromMemory(vertexShader,fragmentShader);
		return program;
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
		buffer->bind();
		layout->bind();
		program->use();
		
		if(buffer->getPrimitiveType() == PrimitiveType::TRIANGLES) {
			glDrawArrays(GL_TRIANGLES,0,buffer->getElementCount());
		}
	}
	
	void  KYRA_RENDERDEVICEGL_API RenderDeviceGL::draw(IDrawable::Ptr drawable) {
		drawable->draw(*this);
	}
	
	void  KYRA_RENDERDEVICEGL_API RenderDeviceGL::draw(IDrawable& drawable) {
		drawable.draw(*this);
	}
	
	Rect KYRA_RENDERDEVICEGL_API RenderDeviceGL::getClientRect() const {
		return m_Window->getClientRect();
	}
	
}