#ifndef KYRAGAMEFRAMEWORK_ABSTRACTRENDERDEVICE_IRENDERDEVICE_HPP
#define KYRAGAMEFRAMEWORK_ABSTRACTRENDERDEVICE_IRENDERDEVICE_HPP

#include <KyraGameFramework/AbstractRenderDevice/DLL.hpp>
#include <KyraGameFramework/AbstractRenderDevice/IDrawable.hpp>
#include <KyraGameFramework/AbstractRenderDevice/IProgram.hpp>
#include <KyraGameFramework/AbstractRenderDevice/IVertexBuffer.hpp>
#include <KyraGameFramework/AbstractRenderDevice/IVertexLayout.hpp>
#include <KyraGameFramework/Window/IWindow.hpp>

#include <filesystem>
 
namespace kyra {

	/// The RenderDevice is the most important class within the rendering API. 
	/// Programs, fonts, textures and buffers are created via the class.

	//! Abstract class for all RenderDevice-Classes
	class KYRA_ARD_API IRenderDevice {
		
		public:
		IRenderDevice();
		virtual ~IRenderDevice();
		
		//! Abstract class to create a vertex buffer
		virtual IVertexBuffer::Ptr createVertexBuffer() = 0;
		
		//! Abstract class for creating managed program from file
		virtual IProgram::Ptr createProgramFromFile( const std::string& id, const std::filesystem::path& vertexShader, const std::filesystem::path& fragmentShader ) = 0;
		
		//! Abstract class for creating managed program from memory
		virtual IProgram::Ptr createProgramFromMemory(const std::string& id, const std::string& vertexShader, const std::string& fragmentShader ) = 0;
		
		//! Abstract class for creating managed program from file
		virtual IProgram::Ptr createInternalProgramFromFile(InternalProgramType type, const std::filesystem::path& vertexShader, const std::filesystem::path& fragmentShader ) = 0;
		
		//! Abstract class for creating managed program from memory
		virtual IProgram::Ptr createInternalProgramFromMemory(InternalProgramType type, const std::string& vertexShader, const std::string& fragmentShader ) = 0;
		
		virtual IProgram::Ptr getProgram(const std::string& id) = 0;

		virtual IProgram::Ptr getInternalProgram(InternalProgramType type) = 0;
		
		//! Abstract class to create a vertex layout
		virtual IVertexLayout::Ptr createVertexLayout() = 0;
		
		//! Initializes the shader
		virtual bool create(IWindow& window) = 0;
		
		//! Clears the screen
		virtual void clear() = 0;
		
		//! Displays the screen
		virtual void display() = 0;
		
		//! Draw call to draw the vertex buffer
		virtual void draw(IVertexBuffer::Ptr buffer, IProgram::Ptr program, IVertexLayout::Ptr layout) = 0;

		//! Draws the IDrawable by calling IDrawable::draw(IRenderDevice&)
		virtual void draw(IDrawable::Ptr drawable) = 0;
	};

}

#endif