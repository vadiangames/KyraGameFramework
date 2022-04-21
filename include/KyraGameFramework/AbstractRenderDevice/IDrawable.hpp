#ifndef KYRAGAMEFRAMEWORK_ABSTRACTRENDERDEVICE_IDRAWABLE_HPP
#define KYRAGAMEFRAMEWORK_ABSTRACTRENDERDEVICE_IDRAWABLE_HPP

#include <memory>

namespace kyra {
	
	class IRenderDevice;
	class IDrawable {
		
		public:
		
		typedef std::shared_ptr<IDrawable> Ptr;
		
		virtual void draw(IRenderDevice& device) = 0;
		
	};
	
}

#endif