#ifndef KYRAGAMEFRAMEWORK_ABSTRACTRENDERDEVICE_ITEXTURE_HPP
#define KYRAGAMEFRAMEWORK_ABSTRACTRENDERDEVICE_ITEXTURE_HPP

namespace kyra {
	
	class ITexture {
		
		public:
		ITexture() {}
		virtual ~ITexture() {}
		
		virtual void bind(uint32_t slot = 0) = 0;
	};
	
}

#endif