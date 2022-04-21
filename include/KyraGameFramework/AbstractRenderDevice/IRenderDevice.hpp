#ifndef KYRAGAMEFRAMEWORK_ABSTRACTRENDERDEVICE_IRENDERDEVICE_HPP
#define KYRAGAMEFRAMEWORK_ABSTRACTRENDERDEVICE_IRENDERDEVICE_HPP

#include <KyraGameFramework/AbstractRenderDevice/DLL.hpp>
#include <KyraGameFramework/AbstractRenderDevice/IDrawable.hpp>
#include <KyraGameFramework/AbstractRenderDevice/IProgram.hpp>
#include <KyraGameFramework/AbstractRenderDevice/IVertexBuffer.hpp>
#include <KyraGameFramework/AbstractRenderDevice/IVertexLayout.hpp>
#include <KyraGameFramework/Window/IWindow.hpp>

namespace kyra {

	class KYRA_ARD_API IRenderDevice {
		
		public:
		IRenderDevice();
		virtual ~IRenderDevice();
		
		
		virtual IVertexBuffer::Ptr createVertexBuffer() = 0;
		virtual IProgram::Ptr createProgram() = 0;
		virtual IVertexLayout::Ptr createVertexLayout() = 0;
		
		virtual bool create(IWindow& window) = 0;
		virtual void clear() = 0;
		virtual void display() = 0;
		
		virtual void draw(IVertexBuffer& buffer, IProgram& program, IVertexLayout& layout) = 0;
		virtual void draw(IVertexBuffer::Ptr buffer, IProgram::Ptr program, IVertexLayout::Ptr layout) = 0;
		virtual void draw(IDrawable& drawable) = 0;
		virtual void draw(IDrawable::Ptr drawable) = 0;
	};

}

#endif