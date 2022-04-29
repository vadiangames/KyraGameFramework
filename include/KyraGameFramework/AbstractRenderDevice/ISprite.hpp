#ifndef KYRAGAMEFRAMEWORK_ABSTRACTRENDERDEVICE_ISPRITE_HPP
#define KYRAGAMEFRAMEWORK_ABSTRACTRENDERDEVICE_ISPRITE_HPP

#include <glm/glm.hpp>
#include <filesystem>
#include <memory>

#include <KyraGameFramework/AbstractRenderDevice/IDrawable.hpp>

namespace kyra {
	
	class IRenderDevice;
	class ITexture;

	class ISprite : public IDrawable {
		
		public:
		ISprite() {}
		virtual ~ISprite() {}
		
		typedef std::shared_ptr<ISprite> Ptr;
		
		virtual void create(IRenderDevice& renderDevice) = 0;
		virtual void setTexture(std::shared_ptr<ITexture> texture) = 0;
		
		virtual glm::vec2 getSize()  const = 0;
		virtual void setSize(const glm::vec2& size) = 0;
		virtual glm::vec3 getPosition() const = 0;
		virtual void setPosition(const glm::vec3& position) = 0;
		virtual void setColor(const glm::vec4& color) = 0;
	};
	
}

#endif