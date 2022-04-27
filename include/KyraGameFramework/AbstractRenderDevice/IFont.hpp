#ifndef KYRAGAMEFRAMEWORK_ABSTRACTRENDERDEVICE_IFONT_HPP
#define KYRAGAMEFRAMEWORK_ABSTRACTRENDERDEVICE_IFONT_HPP

#include <memory>

namespace kyra {
	
	class IRenderDevice;
	
	/// \brief Abstract interface for all font implementations
	class IFont {
		
		public:
		
		typedef std::shared_ptr<IFont> Ptr;

	};
	
}

#endif