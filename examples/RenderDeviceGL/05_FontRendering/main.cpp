#include <KyraGameFramework/Window.hpp>
#include <KyraGameFramework/RenderDeviceGL/RenderDeviceGL.hpp>
#include <KyraGameFramework/RenderDeviceGL/Shader.hpp>
#include <KyraGameFramework/RenderDeviceGL/Program.hpp>
#include <KyraGameFramework/RenderDeviceGL/VertexBuffer.hpp>
#include <KyraGameFramework/RenderDeviceGL/VertexLayout.hpp>
#include <KyraGameFramework/RenderDeviceGL/Texture.hpp>
#include <KyraGameFramework/RenderDeviceGL/Font.hpp>
#include <KyraGameFramework/Math/Vector3.hpp>
#include <KyraGameFramework/Graphics/VertexArray.hpp>



//#include <ft2build.h>
//#include FT_FREETYPE_H  

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp> 

#include <iostream>
#include <filesystem>
#include <map>

std::string vertexShaderSrc = "#version 330 core\n"
							  "layout (location = 0) in vec4 vertex;\n"
							  "out vec2 TexCoords;\n"
							  "uniform mat4 projection;\n"
							  "void main()\n"
							  "{\n"
							  "gl_Position = projection * vec4(vertex.xy, 0.0, 1.0);\n"
							  "TexCoords = vertex.zw;\n"
							  "}";
							  
std::string fragmentShaderSrc = "#version 330 core\n"
								"in vec2 TexCoords;\n"
								"out vec4 color;\n"
								"uniform sampler2D text;\n"
								"uniform vec3 textColor;\n"
								"void main()\n"
								"{\n"
								"vec4 sampled = vec4(1.0, 1.0, 1.0, texture(text, TexCoords).r);\n"
								"color = vec4(textColor, 1.0) * sampled;\n"
								"}\n"; 

								
typedef struct {
	unsigned int id;
	glm::ivec2 size;
	glm::ivec2 bearing;
	long int advance;
}Character;

typedef struct {
	glm::vec4 data;
}TextVertex;
								
class MyApplication : public kyra::SystemEventListener {

	kyra::Window m_Window;
	kyra::RenderDeviceGL m_Renderer;
	
	public:
	MyApplication() {}
	~MyApplication() {}
	
	
	//! Implementation of kyra::SystemEventListener::onClose()
	virtual void onClose() {
		m_Window.close();
	}
		
	void run() {
		
		kyra::WindowSettings windowSettings;
		windowSettings.width = 800;
		windowSettings.height = 600;
		windowSettings.title = L"KyraGameFramework - Window - 03_ColoredTrinagle";
		
		std::map<char, Character> characters;
		
		if(m_Window.create(windowSettings)) {
			
			m_Window.addListener(this);
			
			if(m_Renderer.create(m_Window)) {
				
				glm::mat4 projection = glm::ortho(0.f,800.0f, 600.0f, -39.f, -1.0f, 1.0f);
								
				glm::vec3 color = glm::vec3(1.0f, 0.0f,1.0f);
				std::string text = "Hello World";
								
				kyra::IProgram::Ptr program = m_Renderer.createProgramFromMemory("DefaultShader", vertexShaderSrc, fragmentShaderSrc);
				program->setMatrix4("projection", projection);
				
				kyra::Font font;
				font.loadFromFile("Antonio-Regular.ttf",48);
			
				unsigned int VAO, VBO;
				GL_CHECK(glGenVertexArrays(1, &VAO));
				GL_CHECK(glGenBuffers(1, &VBO));
				GL_CHECK(glBindVertexArray(VAO));
				GL_CHECK(glBindBuffer(GL_ARRAY_BUFFER, VBO));
				GL_CHECK(glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 6 * 4, NULL, GL_DYNAMIC_DRAW));
				GL_CHECK(glEnableVertexAttribArray(0));
				GL_CHECK(glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), 0));
				GL_CHECK(glBindBuffer(GL_ARRAY_BUFFER, 0));
				GL_CHECK(glBindVertexArray(0));  
				
				while(m_Window.isOpen()) {
					m_Window.processEvents();
					m_Renderer.clear();
						program->use();
						program->setVector3("textColor", color);
						std::string::const_iterator c;
						GL_CHECK(glActiveTexture(GL_TEXTURE0));
						GL_CHECK(glBindVertexArray(VAO));
						float x = 0;
						float y = 0;
						float scale = 1.0f;
				
						// iterate through all characters
						for (c = text.begin(); c != text.end(); c++)
						{
							kyra::Character ch = font.getCharacter(*c);
							//Character ch = characters[*c];

							float xpos = x + ch.bearing.x * scale;
							float ypos = 0; //y - (ch.size.y - ch.bearing.y) * scale;

							float w = ch.size.x * scale;
							float h = ch.size.y * scale;
							
							float vertices[6][4] = {
								{ xpos,     ypos + 24 - h,   0.0f, 0.0f },            
								{ xpos,     ypos + 24,       0.0f, 1.0f },
								{ xpos + w, ypos + 24,       1.0f, 1.0f },

								{ xpos,     ypos + 24 - h,   0.0f, 0.0f },
								{ xpos + w, ypos + 24,       1.0f, 1.0f },
								{ xpos + w, ypos + 24 - h,   1.0f, 0.0f }           
							};
							
							// render glyph texture over quad
							GL_CHECK(glBindTexture(GL_TEXTURE_2D, ch.id));
							// update content of VBO memory
							GL_CHECK(glBindBuffer(GL_ARRAY_BUFFER, VBO));
							GL_CHECK(glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices)); 
							// render quad
							GL_CHECK(glDrawArrays(GL_TRIANGLES, 0, 6));
							// now advance cursors for next glyph (note that advance is number of 1/64 pixels)
							x += (ch.advance >> 6) * scale; // bitshift by 6 to get value in pixels (2^6 = 64)*/
						}
						GL_CHECK(glBindVertexArray(0));
						GL_CHECK(glBindTexture(GL_TEXTURE_2D, 0));
					m_Renderer.display();
				}
				GL_CHECK(glDeleteVertexArrays(1, &VAO));
			}			
			
		}
		
	}

};

int main(int argc, char** argv) {

	MyApplication().run();
	
	return 0;
}