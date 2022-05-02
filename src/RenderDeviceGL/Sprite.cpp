#include <KyraGameFramework/RenderDeviceGL/Sprite.hpp>

namespace kyra {
	
	IProgram::Ptr KYRA_RENDERDEVICEGL_API Sprite::g_Program;
	IVertexBuffer::Ptr KYRA_RENDERDEVICEGL_API  Sprite::g_VertexBuffer;
	IVertexLayout::Ptr KYRA_RENDERDEVICEGL_API  Sprite::g_VertexLayout;
	
	std::string KYRA_RENDERDEVICEGL_API  Sprite::g_VertexShader = "#version 330 core\n"
										 "layout (location = 0) in vec4 vertex;\n"
										 "out vec2 TexCoords;\n"
										 "uniform mat4 model;\n"
										 "uniform mat4 projection;\n"
										 "void main()\n"
										 "{\n"
										 "TexCoords = vertex.zw;\n"
										 "gl_Position = projection * model * vec4(vertex.xy, 0.0, 1.0);\n"
										 "}";
	
	std::string KYRA_RENDERDEVICEGL_API Sprite::g_FragmentShader = "#version 330 core\n"
										   "in vec2 TexCoords;\n"
										   "out vec4 color;\n"
										   "uniform sampler2D sprite;\n"
										   "uniform vec4 spriteColor;\n"
										   "void main()\n"
										   "{\n"
										   "color = spriteColor * texture(sprite, TexCoords);\n"
										   "}\n";
										   
										   
										  
	void KYRA_RENDERDEVICEGL_API Sprite::recalculate() {
		m_Transformation = kyra::Matrix4<float>::getIdentity();
		m_Transformation.translate(m_Position);
		m_Transformation.scale(kyra::Vector3<float>(m_Size[0], m_Size[1], 1.0f));
	}
		

	KYRA_RENDERDEVICEGL_API Sprite::Sprite() {
		m_Color = kyra::Vector4<float>(1.f,1.f,1.0f,1.0f);
		m_Position = kyra::Vector3<float>(0.f,0.f,0.f);
	}
		
	KYRA_RENDERDEVICEGL_API Sprite::~Sprite() {
			
	}
	
	kyra::Vector2<float> KYRA_RENDERDEVICEGL_API Sprite::getSize()  const {
		return m_Size;
	}
		
	void KYRA_RENDERDEVICEGL_API Sprite::setSize(const kyra::Vector2<float>& size)  {
		m_Size = size;
	}
		
	kyra::Vector3<float> KYRA_RENDERDEVICEGL_API Sprite::getPosition() const {
		return m_Position;
	}
		
	void KYRA_RENDERDEVICEGL_API Sprite::setPosition(const kyra::Vector3<float>& position) {
		m_Position = position;
		recalculate();
	}

	void KYRA_RENDERDEVICEGL_API Sprite::create(IRenderDevice& renderDevice) {
		if(!Sprite::g_Program) {
			Sprite::g_Program = renderDevice.createProgramFromMemory(Sprite::g_VertexShader, Sprite::g_FragmentShader);	
		}
		if(!Sprite::g_VertexBuffer) {
			VertexArray<Sprite::Vertex> vertexArray(PrimitiveType::TRIANGLES, 6);
			vertexArray.resize(6);
			vertexArray[0].data = kyra::Vector4<float>(0.0f, 1.0f, 0.0f, 1.0f);
			vertexArray[1].data = kyra::Vector4<float>(1.0f, 0.0f, 1.0f, 0.0f);
			vertexArray[2].data = kyra::Vector4<float>(0.0f, 0.0f, 0.0f, 0.0f);
			vertexArray[3].data = kyra::Vector4<float>(0.0f, 1.0f, 0.0f, 1.0f);
			vertexArray[4].data = kyra::Vector4<float>(1.0f, 1.0f, 1.0f, 1.0f);
			vertexArray[5].data = kyra::Vector4<float>(1.0f, 0.0f, 1.0f, 0.0f);
			Sprite::g_VertexBuffer = renderDevice.createVertexBuffer();
			Sprite::g_VertexBuffer->create(vertexArray);
		}
		if(!Sprite::g_VertexLayout) {
			Sprite::g_VertexLayout = renderDevice.createVertexLayout();
			Sprite::g_VertexLayout->add(4,4*sizeof(float),GL_FLOAT);
		}
	}

	void KYRA_RENDERDEVICEGL_API Sprite::setTexture(std::shared_ptr<ITexture> texture)  {
		m_Texture = texture;
		setSize( texture->getSize() );
		recalculate();
	}
		
	
	void KYRA_RENDERDEVICEGL_API Sprite::draw(IRenderDevice& renderDevice) {
		
		Rect clientRect = renderDevice.getClientRect();
		kyra::Matrix4<float> projection = kyra::Matrix4<float>::getOrtho(0.f, (float)(clientRect.width), (float)(clientRect.height), -39.0f);
		Sprite::g_Program->setMatrix4("projection", projection);
				
		Sprite::g_Program->setInteger("sprite",0);
		Sprite::g_Program->setMatrix4("model", m_Transformation);
		Sprite::g_Program->setVector4("spriteColor", m_Color);
		
		if(m_Texture) {
			m_Texture->bind(0);
		} else {
			std::cout << "[WARNING] No texture assigned" << std::endl;
		}
		renderDevice.draw(Sprite::g_VertexBuffer, Sprite::g_Program, Sprite::g_VertexLayout);
	}
	
	void KYRA_RENDERDEVICEGL_API Sprite::setColor(const kyra::Vector4<float>& color) {
		m_Color = color;
	}


	
}