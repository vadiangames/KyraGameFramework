#ifndef KYRAGAMEFRAMEWORK_RENDERDEVICEGL_RENDERDEVICEGL_HPP
#define KYRAGAMEFRAMEWORK_RENDERDEVICEGL_RENDERDEVICEGL_HPP


#include <KyraGameFramework/GLExtensionLoader/GLExtensionLoader.hpp>
#include <KyraGameFramework/RenderDeviceGL/DLL.hpp>
#include <KyraGameFramework/AbstractRenderDevice/IRenderDevice.hpp>
#include <KyraGameFramework/AbstractRenderDevice/IRectangleShape.hpp>

#include <windows.h>
#include <map>

namespace kyra {

	class KYRA_RENDERDEVICEGL_API RenderDeviceGL : public IRenderDevice {
		
		HWND m_WindowHandle;
		HDC m_DeviceContext;
		HGLRC m_RenderContext;
		
		IWindow* m_Window;
		
		uint64_t m_DrawCalls;
		
		unsigned int VAO;
		
		bool setPixelFormat(HDC hdc);
		
		View m_View;
		
		public:
		RenderDeviceGL();
		virtual ~RenderDeviceGL();
		
		void setActiveSyncEnabled(bool value) final;
		
		
		IFont::Ptr createFont(const std::filesystem::path& path, unsigned int charSize) final;
		
		IText::Ptr createText(IFont::Ptr font, const std::string& text) final;
		
		ITexture::Ptr createTexture(const std::filesystem::path& path) final;
		ITexture::Ptr createTexture( const math::Vector2<int>& size, void* data ) final;
		
		ISprite::Ptr createSprite(ITexture::Ptr texture) final;
		
		IProgram::Ptr createProgramFromFile( const std::filesystem::path& vertexShader, const std::filesystem::path& fragmentShader ) final;
		IProgram::Ptr createProgramFromMemory( const std::string& vertexShader, const std::string& fragmentShader ) final;
						
		IVertexBuffer::Ptr createVertexBuffer() final;
		IVertexLayout::Ptr createVertexLayout() final;
		IIndexBuffer::Ptr createIndexBuffer() final;
		
		IRectangleShape::Ptr createRectangleShape( const math::Vector3<float>& position, const math::Vector2<float>& size) final;
		
		bool create(IWindow& window) final;
		void clear() final;
		void display() final;
		
		void draw(IVertexBuffer::Ptr buffer, IProgram::Ptr program, IVertexLayout::Ptr layout) final;
		
		void draw(IVertexBuffer::Ptr vertexBuffer, IIndexBuffer::Ptr indexBuffer, IProgram::Ptr program, IVertexLayout::Ptr layout) final;

		
		void draw(IDrawable::Ptr drawable) final;
		
		void draw(IDrawable& drawable) final;
		
		IWindow& getWindow() const final;

		uint64_t getDrawCalls() final {
			uint64_t tmp = m_DrawCalls;
			m_DrawCalls = 0;
			return tmp;
		}

	};

}

#endif