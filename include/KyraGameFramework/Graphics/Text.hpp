#ifndef KYRAGAMEFRAMEWORK_GRAPHICS_TEXT_HPP
#define KYRAGAMEFRAMEWORK_GRAPHICS_TEXT_HPP

#include <KyraGameFramework/AbstractRenderDevice/IDrawable.hpp>
#include <KyraGameFramework/AbstractRenderDevice/ITexture.hpp>
#include <KyraGameFramework/AbstractRenderDevice/IRenderDevice.hpp>
#include <KyraGameFramework/AbstractRenderDevice/IVertexBuffer.hpp>
#include <KyraGameFramework/AbstractRenderDevice/IProgram.hpp>

#include <memory>

namespace kyra {
	
	class Text : public IDrawable {

		ITexture* m_Texture;
		IVertexBuffer::Ptr m_VertexBuffer;
		IVertexLayout::Ptr m_VertexLayout;
		
		static IProgram::Ptr s_FontProgram;
		//static IVertexLayout::Ptr s_VertexLayout;
		//static IVertexBuffer::Ptr s_VertexBuffer;
		//static std::string s_VertexShader;
		//static std::string s_FragmentShader;
		
		Text() : m_Texture(nullptr) {
			
		}
		
		public:
		
		typedef std::shared_ptr<Text> Ptr;
		
		~Text() {
			
		}
		
		static Ptr create(IRenderDevice& device) {
			if(!Text::s_FontProgram) {
				
			}
			return Ptr(new Text());
		}
				
		void setTexture(ITexture& texture) {
			m_Texture = &texture;
		}
		
		void draw(IRenderDevice& device) final {
			//device.setTextureSlot(0, *m_Texture);
			//device.draw(m_VertexBuffer, Sprite::s_SpriteProgram, m_VertexLayout);
		}
	};
	
	IProgram::Ptr Text::s_FontProgram = IProgram::Ptr(nullptr);
}

#endif