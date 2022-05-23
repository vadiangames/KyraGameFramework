#include <KyraGameFramework/RenderDeviceGL/Text.hpp>
#include <KyraGameFramework/GLExtensionLoader/GLExtensionLoader.hpp>

//https://code-examples.net/en/q/13550e3

namespace kyra {

	KYRA_RENDERDEVICEGL_API Text::Text() : m_Position(math::Vector3<float>(0.0f,0.0f,0.0f)),  
										   m_Transformation(math::Matrix4<float>::getIdentity()),
										   m_Color(math::Vector4<float>(1.0f,1.0f,1.0f,1.0f)) {

	}
		
	KYRA_RENDERDEVICEGL_API Text::~Text() {

	}

	void KYRA_RENDERDEVICEGL_API Text::setText(IFont::Ptr font, const std::string& text, IRenderDevice& renderDevice) {
		if(!Text::g_Program) {
			Text::g_Program = renderDevice.createProgramFromMemory(Text::vertexShaderSrc, Text::fragmentShaderSrc);
		}
		if(!Text::g_VertexLayout) {
			Text::g_VertexLayout = renderDevice.createVertexLayout();
			Text::g_VertexLayout->add(4, 4*sizeof(float), GL_FLOAT);
		}
		m_VertexBuffer = renderDevice.createVertexBuffer();
		m_VertexBuffer->create(PrimitiveType::TRIANGLES, 6, sizeof(float) * 6 * 4, NULL, BufferType::DYNAMIC_DRAW );
		m_Font = font;
		if(!m_Font) {
			std::cout << "[WARNING] Font is not initialized" << std::endl;
		}
		m_Text = text;
	}
	
	std::string KYRA_RENDERDEVICEGL_API Text::getText() const {
		return m_Text;
	}
	
	void KYRA_RENDERDEVICEGL_API Text::setPosition(const math::Vector3<float>& vec)  {
		m_Position = vec;
	}

	math::Vector3<float> KYRA_RENDERDEVICEGL_API Text::getPosition() const {
		return m_Position;
	}
	
	void KYRA_RENDERDEVICEGL_API Text::setColor( const kyra::math::Vector4<float>& vec ) {
		m_Color = vec;
	}
	

	void KYRA_RENDERDEVICEGL_API Text::draw(IRenderDevice& renderDevice)  {
			
		if(!Text::g_Program) { std::cout << "[WARNING] Text::g_Program is not intialised" << std::endl; return;	}

		Text::g_Program->setVector4("textColor", m_Color);
		
		//TODO We have to calculate this once and after resizing the window
		Rect clientRect = renderDevice.getWindow().getClientRect();
		math::Matrix4<float> projection = math::Matrix4<float>::getOrtho(0.f, float(clientRect.width), float(clientRect.height), 0.0f ); 
		Text::g_Program->setMatrix4("projection", projection);
				
		if(!Text::g_VertexLayout) {std::cout << "[WARNING] Text::g_VertexLayout is not intialised" << std::endl;return;}
		
		if(!m_VertexBuffer) {std::cout << "[WARNING] VertexBuffer is not intialised" << std::endl;return;}
			
		std::string::iterator c;
		float scale = 1.0f;
			
		float x = m_Position[0];
		
		for(c = m_Text.begin(); c != m_Text.end(); ++c) {
			
			float xpos = x + m_Font->getCharacterBearing(*c)[0] * scale;
			float ypos = m_Position[1];
				
			float w = m_Font->getCharacterSize(*c)[0] * scale;
			float h = m_Font->getCharacterSize(*c)[1] * scale;
			
			float v = (m_Font->getCharacterBearing(*c)[1] * scale) - (m_Font->getCharacterSize(*c)[1] * scale);
			
			float vertices[6][4] = {
				
				{ xpos,     ypos + m_Font->getFontSize() - h -v,   0.0f, 0.0f },            
				{ xpos,     ypos + m_Font->getFontSize() -v,       0.0f, 1.0f },
				{ xpos + w, ypos + m_Font->getFontSize() -v,       1.0f, 1.0f },

				{ xpos,     ypos + m_Font->getFontSize() - h -v,   0.0f, 0.0f },
				{ xpos + w, ypos + m_Font->getFontSize() -v,       1.0f, 1.0f },
				{ xpos + w, ypos + m_Font->getFontSize() - h -v,   1.0f, 0.0f }  				
				
			};
			m_VertexBuffer->bind();
			m_VertexBuffer->update( sizeof(vertices), vertices);
			m_Font->bindCharacterTexture(*c);
			renderDevice.draw(m_VertexBuffer, Text::g_Program, Text::g_VertexLayout);			
			x += m_Font->getCharacterAdvance(*c);
		}
	}
	
	IProgram::Ptr KYRA_RENDERDEVICEGL_API Text::g_Program;
	
	IVertexLayout::Ptr KYRA_RENDERDEVICEGL_API Text::g_VertexLayout;
	
	std::string KYRA_RENDERDEVICEGL_API Text::vertexShaderSrc = "#version 330 core\n"
							  "layout (location = 0) in vec4 vertex;\n"
							  "out vec2 TexCoords;\n"
							  "uniform mat4 projection;\n"
							  "void main()\n"
							  "{\n"
							  "gl_Position = projection * vec4(vertex.xy, 0.0, 1.0);\n"
							  "TexCoords = vertex.zw;\n"
							  "}";
							  
	 std::string KYRA_RENDERDEVICEGL_API Text::fragmentShaderSrc = "#version 330 core\n"
								"in vec2 TexCoords;\n"
								"out vec4 color;\n"
								"uniform sampler2D text;\n"
								"uniform vec4 textColor;\n"
								"void main()\n"
								"{\n"
								"vec4 sampled = vec4(1.0, 1.0, 1.0, texture(text, TexCoords).r);\n"
								"color = textColor * sampled;\n"
								"}\n"; 
	
};
