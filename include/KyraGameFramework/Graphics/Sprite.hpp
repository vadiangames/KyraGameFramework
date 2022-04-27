#ifndef KYRAGAMEFRAMEWORK_GRAPHICS_SPRITE_HPP
#define KYRAGAMEFRAMEWORK_GRAPHICS_SPRITE_HPP

#include <KyraGameFramework/AbstractRenderDevice/IDrawable.hpp>
#include <KyraGameFramework/AbstractRenderDevice/ITexture.hpp>
#include <KyraGameFramework/AbstractRenderDevice/IRenderDevice.hpp>
#include <KyraGameFramework/AbstractRenderDevice/IVertexBuffer.hpp>
#include <KyraGameFramework/AbstractRenderDevice/IProgram.hpp>
#include <KyraGameFramework/Graphics/VertexArray.hpp>

#include <memory>

#include <glm/gtc/matrix_transform.hpp> 

namespace kyra {
	
	class Sprite : public IDrawable {

		glm::vec2 m_Size; //!< The Size of the sprite
		glm::vec3 m_Position; //!< The position of the sprite
		glm::vec3 m_Color; //!< The color of the sprite (gets mixed with the texture-color)
		glm::mat4 m_Transformation; //! The transformation of the sprite
		
		ITexture* m_Texture;	//! The texured used to render the sprite
		
		IProgram::Ptr m_SpriteProgram;
		IVertexLayout::Ptr m_VertexLayout;
		IVertexBuffer::Ptr m_VertexBuffer;
		
		
		/// \brief The vertex type for rendering sprites
		typedef struct {
			glm::vec4 data;
		}Vertex;
		
		/// \brief recalculates the transformation-matrix	
		void recalculate() {
			m_Transformation = glm::mat4(1.0f);
			m_Transformation = glm::translate(m_Transformation, m_Position);
			m_Transformation = glm::scale(m_Transformation, glm::vec3(m_Size,1.0f));
		}
		
		public:
		
		typedef std::shared_ptr<Sprite> Ptr;
		
		Sprite() : m_Texture(nullptr) {
			m_Color = glm::vec3(0.0f,1.0f,1.0f);
			m_Position = glm::vec3(0.0f,0.0f,0.0f);
		}
				
		~Sprite() {
			
		}
		
		void create(IRenderDevice& device) {
			if(!m_SpriteProgram) {
				m_SpriteProgram = device.getInternalProgram(InternalProgramType::SPRITE);
			}
			if(!m_VertexBuffer) {
				VertexArray<Sprite::Vertex> vertexArray(PrimitiveType::TRIANGLES,6);
				vertexArray.resize(6);
				vertexArray[0].data = glm::vec4(0.0f, 1.0f, 0.0f, 1.0f);
				vertexArray[1].data = glm::vec4(1.0f, 0.0f, 1.0f, 0.0f);
				vertexArray[2].data = glm::vec4(0.0f, 0.0f, 0.0f, 0.0f);
				vertexArray[3].data = glm::vec4(0.0f, 1.0f, 0.0f, 1.0f);
				vertexArray[4].data = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
				vertexArray[5].data = glm::vec4(1.0f, 0.0f, 1.0f, 0.0f);
					
				m_VertexBuffer = device.createVertexBuffer();
				m_VertexBuffer->create(vertexArray);
			}

			if(!m_VertexLayout) {
				m_VertexLayout = device.createVertexLayout();
				m_VertexLayout->add(4, 4*sizeof(float), GL_FLOAT);
			}
			
		}
	
		/// \brief Sets the size of the sprite 
		/// \param vec The vector with x as width and y as height
		/// \todo Change param to const kyra::Size<float>& size
		void setSize(const glm::vec2& vec) {
			m_Size = vec;
			recalculate();
		}
		
		/// \brief Sets the position of the sprite
		/// \param position the position to set
		void setPosition(const glm::vec3& position){
			m_Position = position;
			recalculate();
		}
		
		/// \brief Sets texture of the sprite
		/// \param texture The texture for the sprite
		/// \todo Shouldnt this be ITexture::Ptr?
		void setTexture(ITexture& texture) {
			m_Texture = &texture;
			setSize( texture.getSize() );
			recalculate();
		}
		
		
		/// \brief Draw the sprite
		/// \param device The render-device to draw to
		void draw(IRenderDevice& device) final {
			
			m_SpriteProgram->setMatrix4("model", m_Transformation);
			m_SpriteProgram->setVector3("spriteColor", m_Color);
			
			if(m_Texture) {
				m_Texture->bind(0);
			}
			device.draw(m_VertexBuffer, m_SpriteProgram, m_VertexLayout);
		}
	};
	
	
}

#endif