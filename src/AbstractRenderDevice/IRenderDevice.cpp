
#include <KyraGameFramework/AbstractRenderDevice/IRenderDevice.hpp>

namespace kyra {
	
	KYRA_ARD_API IRenderDevice::IRenderDevice() {
		
	}
		
	KYRA_ARD_API IRenderDevice::~IRenderDevice() {
		
	}
	
	void KYRA_ARD_API IRenderDevice::draw(IDrawable& drawable) {
		drawable.draw(*this);
	}
	
}