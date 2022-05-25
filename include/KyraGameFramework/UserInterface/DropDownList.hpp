#ifndef KYRAGAMEFRAMEWORK_USERINTERFACE_DROPDOWNLIST_HPP
#define	KYRAGAMEFRAMEWORK_USERINTERFACE_DROPDOWNLIST_HPP

#include <KyraGameFramework/UserInterface/Widget.hpp>

namespace kyra {
	namespace ui {
		
		class DropDownListElement {
			
			size_t m_Id;
			Widget::Ptr m_Widget;
			
			public:
			DropDownListElement() {
				
			}
			
			DropDownListElement(size_t id, Widget::Ptr widget) : m_Id(id), m_Widget(widget) {
				
			}
			
			~DropDownListElement() {
				
			}
			
			size_t getId() const {
				return m_Id;
			}
			
			Widget::Ptr getWidget() {
				return m_Widget;
			}
			
		};
		
		
		class DropDownList : public Widget {
			
			public:
			DropDownList() {}
			~DropDownList() {}
			
			typedef std::shared_ptr<DropDownList> Ptr;
			
			static Ptr create() {
				return Ptr(new DropDownList());
			}
			
		};
	}
}

#endif