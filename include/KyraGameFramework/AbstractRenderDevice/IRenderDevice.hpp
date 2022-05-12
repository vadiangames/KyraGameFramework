#ifndef KYRAGAMEFRAMEWORK_ABSTRACTRENDERDEVICE_IRENDERDEVICE_HPP
#define KYRAGAMEFRAMEWORK_ABSTRACTRENDERDEVICE_IRENDERDEVICE_HPP

#include <KyraGameFramework/AbstractRenderDevice/DLL.hpp>
#include <KyraGameFramework/AbstractRenderDevice/IDrawable.hpp>
#include <KyraGameFramework/AbstractRenderDevice/IProgram.hpp>
#include <KyraGameFramework/AbstractRenderDevice/IVertexBuffer.hpp>
#include <KyraGameFramework/AbstractRenderDevice/IIndexBuffer.hpp>
#include <KyraGameFramework/AbstractRenderDevice/IVertexLayout.hpp>
#include <KyraGameFramework/AbstractRenderDevice/ITexture.hpp>
#include <KyraGameFramework/AbstractRenderDevice/ISprite.hpp>
#include <KyraGameFramework/AbstractRenderDevice/IRectangleShape.hpp>
#include <KyraGameFramework/Window/IWindow.hpp>

#include <filesystem>
 
namespace kyra {

	/// The RenderDevice is the most important class within the rendering API. 
	/// Programs, fonts, textures and buffers are created and managed via the class.

	//! Abstract class for all RenderDevice-Classes
	class KYRA_ARD_API IRenderDevice {
		
		public:
		IRenderDevice();
		virtual ~IRenderDevice();
		
		typedef std::shared_ptr<IRenderDevice> Ptr;
		
		virtual void setActiveSyncEnabled(bool value) = 0;
		
		//! Abstract class to create a vertex buffer
		virtual IVertexBuffer::Ptr createVertexBuffer() = 0;
		
		//! Abstract class to create a texture
		virtual ITexture::Ptr createTexture(const std::filesystem::path& path) = 0;
		
		//! Abstract class to create a sprite
		virtual ISprite::Ptr createSprite(ITexture::Ptr texture) = 0;
		
		//! Abstract class for creating managed program from file
		virtual IProgram::Ptr createProgramFromFile( const std::filesystem::path& vertexShader, const std::filesystem::path& fragmentShader ) = 0;
		
		//! Abstract class for creating managed program from memory
		virtual IProgram::Ptr createProgramFromMemory( const std::string& vertexShader, const std::string& fragmentShader ) = 0;
		
		//! Abstract class to create a vertex layout
		virtual IVertexLayout::Ptr createVertexLayout() = 0;
		
		virtual IIndexBuffer::Ptr createIndexBuffer() = 0;
		
		virtual IRectangleShape::Ptr createRectangleShape( const math::Vector3<float>& position, const math::Vector2<float>& size) = 0;
		
		//! Initializes the shader
		virtual bool create(IWindow& window) = 0;
		
		//! Clears the screen
		virtual void clear() = 0;
		
		//! Displays the screen
		virtual void display() = 0;
		
		//! Draw call to draw the vertex buffer
		virtual void draw(IVertexBuffer::Ptr buffer, IProgram::Ptr program, IVertexLayout::Ptr layout) = 0;

		//! Draw call to draw the vertex buffer
		virtual void draw(IVertexBuffer::Ptr vertexBuffer, IIndexBuffer::Ptr indexBuffer, IProgram::Ptr program, IVertexLayout::Ptr layout) = 0;


		//! Draws the IDrawable by calling IDrawable::draw(IRenderDevice&)
		virtual void draw(IDrawable::Ptr drawable) = 0;
		
		//! Draws the IDrawable by calling IDrawable::draw(IRenderDevice&)
		virtual void draw(IDrawable& drawable) = 0;
		
		virtual Rect getClientRect() const = 0;
	};

}

#endif