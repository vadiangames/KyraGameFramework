#ifndef KYRAGAMEFRAMEWORK_ABSTRACTRENDERDEVICE_IDRAWABLE_HPP
#define KYRAGAMEFRAMEWORK_ABSTRACTRENDERDEVICE_IDRAWABLE_HPP

#include <memory>

namespace kyra {
	
	class IRenderDevice;
	
	/// \brief Abstract interface for all drawable classes
	class IDrawable {
		
		public:
		
		typedef std::shared_ptr<IDrawable> Ptr;
		
		/// \brief Draws the IDrawable with the given RenderDevice
		virtual void draw(IRenderDevice& device) = 0;
		
	};
	
}

#endif