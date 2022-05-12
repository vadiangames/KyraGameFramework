#ifndef KYRAGAMEFRAMEWORK_USERINTERFACE_WIDGET_HPP
#define KYRAGAMEFRAMEWORK_USERINTERFACE_WIDGET_HPP

#include <KyraGameFramework/AbstractRenderDevice/IDrawable.hpp>
#include <KyraGameFramework/UserInterface/DLL.hpp>
#include <memory>

namespace kyra {
	
	namespace ui {
	
		class KYRA_USERINTERFACE_API Widget : public IDrawable {
			
			public:
			Widget();
			virtual ~Widget();
			
			typedef std::shared_ptr<Widget> Ptr;
					
		};
	}
}

#endif