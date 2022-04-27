#ifndef KYRAGAMEFRAMEWORK_RENDERDEVICEGL_TEXT_HPP
#define KYRAGAMEFRAMEWORK_RENDERDEVICEGL_TEXT_HPP

#include <KyraGameFramework/RenderDeviceGL/Font.hpp>

namespace kyra {
	
	class Text {
		
		GLuint m_VAO;
		GLuint m_VBO;
		glm::ivec2 m_Position;
		IProgram::Ptr m_Program;
		
		
		static std::string vertexShaderSrc = "#version 330 core\n"
							  "layout (location = 0) in vec4 vertex;\n"
							  "out vec2 TexCoords;\n"
							  "uniform mat4 projection;\n"
							  "void main()\n"
							  "{\n"
							  "gl_Position = projection * vec4(vertex.xy, 0.0, 1.0);\n"
							  "TexCoords = vertex.zw;\n"
							  "}";
							  
		static std::string fragmentShaderSrc = "#version 330 core\n"
								"in vec2 TexCoords;\n"
								"out vec4 color;\n"
								"uniform sampler2D text;\n"
								"uniform vec3 textColor;\n"
								"void main()\n"
								"{\n"
								"vec4 sampled = vec4(1.0, 1.0, 1.0, texture(text, TexCoords).r);\n"
								"color = vec4(textColor, 1.0) * sampled;\n"
								"}\n"; 
		
		
		public:
		Text() : m_VAO(0), m_VBO(0) {
			
			m_Program = 
			
			
			if(!Sprite::m_SpriteProgram) {
				Sprite::m_SpriteProgram = std::unique_ptr<Program>(new Program());
				glm::mat4 projection = glm::ortho(0.f,800.0f, 600.0f, -39.f, -1.0f, 1.0f);
				Sprite::m_SpriteProgram->createProgramFromMemory("DefaultShader", Sprite::vertexShaderSrc, Sprite::fragmentShaderSrc);
				Sprite::m_SpriteProgram->setMatrix4("projection", projection);
			}
			
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
		}
		
		~Sprite() {

		}

		void draw


	};


	std::unique_ptr<Program> m_SpriteProgram
};


				  



#endif