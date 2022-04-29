#ifndef KYRAGAMEFRAMEWORK_RENDERDEVICEGL_SPRITE_HPP
#define KYRAGAMEFRAMEWORK_RENDERDEVICEGL_SPRITE_HPP

#include <KyraGameFramework/GLExtensionLoader/GLExtensionLoader.hpp>
#include <KyraGameFramework/AbstractRenderDevice/ISprite.hpp>
#include <KyraGameFramework/RenderDeviceGL/Texture.hpp>
#include <KyraGameFramework/RenderDeviceGL/Program.hpp>
#include <KyraGameFramework/RenderDeviceGL/VertexBuffer.hpp>
#include <KyraGameFramework/RenderDeviceGL/VertexLayout.hpp>
#include <KyraGameFramework/AbstractRenderDevice/VertexArray.hpp>
#include <KyraGameFramework/AbstractRenderDevice/IRenderDevice.hpp>


#include <filesystem>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp> 

namespace kyra {
	
	class KYRA_RENDERDEVICEGL_API Sprite : public ISprite {
		
		glm::vec2 m_Size;
		glm::vec3 m_Position;
		glm::vec4 m_Color;
		glm::mat4 m_Transformation;
		
		ITexture::Ptr m_Texture;
		
		static IProgram::Ptr g_Program;
		static IVertexLayout::Ptr  g_VertexLayout;
		static IVertexBuffer::Ptr  g_VertexBuffer;
		
		static std::string g_VertexShader;
		static std::string g_FragmentShader;
		
		glm::mat4 m_Projection;
		
		typedef struct {
			glm::vec4 data;
		}Vertex;
		
		void recalculate();
		
		public:
		Sprite();
		
		~Sprite();
		
		glm::vec2 getSize() const final;
		
		void setSize(const glm::vec2& size) final;
		
		glm::vec3 getPosition() const final;
		
		void setPosition(const glm::vec3& position) final;

		void create(IRenderDevice& renderDevice) final;
		
		void setTexture(std::shared_ptr<ITexture> texture) final;
		
		void draw(IRenderDevice& renderDevice) final;

		void setColor(const glm::vec4& color) final;
	};



}

#endif