#ifndef KYRAGAMEFRAMEWORK_ABSTRACTRENDERDEVICE_IRECTANGLESHAPE_HPP
#define KYRAGAMEFRAMEWORK_ABSTRACTRENDERDEVICE_IRECTANGLESHAPE_HPP

#include <KyraGameFramework/AbstractRenderDevice/IDrawable.hpp>
#include <KyraGameFramework/AbstractRenderDevice/IRenderDevice.hpp>
#include <KyraGameFramework/Math/Vector2.hpp>
#include <KyraGameFramework/Math/Vector3.hpp>
#include <KyraGameFramework/Math/Vector4.hpp>
#include <memory>

namespace kyra {
	
	class IRectangleShape : public IDrawable {
		
		public:

		typedef std::shared_ptr<IRectangleShape> Ptr;
		
		virtual math::Vector2<float> getSize() const = 0;
		
		virtual void setSize(const math::Vector2<float>& size) = 0;
		
		virtual math::Vector3<float> getPosition() const = 0;
		
		virtual void setPosition(const math::Vector3<float>& position) = 0;

		virtual void create(IRenderDevice& renderDevice) = 0;
		
		virtual void draw(IRenderDevice& renderDevice) = 0;

		virtual void setColor(const math::Vector4<float>& color) = 0;
	};



}

#endif