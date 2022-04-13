#ifndef KYRAGAMEFRAMEWORK_ABSTRACTRENDERDEVICE_IDRAWABLE_HPP
#define KYRAGAMEFRAMEWORK_ABSTRACTRENDERDEVICE_IDRAWABLE_HPP

namespace kyra {
	
	class IRenderDevice;
	class IDrawable {
		
		public:
		
		virtual void draw(IRenderDevice& device) = 0;
		
	};
	
}

#endif