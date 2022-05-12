#ifndef KYRAGAMEFRAMEWORK_ABSTRACTRENDERDEVICE_IFONT_HPP
#define KYRAGAMEFRAMEWORK_ABSTRACTRENDERDEVICE_IFONT_HPP

#include <memory>
#include <string>

#include <KyraGameFramework/Math/Vector2.hpp>

namespace kyra {
	
	class IRenderDevice;
		
	/// \brief Abstract interface for all font implementations
	class IFont {
		
		public:
		
		typedef std::shared_ptr<IFont> Ptr;
		
		virtual bool loadFromFile(const std::string& file, unsigned int charSize) = 0;
		virtual kyra::math::Vector2<int> getCharacterSize(char c) = 0;
		virtual kyra::math::Vector2<int> getCharacterBearing(char c) = 0;
		virtual float getCharacterAdvance(char c) = 0;
		virtual void bindCharacterTexture(char c) = 0;
	};
	
}

#endif