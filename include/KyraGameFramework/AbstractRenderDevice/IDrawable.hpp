#ifndef KYRAGAMEFRAMEWORK_ABSTRACTRENDERDEVICE_IDRAWABLE_HPP
#define KYRAGAMEFRAMEWORK_ABSTRACTRENDERDEVICE_IDRAWABLE_HPP

#include <memory>

namespace kyra {
	
	class IRenderDevice;
	
	//! Abstract interface for all drawable classes
	class IDrawable {
		
		public:
		
		typedef std::shared_ptr<IDrawable> Ptr;
		
		//! Abstract function for drawing the class
		virtual void draw(IRenderDevice& device) = 0;
		
	};
	
}

#endif