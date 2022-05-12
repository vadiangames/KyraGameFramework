#ifndef KYRAGAMEFRAMEWORK_RENDERDEVICEGL_RECTANGLESHAPE_HPP
#define KYRAGAMEFRAMEWORK_RENDERDEVICEGL_RECTANGLESHAPE_HPP


#include <KyraGameFramework/GLExtensionLoader/GLExtensionLoader.hpp>
#include <KyraGameFramework/AbstractRenderDevice/IRenderDevice.hpp>
#include <KyraGameFramework/RenderDeviceGL/DLL.hpp>
#include <KyraGameFramework/RenderDeviceGL/Program.hpp>
#include <KyraGameFramework/RenderDeviceGL/VertexBuffer.hpp>
#include <KyraGameFramework/RenderDeviceGL/IndexBuffer.hpp>
#include <KyraGameFramework/RenderDeviceGL/VertexLayout.hpp>
#include <KyraGameFramework/AbstractRenderDevice/VertexArray.hpp>



#include <filesystem>

namespace kyra {
	
	class KYRA_RENDERDEVICEGL_API RectangleShape : public IRectangleShape {
		
		math::Vector2<float> m_Size;
		math::Vector3<float> m_Position;
		math::Vector4<float> m_Color;
		math::Matrix4<float> m_Transformation;
		
		static size_t g_References;
		static IProgram::Ptr g_Program;
		static IVertexLayout::Ptr  g_VertexLayout;
		static IVertexBuffer::Ptr  g_VertexBuffer;
		static IIndexBuffer::Ptr g_IndexBuffer; 
		
		/// The VertexShader-Code used for drawing the RectangleShape
		static std::string g_VertexShader;

		/// The FragmentShader-Code used for drawing the RectangleShape
		static std::string g_FragmentShader;
		
		/// The Projection-Matrix used to draw the RectangleShape
		math::Matrix4<float> m_Projection;
		
		/// VertexType for drawing a RectangleShape
		typedef struct {
			math::Vector3<float> data;
		}Vertex;
		
		void recalculate();
		
		public:
		///Default Constructor
		RectangleShape();
		
		///Default Destructor
		~RectangleShape();
		
		///Returns the size
		math::Vector2<float> getSize() const final;
		
		///Sets the size
		void setSize(const math::Vector2<float>& size) final;
		
		///Returns the position
		math::Vector3<float> getPosition() const final;
		
		///Sets the position
		void setPosition(const math::Vector3<float>& position) final;

		///Create a RectangleShape
		void create(IRenderDevice& renderDevice) final;
		
		///Draws the RectangleShape
		void draw(IRenderDevice& renderDevice) final;

		///Sets the color of the RectangleShape
		void setColor(const math::Vector4<float>& color) final;
	};



}

#endif