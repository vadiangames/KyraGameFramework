#include <KyraGameFramework/RenderDeviceGL/Sprite.hpp>

namespace kyra {
	
	IProgram::Ptr KYRA_RENDERDEVICEGL_API Sprite::g_Program;
	IVertexBuffer::Ptr KYRA_RENDERDEVICEGL_API  Sprite::g_VertexBuffer;
	IIndexBuffer::Ptr KYRA_RENDERDEVICEGL_API  Sprite::g_IndexBuffer;
	IVertexLayout::Ptr KYRA_RENDERDEVICEGL_API  Sprite::g_VertexLayout;
	size_t KYRA_RENDERDEVICEGL_API Sprite::g_References = 0;
	
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
		m_Transformation = math::Matrix4<float>::getIdentity();
		m_Transformation.translate(m_Position);
		m_Transformation.scale(math::Vector3<float>(m_Size[0], m_Size[1], 1.0f));
	}
		

	KYRA_RENDERDEVICEGL_API Sprite::Sprite() {
		m_Color = math::Vector4<float>(1.f,1.f,1.0f,1.0f);
		m_Position = math::Vector3<float>(0.f,0.f,0.f);
	}
		
	KYRA_RENDERDEVICEGL_API Sprite::~Sprite() {
		Sprite::g_References--;
		if(Sprite::g_References == 0) {
			Sprite::g_Program = IProgram::Ptr(nullptr);
			Sprite::g_VertexBuffer = IVertexBuffer::Ptr(nullptr);
			Sprite::g_IndexBuffer = IIndexBuffer::Ptr(nullptr);
			Sprite::g_VertexLayout = IVertexLayout::Ptr(nullptr);		
		}
	}
	
	math::Vector2<float> KYRA_RENDERDEVICEGL_API Sprite::getSize()  const {
		return m_Size;
	}
		
	void KYRA_RENDERDEVICEGL_API Sprite::setSize(const math::Vector2<float>& size)  {
		m_Size = size;
	}
		
	math::Vector3<float> KYRA_RENDERDEVICEGL_API Sprite::getPosition() const {
		return m_Position;
	}
		
	void KYRA_RENDERDEVICEGL_API Sprite::setPosition(const math::Vector3<float>& position) {
		m_Position = position;
		recalculate();
	}

	void KYRA_RENDERDEVICEGL_API Sprite::create(IRenderDevice& renderDevice) {
		if(!Sprite::g_Program) {
			Sprite::g_Program = renderDevice.createProgramFromMemory(Sprite::g_VertexShader, Sprite::g_FragmentShader);	
		}
		if(!Sprite::g_VertexBuffer) {
			
			VertexArray<Sprite::Vertex> vertexArray(PrimitiveType::TRIANGLES, 4);
			vertexArray.resize(4);
			vertexArray[0].data = math::Vector4<float>(0.0f, 1.0f, 0.0f, 1.0f);
			vertexArray[1].data = math::Vector4<float>(1.0f, 0.0f, 1.0f, 0.0f);
			vertexArray[2].data = math::Vector4<float>(0.0f, 0.0f, 0.0f, 0.0f);
			vertexArray[3].data = math::Vector4<float>(1.0f, 1.0f, 1.0f, 1.0f);
			
			Sprite::g_VertexBuffer = renderDevice.createVertexBuffer();
			Sprite::g_VertexBuffer->create(vertexArray);
			
			unsigned int indices[6] = {0,1,2,0,3,1};
			Sprite::g_IndexBuffer = renderDevice.createIndexBuffer();
			Sprite::g_IndexBuffer->create( 6, sizeof(indices), &indices[0], BufferType::STATIC_DRAW);
						
		}
		if(!Sprite::g_VertexLayout) {
			Sprite::g_VertexLayout = renderDevice.createVertexLayout();
			Sprite::g_VertexLayout->add(4,4*sizeof(float),GL_FLOAT);
		}
		Sprite::g_References++;
	}

	void KYRA_RENDERDEVICEGL_API Sprite::setTexture(std::shared_ptr<ITexture> texture)  {
		m_Texture = texture;
		setSize( texture->getSize() );
		recalculate();
	}
		
	
	void KYRA_RENDERDEVICEGL_API Sprite::draw(IRenderDevice& renderDevice) {
		
		Rect clientRect = renderDevice.getWindow().getClientRect();
		math::Matrix4<float> projection = math::Matrix4<float>::getOrtho(0.f, (float)(clientRect.width), (float)(clientRect.height), 0.0f);
		Sprite::g_Program->setMatrix4("projection", projection);
				
		Sprite::g_Program->setInteger("sprite",0);
		Sprite::g_Program->setMatrix4("model", m_Transformation);
		Sprite::g_Program->setVector4("spriteColor", m_Color);
		
		if(m_Texture) {
			m_Texture->bind(0);
		} else {
			std::cout << "[WARNING] No texture assigned" << std::endl;
		}
		renderDevice.draw(Sprite::g_VertexBuffer,Sprite::g_IndexBuffer, Sprite::g_Program, Sprite::g_VertexLayout);
	}
	
	void KYRA_RENDERDEVICEGL_API Sprite::setColor(const math::Vector4<float>& color) {
		m_Color = color;
	}


	
}