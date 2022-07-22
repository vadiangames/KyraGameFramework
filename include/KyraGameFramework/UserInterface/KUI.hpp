#ifndef KYRAGAMEFRAMEWORK_USERINTERFACE_KUI_HPP
#define KYRAGAMEFRAMEWORK_USERINTERFACE_KUI_HPP

#include <KyraGameFramework/UserInterface/Context.hpp>
#include <tinyxml2.h>

namespace kyra {
	namespace ui {
		class KUI {
		
			public:
			
			static bool load(const std::string& file, Context& context) {
				tinyxml2::XMLDocument  doc;
				doc.LoadFile(file.c_str());
				tinyxml2::XMLElement* root = doc.RootElement();
				
				for(tinyxml2::XMLELement* widget = root->FirstChildElement("Widget"); widget != nullptr; widget = widget->NextSiblingElement("Widget")) {
					
				}
				
				return false;
			}
			
		};
	}
}

#endif