#ifndef KYRAGAMEFRAMEWORK_RENDERDEVICEGL_TEXT_HPP
#define KYRAGAMEFRAMEWORK_RENDERDEVICEGL_TEXT_HPP

#include <KyraGameFramework/RenderDeviceGL/Font.hpp>
#include <KyraGameFramework/AbstractRenderDevice/IText.hpp>
#include <KyraGameFramework/AbstractRenderDevice/IFont.hpp>

namespace kyra {
	
	class Text : public IText {
		
		glm::ivec3 m_Position;
		glm::mat4 m_Transformation;
		IVertexBuffer::Ptr m_VertexBuffer;
		glm::vec4 m_Color;
		IFont::Ptr m_Font;
		
		GLuint m_VAO;
		
		std::string m_Text;
		
		static IProgram::Ptr g_Program;
		static IVertexLayout::Ptr g_VertexLayout;
		
		
		static std::string vertexShaderSrc;
		static std::string fragmentShaderSrc;
		
		public:
		Text()  { 
			m_Transformation = glm::mat4(1.0f);
			m_Color = glm::vec4(1.0f,1.0f,1.0f,1.0f);
			m_Position = glm::vec3(0.0f,0.0f,0.0f);
		}
		
		~Text() {

		}

		void setText(IFont::Ptr font, const std::string& text, IRenderDevice& renderDevice) final {
			if(!Text::g_Program) {
				Text::g_Program = renderDevice.createProgramFromMemory(Text::vertexShaderSrc, Text::fragmentShaderSrc);
			}
			if(!Text::g_VertexLayout) {
				Text::g_VertexLayout = renderDevice.createVertexLayout();
				Text::g_VertexLayout->add(4, 4*sizeof(float), GL_FLOAT);
			}
			m_VertexBuffer = renderDevice.createVertexBuffer();
			m_VertexBuffer->create(PrimitiveType::TRIANGLES, 6, sizeof(float) * 6 * 4, NULL, VertexBufferType::DYNAMIC_DRAW );
			m_Font = font;
			if(!m_Font) {
				std::cout << "[WARNING] Font is not initialized" << std::endl;
			}
			m_Text = text;
		}
	
		void setPosition(const glm::vec3& vec) final {
			m_Position = vec;
		}

		glm::vec3 getPosition() const {
			return m_Position;
		}

		void draw(IRenderDevice& renderDevice) final {
			
			if(!Text::g_Program) { std::cout << "[WARNING] Text::g_Program is not intialised" << std::endl; return;	}
			
			Rect clientRect = renderDevice.getClientRect();
			glm::mat4 projection = glm::ortho(0.f, float(clientRect.width), float(clientRect.height),-39.0f, -1.f, 1.f);
			Text::g_Program->setMatrix4("projection", projection);
			Text::g_Program->setVector4("textColor", m_Color);
						
			if(!Text::g_VertexLayout) {std::cout << "[WARNING] Text::g_VertexLayout is not intialised" << std::endl;return;}
		
			if(!m_VertexBuffer) {std::cout << "[WARNING] VertexBuffer is not intialised" << std::endl;return;}
			
			std::string::iterator c;
			float scale = 1.0f;
			
			float x = m_Position.x;
			float xpos = 0;
			float ypos = 0;
			float w = 0;
			float h = 0;
			
			for(c = m_Text.begin(); c != m_Text.end(); ++c) {
				
				xpos = x + m_Font->getCharacterBearing(*c).x * scale;
				ypos = m_Position.y;
				
				w = m_Font->getCharacterSize(*c).x * scale;
				h = m_Font->getCharacterSize(*c).y * scale;
				
				float vertices[6][4] = {
				
					{ xpos,     ypos + (48*scale) - h,   0.0f, 0.0f },            
					{ xpos,     ypos + (48*scale),       0.0f, 1.0f },
					{ xpos + w, ypos + (48*scale),       1.0f, 1.0f },

					{ xpos,     ypos + (48*scale) - h,   0.0f, 0.0f },
					{ xpos + w, ypos + (48*scale),       1.0f, 1.0f },
					{ xpos + w, ypos + (48*scale) - h,   1.0f, 0.0f }           
				
				};
				m_VertexBuffer->bind();
				m_VertexBuffer->update( sizeof(vertices), vertices);
				m_Font->bindCharacterTexture(*c);
				renderDevice.draw(m_VertexBuffer, Text::g_Program, Text::g_VertexLayout);			
				x += m_Font->getCharacterAdvance(*c);
			}
		}


	};


	IProgram::Ptr Text::g_Program;
	IVertexLayout::Ptr Text::g_VertexLayout;
	
	std::string Text::vertexShaderSrc = "#version 330 core\n"
							  "layout (location = 0) in vec4 vertex;\n"
							  "out vec2 TexCoords;\n"
							  "uniform mat4 projection;\n"
							  "void main()\n"
							  "{\n"
							  "gl_Position = projection * vec4(vertex.xy, 0.0, 1.0);\n"
							  "TexCoords = vertex.zw;\n"
							  "}";
							  
	 std::string Text::fragmentShaderSrc = "#version 330 core\n"
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


				  



#endif