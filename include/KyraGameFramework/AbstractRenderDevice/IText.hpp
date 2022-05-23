#ifndef KYRAGAMEFRAMEWORK_ABSTRACTRENDERDEVICE_ITEXT_HPP
#define KYRAGAMEFRAMEWORK_ABSTRACTRENDERDEVICE_ITEXT_HPP


#include <filesystem>
#include <memory>

#include <KyraGameFramework/Math/Vector3.hpp>
#include <KyraGameFramework/Math/Vector4.hpp>
#include <KyraGameFramework/AbstractRenderDevice/IDrawable.hpp>

namespace kyra {
	
	class IRenderDevice;
	class IFont;

	class IText : public IDrawable {
		
		public:
		IText() {}
		virtual ~IText() {}
		
		typedef std::shared_ptr<IText> Ptr;
		
		virtual void setText(std::shared_ptr<IFont> font, const std::string& text, IRenderDevice& renderDevice) = 0;
		virtual std::string getText() const = 0;
		virtual void setColor( const kyra::math::Vector4<float>& vec ) = 0;
		
		virtual kyra::math::Vector3<float> getPosition() const = 0;
		virtual void setPosition(const kyra::math::Vector3<float>& position) = 0;
	};
	
}

#endif