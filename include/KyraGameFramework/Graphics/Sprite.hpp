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
	
	
	/**
		\todo Set the size by scaling only works with rectangular textures
		\todo Projection-Matrix shouldnt be part of the sprite class
	*/
	class Sprite : public IDrawable {

		glm::vec2 m_Size;
		glm::vec3 m_Position;
		glm::vec3 m_Color;
		glm::mat4 m_Transformation;
		glm::mat4 m_Projection;
		
		typedef struct {
			glm::vec4 data;
		}Vertex;
				
		ITexture* m_Texture;
				
		IProgram::Ptr m_SpriteProgram;
		IVertexLayout::Ptr m_VertexLayout;
		IVertexBuffer::Ptr m_VertexBuffer;
			
		void recalculate() {
			std::cout << "Recalculate" << std::endl;
			m_Transformation = glm::mat4(1.0f);
			m_Transformation = glm::translate(m_Transformation, m_Position);
			m_Transformation = glm::scale(m_Transformation, glm::vec3(m_Size,1.0f));
		}
		
		public:
		
		typedef std::shared_ptr<Sprite> Ptr;
		
		Sprite() : m_Texture(nullptr) {
			m_Color = glm::vec3(0.0f,1.0f,1.0f);
		}
				
		~Sprite() {
			
		}
		
		void create(IRenderDevice& device) {
			if(!m_SpriteProgram) {
				m_SpriteProgram = device.createProgram();
				m_SpriteProgram->linkFromFile("./Shaders/Sprite.vs", "./Shaders/Sprite.fs");
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
			
			m_Projection = glm::ortho(0.0f, 800.0f, 600.f, 0.0f);
		    //glm::mat4 projection = glm::mat4(1.0f);
		}
		
		void setSize(const glm::vec2& vec) {
			m_Size = vec;
			recalculate();
		}
		
		void setPosition(const glm::vec3& position){
			m_Position = position;
			recalculate();
		}
		
		void setTexture(ITexture& texture) {
			m_Texture = &texture;
		}
		
		void draw(IRenderDevice& device) final {
			
			m_SpriteProgram->setMatrix4("model", m_Transformation);
			m_SpriteProgram->setVector3("spriteColor", m_Color);
			m_SpriteProgram->setInteger("sprite",0);
			m_SpriteProgram->setMatrix4("projection", m_Projection);
			
			if(m_Texture) {
				m_Texture->bind(0);
			}
			device.draw(m_VertexBuffer, m_SpriteProgram, m_VertexLayout);
		}
	};
	
	
}

#endif