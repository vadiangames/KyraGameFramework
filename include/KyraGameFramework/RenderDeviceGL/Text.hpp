#ifndef KYRAGAMEFRAMEWORK_RENDERDEVICEGL_TEXT_HPP
#define KYRAGAMEFRAMEWORK_RENDERDEVICEGL_TEXT_HPP

#include <KyraGameFramework/RenderDeviceGL/DLL.hpp>
#include <KyraGameFramework/RenderDeviceGL/Font.hpp>
#include <KyraGameFramework/AbstractRenderDevice/IText.hpp>
#include <KyraGameFramework/AbstractRenderDevice/IFont.hpp>
#include <KyraGameFramework/AbstractRenderDevice/IVertexBuffer.hpp>
#include <KyraGameFramework/AbstractRenderDevice/IProgram.hpp>
#include <KyraGameFramework/AbstractRenderDevice/IVertexLayout.hpp>
#include <KyraGameFramework/AbstractRenderDevice/IRenderDevice.hpp>

#include <KyraGameFramework/Math/Vector3.hpp>
#include <KyraGameFramework/Math/Vector4.hpp>
#include <KyraGameFramework/Math/Matrix4.hpp>

namespace kyra {
	
	class KYRA_RENDERDEVICEGL_API Text : public IText {
		
		kyra::math::Vector3<float> m_Position;
		kyra::math::Matrix4<float> m_Transformation;
		IVertexBuffer::Ptr m_VertexBuffer;
		kyra::math::Vector4<float> m_Color;
		IFont::Ptr m_Font;
		
		GLuint m_VAO;
		
		std::string m_Text;
		
		static IProgram::Ptr g_Program;
		static IVertexLayout::Ptr g_VertexLayout;
		
		
		static std::string vertexShaderSrc;
		static std::string fragmentShaderSrc;
		
		public:
		Text();
		
		~Text();

		void setText(IFont::Ptr font, const std::string& text, IRenderDevice& renderDevice) final;
	
		void setPosition(const kyra::math::Vector3<float>& vec) final;
		
		void setColor( const kyra::math::Vector4<float>& vec ) final;

		inline kyra::math::Vector3<float> getPosition() const;

		void draw(IRenderDevice& renderDevice) final;


	};
	
}


				  



#endif