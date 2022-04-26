#ifndef KYRAGAMEFRAMEWORK_ABSTRACTRENDERDEVICE_IFONT_HPP
#define KYRAGAMEFRAMEWORK_ABSTRACTRENDERDEVICE_IFONT_HPP

#include <memory>

namespace kyra {
	
	class IRenderDevice;
	
	//! Abstract interface for all drawable classes
	class IFont {
		
		public:
		
		typedef std::shared_ptr<IFont> Ptr;

	};
	
}

#endif