#ifndef KYRAGAMEFRAMEWORK_RENDERDEVICEGL_RENDERDEVICEGL_HPP
#define KYRAGAMEFRAMEWORK_RENDERDEVICEGL_RENDERDEVICEGL_HPP


#include <KyraGameFramework/GLExtensionLoader/GLExtensionLoader.hpp>
#include <KyraGameFramework/RenderDeviceGL/DLL.hpp>
#include <KyraGameFramework/AbstractRenderDevice/IRenderDevice.hpp>

#include <windows.h>
#include <map>

namespace kyra {

	class KYRA_RENDERDEVICEGL_API RenderDeviceGL : public IRenderDevice {
		
		HWND m_WindowHandle;
		HDC m_DeviceContext;
		HGLRC m_RenderContext;
		
		IWindow* m_Window;
		
		unsigned int VAO;
		
		bool setPixelFormat(HDC hdc);
		
		public:
		RenderDeviceGL();
		virtual ~RenderDeviceGL();
				
		virtual ITexture::Ptr createTexture(const std::filesystem::path& path) final;
		virtual ISprite::Ptr createSprite(ITexture::Ptr texture) final;
		
		virtual IProgram::Ptr createProgramFromFile( const std::filesystem::path& vertexShader, const std::filesystem::path& fragmentShader ) final;
		virtual IProgram::Ptr createProgramFromMemory( const std::string& vertexShader, const std::string& fragmentShader ) final;
				
		virtual IVertexBuffer::Ptr createVertexBuffer() final;
		virtual IVertexLayout::Ptr createVertexLayout() final;
		
		virtual bool create(IWindow& window) final;
		virtual void clear() final;
		virtual void display() final;
		
		void draw(IVertexBuffer::Ptr buffer, IProgram::Ptr program, IVertexLayout::Ptr layout) final;
		
		void draw(IDrawable::Ptr drawable) final;
		
		void draw(IDrawable& drawable) final;
		
		Rect getClientRect() const final;

	};

}

#endif