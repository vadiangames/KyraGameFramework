#ifndef KYRAGAMEFRAMEWORK_ABSTRACTRENDERDEVICE_ISPRITE_HPP
#define KYRAGAMEFRAMEWORK_ABSTRACTRENDERDEVICE_ISPRITE_HPP

#include <filesystem>
#include <memory>

#include <KyraGameFramework/AbstractRenderDevice/IDrawable.hpp>

#include <KyraGameFramework/Math/Vector2.hpp>
#include <KyraGameFramework/Math/Vector3.hpp>
#include <KyraGameFramework/Math/Vector4.hpp>

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
		
		virtual kyra::Vector2<float> getSize()  const = 0;
		virtual void setSize(const kyra::Vector2<float>& size) = 0;
		virtual kyra::Vector3<float> getPosition() const = 0;
		virtual void setPosition(const kyra::Vector3<float>& position) = 0;
		virtual void setColor(const kyra::Vector4<float>& color) = 0;
	};
	
}

#endif