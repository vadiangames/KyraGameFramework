#ifndef KYRAGAMEFRAMEWORK_ABSTRACTRENDERDEVICE_IRENDERDEVICE_HPP
#define KYRAGAMEFRAMEWORK_ABSTRACTRENDERDEVICE_IRENDERDEVICE_HPP

#include <KyraGameFramework/AbstractRenderDevice/DLL.hpp>
#include <KyraGameFramework/AbstractRenderDevice/IDrawable.hpp>
#include <KyraGameFramework/AbstractRenderDevice/IProgram.hpp>
#include <KyraGameFramework/AbstractRenderDevice/IVertexBuffer.hpp>
#include <KyraGameFramework/AbstractRenderDevice/IVertexLayout.hpp>
#include <KyraGameFramework/Window/IWindow.hpp>

namespace kyra {

	//! Abstract class for all RenderDevice-Classes
	class KYRA_ARD_API IRenderDevice {
		
		public:
		IRenderDevice();
		virtual ~IRenderDevice();
		
		//! Abstract class to create a vertex buffer
		virtual IVertexBuffer::Ptr createVertexBuffer() = 0;
		
		//! Abstract class to create a program
		virtual IProgram::Ptr createProgram() = 0;
		
		//! Abstract class to create a vertex layout
		virtual IVertexLayout::Ptr createVertexLayout() = 0;
		
		//! Initializes the shader
		virtual bool create(IWindow& window) = 0;
		
		//! Clears the screen
		virtual void clear() = 0;
		
		//! Displays the screen
		virtual void display() = 0;
		
		[[deprecated]]
		virtual void draw(IVertexBuffer& buffer, IProgram& program, IVertexLayout& layout) = 0;
		
		//! Draw call to draw the vertex buffer
		virtual void draw(IVertexBuffer::Ptr buffer, IProgram::Ptr program, IVertexLayout::Ptr layout) = 0;
		
		[[deprecated]]
		virtual void draw(IDrawable& drawable) = 0;
		
		//! Draws the IDrawable by calling IDrawable::draw(IRenderDevice&)
		virtual void draw(IDrawable::Ptr drawable) = 0;
	};

}

#endif