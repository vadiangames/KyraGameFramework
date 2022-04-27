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
		unsigned int VAO;
		
		bool setPixelFormat(HDC hdc);
		
		std::map<std::string, IProgram::Ptr> m_ProgramMap;
		std::map<InternalProgramType, IProgram::Ptr> m_InternalProgramMap;
		
		public:
		RenderDeviceGL();
		virtual ~RenderDeviceGL();
		
		
		virtual IProgram::Ptr createProgramFromFile( const std::string& id, const std::filesystem::path& vertexShader, const std::filesystem::path& fragmentShader );
		virtual IProgram::Ptr createProgramFromMemory(const std::string& id, const std::string& vertexShader, const std::string& fragmentShader );
		
		virtual IProgram::Ptr createInternalProgramFromFile(InternalProgramType type, const std::filesystem::path& vertexShader, const std::filesystem::path& fragmentShader );
		virtual IProgram::Ptr createInternalProgramFromMemory(InternalProgramType type, const std::string& vertexShader, const std::string& fragmentShader );
		
		virtual IProgram::Ptr getProgram(const std::string& id);
		virtual IProgram::Ptr getInternalProgram(InternalProgramType type);
		
		
		virtual IVertexBuffer::Ptr createVertexBuffer() final;
		virtual IVertexLayout::Ptr createVertexLayout() final;
		
		virtual bool create(IWindow& window) final;
		virtual void clear() final;
		virtual void display() final;
		
		void draw(IVertexBuffer::Ptr buffer, IProgram::Ptr program, IVertexLayout::Ptr layout);
		
		void draw(IDrawable::Ptr drawable) final;
	};

}

#endif