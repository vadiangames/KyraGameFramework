#ifndef KYRAGAMEFRAMEWORK_USERINTERFACE_WIDGET_HPP
#define KYRAGAMEFRAMEWORK_USERINTERFACE_WIDGET_HPP

#include <KyraGameFramework/AbstractRenderDevice/IDrawable.hpp>
#include <KyraGameFramework/AbstractRenderDevice/IRenderDevice.hpp>
#include <KyraGameFramework/UserInterface/DLL.hpp>
#include <KyraGameFramework/Math/Vector2.hpp>

#include <memory>
#include <map>
#include <functional>

namespace kyra {
	
	namespace ui {
	
		enum class WidgetEvent {
			ON_HOVER,
			ON_LEAVE,
			ON_LEFT_CLICK,
			ON_RIGHT_CLICK,
			ON_ACTIVATE,
			ON_DEACTIVATE
		};
	
		class KYRA_USERINTERFACE_API Widget : public IDrawable {
			
			std::map< WidgetEvent, std::function<void()> > m_FunctionMap;
			IRenderDevice::Ptr m_RenderDevice;
			
			public:
			Widget(IRenderDevice::Ptr renderDevice);
			virtual ~Widget();
			
			typedef std::shared_ptr<Widget> Ptr;
			
			virtual void onTextEntered( char character ) {
				
			}
			
			virtual void setPosition(const math::Vector3<float>& vec) = 0;
			virtual void setSize( const math::Vector2<float>& vec ) = 0;
			virtual math::Vector2<float> getSize() const = 0;
			virtual bool contains(const math::Vector2<float>& vec) const = 0;
			constexpr virtual bool hasChildElements() const = 0;
			virtual Widget::Ptr getHoveredChild( const math::Vector2<float>& vec) = 0;
			
			void bind( WidgetEvent event, std::function<void()> func);
			void execute(WidgetEvent event);
			
			IRenderDevice::Ptr getRenderDevice() {
				return m_RenderDevice;
			}
					
		};
	}
}

#endif