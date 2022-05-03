#ifndef KYRAGAMEFRAMEWORK_USERINTERFACE_WIDGET_HPP
#define KYRAGAMEFRAMEWORK_USERINTERFACE_WIDGET_HPP

#include <KyraGameFramework/AbstractRenderDevice/IDrawable.hpp>

namespace kyra {
	
	class Widget : public IDrawable {
		
		public:
		Widget() {}
		virtual ~Widget() {}
		
		typedef std::shared_ptr<Widget> Ptr;
				
	};
	
}

#endif