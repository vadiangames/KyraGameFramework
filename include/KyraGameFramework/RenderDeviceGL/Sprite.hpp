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
//#include <glm/glm.hpp>
//#include <glm/gtc/matrix_transform.hpp> 

namespace kyra {
	
	class KYRA_RENDERDEVICEGL_API Sprite : public ISprite {
		
		kyra::Vector2<float> m_Size;
		kyra::Vector3<float> m_Position;
		//glm::vec2 m_Size;
		//glm::vec3 m_Position;
		kyra::Vector4<float> m_Color;
		//glm::mat4 m_Transformation;
		kyra::Matrix4<float> m_Transformation;
		
		
		ITexture::Ptr m_Texture;
		
		static IProgram::Ptr g_Program;
		static IVertexLayout::Ptr  g_VertexLayout;
		static IVertexBuffer::Ptr  g_VertexBuffer;
		
		static std::string g_VertexShader;
		static std::string g_FragmentShader;
		
		kyra::Matrix4<float> m_Projection;
		
		typedef struct {
			kyra::Vector4<float> data;
		}Vertex;
		
		void recalculate();
		
		public:
		Sprite();
		
		~Sprite();
		
		kyra::Vector2<float> getSize() const final;
		
		void setSize(const kyra::Vector2<float>& size) final;
		
		kyra::Vector3<float> getPosition() const final;
		
		void setPosition(const kyra::Vector3<float>& position) final;

		void create(IRenderDevice& renderDevice) final;
		
		void setTexture(std::shared_ptr<ITexture> texture) final;
		
		void draw(IRenderDevice& renderDevice) final;

		void setColor(const kyra::Vector4<float>& color) final;
	};



}

#endif