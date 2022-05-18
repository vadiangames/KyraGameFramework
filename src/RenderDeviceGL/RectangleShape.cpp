#include <KyraGameFramework/RenderDeviceGL/RectangleShape.hpp>

namespace kyra {
	
	IProgram::Ptr KYRA_RENDERDEVICEGL_API RectangleShape::g_Program;
	IVertexBuffer::Ptr KYRA_RENDERDEVICEGL_API  RectangleShape::g_VertexBuffer;
	IIndexBuffer::Ptr KYRA_RENDERDEVICEGL_API  RectangleShape::g_IndexBuffer;
	IVertexLayout::Ptr KYRA_RENDERDEVICEGL_API  RectangleShape::g_VertexLayout;
	size_t KYRA_RENDERDEVICEGL_API RectangleShape::g_References = 0;
	
	std::string KYRA_RENDERDEVICEGL_API  RectangleShape::g_VertexShader = "#version 330 core\n"
										 "layout (location = 0) in vec3 vertex;\n"
										 "uniform mat4 model;\n"
										 "uniform mat4 projection;\n"
										 "void main()\n"
										 "{\n"
										 "gl_Position = projection * model * vec4(vertex.xyz, 1.0);\n"
										 "}";
	
	std::string KYRA_RENDERDEVICEGL_API RectangleShape::g_FragmentShader = "#version 330 core\n"
										   "out vec4 color;\n"
										   "uniform vec4 RectangleShapeColor;\n"
										   "void main()\n"
										   "{\n"
										   "color = RectangleShapeColor;\n"
										   "}\n";
										   
										   
										  
	void KYRA_RENDERDEVICEGL_API RectangleShape::recalculate() {
		//Recalculate the Modelview-Matrix m_Transformation
		m_Transformation = math::Matrix4<float>::getIdentity();
		
		//Set the size
		m_Transformation.scale(math::Vector3<float>(m_Size[0], m_Size[1], 1.0f));
		
		//Set the position
		m_Transformation.translate(m_Position);
	
	}
		

	KYRA_RENDERDEVICEGL_API RectangleShape::RectangleShape() : m_Position(math::Vector3<float>(0.0f,0.0f,0.0f)), m_Color(math::Vector4<float>(1.0f,1.0f,1.0f,1.0f)) {
		recalculate();
	}
		
	KYRA_RENDERDEVICEGL_API RectangleShape::~RectangleShape() {
		//Decreases the references to the program, vertexbuffer, indexbuffer and the vertexlayout
		RectangleShape::g_References--;

		//If there are no more references, release the objects
		if(RectangleShape::g_References == 0) {
			RectangleShape::g_Program = IProgram::Ptr(nullptr);
			RectangleShape::g_VertexBuffer = IVertexBuffer::Ptr(nullptr);
			RectangleShape::g_IndexBuffer = IIndexBuffer::Ptr(nullptr);
			RectangleShape::g_VertexLayout = IVertexLayout::Ptr(nullptr);		
		}
	}
	
	math::Vector2<float> KYRA_RENDERDEVICEGL_API RectangleShape::getSize()  const {
		return m_Size;
	}
		
	void KYRA_RENDERDEVICEGL_API RectangleShape::setSize(const math::Vector2<float>& size)  {
		//Set the size and recalculate the modelview-matrix
		m_Size = size;
		recalculate();
	}
		
	math::Vector3<float> KYRA_RENDERDEVICEGL_API RectangleShape::getPosition() const {
		return m_Position;
	}
		
	void KYRA_RENDERDEVICEGL_API RectangleShape::setPosition(const math::Vector3<float>& position) {
		//Set the position and recalculate the modelview-matrix
		m_Position = position;
		recalculate();
	}

	void KYRA_RENDERDEVICEGL_API RectangleShape::create(IRenderDevice& renderDevice) {
		//If the program not created before, create it
		if(!RectangleShape::g_Program) {
			RectangleShape::g_Program = renderDevice.createProgramFromMemory(RectangleShape::g_VertexShader, RectangleShape::g_FragmentShader);	
		}

		//If the vertexbuffer not created before, create it
		if(!RectangleShape::g_VertexBuffer) {
			
			VertexArray<RectangleShape::Vertex> vertexArray(PrimitiveType::TRIANGLES, 4);
			vertexArray.resize(4);
			
			//We set the size to 1 and stretch it in the shader to the given size
			vertexArray[0].data = math::Vector3<float>(0.0f, 1.0f, 1.0f);
			vertexArray[1].data = math::Vector3<float>(1.0f, 0.0f, 1.0f);
			vertexArray[2].data = math::Vector3<float>(0.0f, 0.0f, 1.0f);
			vertexArray[3].data = math::Vector3<float>(1.0f, 1.0f, 1.0f);
			RectangleShape::g_VertexBuffer = renderDevice.createVertexBuffer();
			RectangleShape::g_VertexBuffer->create(vertexArray);
			
			//Create and fill the indexbuffer
			unsigned int indices[6] = {0,1,2,0,3,1};
			RectangleShape::g_IndexBuffer = renderDevice.createIndexBuffer();
			RectangleShape::g_IndexBuffer->create( 6, sizeof(indices), &indices[0], BufferType::STATIC_DRAW);
						
		}
		
		//If the vertexlayout not created before, create it
		if(!RectangleShape::g_VertexLayout) {
			RectangleShape::g_VertexLayout = renderDevice.createVertexLayout();
			RectangleShape::g_VertexLayout->add(3,3*sizeof(float),GL_FLOAT);
		}
		//Increase the reference counter for the vertexbuffer, program and vertexlayout
		//This prevents the objects from being deleted too early ( see RectangleShape::~RectangleShape)
		RectangleShape::g_References++;
	}

		void KYRA_RENDERDEVICEGL_API RectangleShape::draw(IRenderDevice& renderDevice) {
		
		//Get the window size for calculating the projection matrix
		Rect clientRect = renderDevice.getWindow().getClientRect();

		//Calculate and set the projection matrix
		math::Matrix4<float> projection = math::Matrix4<float>::getOrtho(0.f, (float)(clientRect.width), (float)(clientRect.height), 0);
		RectangleShape::g_Program->setMatrix4("projection", projection);

		//Set the Modelview-Matrix		
		RectangleShape::g_Program->setMatrix4("model", m_Transformation);
		
		//Set the Shape-color
		RectangleShape::g_Program->setVector4("RectangleShapeColor", m_Color);
		
		//Draw the RectangleShape
		renderDevice.draw(RectangleShape::g_VertexBuffer,RectangleShape::g_IndexBuffer, RectangleShape::g_Program, RectangleShape::g_VertexLayout);
	}
	
	void KYRA_RENDERDEVICEGL_API RectangleShape::setColor(const math::Vector4<float>& color) {
		m_Color = color;
	}


	
}