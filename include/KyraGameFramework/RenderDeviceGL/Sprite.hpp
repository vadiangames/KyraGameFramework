#ifndef KYRAGAMEFRAMEWORK_RENDERDEVICEGL_SPRITE_HPP
#define KYRAGAMEFRAMEWORK_RENDERDEVICEGL_SPRITE_HPP

#include <KyraGameFramework/GLExtensionLoader/GLExtensionLoader.hpp>
#include <KyraGameFramework/AbstractRenderDevice/ISprite.hpp>
#include <KyraGameFramework/RenderDeviceGL/Texture.hpp>
#include <KyraGameFramework/RenderDeviceGL/Program.hpp>
#include <KyraGameFramework/RenderDeviceGL/VertexBuffer.hpp>
#include <KyraGameFramework/RenderDeviceGL/IndexBuffer.hpp>
#include <KyraGameFramework/RenderDeviceGL/VertexLayout.hpp>
#include <KyraGameFramework/AbstractRenderDevice/VertexArray.hpp>
#include <KyraGameFramework/AbstractRenderDevice/IRenderDevice.hpp>



#include <filesystem>

namespace kyra {
	
	class KYRA_RENDERDEVICEGL_API Sprite : public ISprite {
		
		math::Vector2<float> m_Size;
		math::Vector3<float> m_Position;
		math::Vector4<float> m_Color;
		math::Matrix4<float> m_Transformation;
		
		
		ITexture::Ptr m_Texture;
		
		static size_t g_References;
		static IProgram::Ptr g_Program;
		static IVertexLayout::Ptr  g_VertexLayout;
		static IVertexBuffer::Ptr  g_VertexBuffer;
		static IIndexBuffer::Ptr g_IndexBuffer;
		
		static std::string g_VertexShader;
		static std::string g_FragmentShader;
		
		math::Matrix4<float> m_Projection;
		
		typedef struct {
			math::Vector4<float> data;
		}Vertex;
		
		void recalculate();
		
		public:
		Sprite();
		
		~Sprite();
		
		math::Vector2<float> getSize() const final;
		
		void setSize(const math::Vector2<float>& size) final;
		
		math::Vector3<float> getPosition() const final;
		
		void setPosition(const math::Vector3<float>& position) final;

		void create(IRenderDevice& renderDevice) final;
		
		void setTexture(std::shared_ptr<ITexture> texture) final;
		
		void draw(IRenderDevice& renderDevice) final;

		void setColor(const math::Vector4<float>& color) final;
	};



}

#endif