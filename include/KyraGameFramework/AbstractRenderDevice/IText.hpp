#ifndef KYRAGAMEFRAMEWORK_ABSTRACTRENDERDEVICE_ITEXT_HPP
#define KYRAGAMEFRAMEWORK_ABSTRACTRENDERDEVICE_ITEXT_HPP

#include <glm/glm.hpp>
#include <filesystem>
#include <memory>

#include <KyraGameFramework/AbstractRenderDevice/IDrawable.hpp>

namespace kyra {
	
	class IRenderDevice;
	class IFont;

	class IText : public IDrawable {
		
		public:
		IText() {}
		virtual ~IText() {}
		
		typedef std::shared_ptr<IText> Ptr;
		
		//virtual void create(IRenderDevice& renderDevice) = 0;
		virtual void setText(std::shared_ptr<IFont> font, const std::string& text, IRenderDevice& renderDevice) = 0;
		
		virtual glm::vec3 getPosition() const = 0;
		virtual void setPosition(const glm::vec3& position) = 0;
	};
	
}

#endif