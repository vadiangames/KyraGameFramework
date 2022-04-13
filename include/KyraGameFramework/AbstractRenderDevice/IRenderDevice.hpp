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
		
		virtual bool create(IWindow& window) = 0;
		virtual void clear() = 0;
		virtual void display() = 0;
		
		virtual void draw(IVertexBuffer& buffer, IProgram& program, IVertexLayout& layout) = 0;

		void draw(IDrawable& drawable);
	};

}

#endif