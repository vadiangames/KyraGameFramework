#ifndef KYRAGAMEFRAMEWORK_RENDERDEVICEGL_FONT_HPP
#define KYRAGAMEFRAMEWORK_RENDERDEVICEGL_FONT_HPP

#include <ft2build.h>
#include FT_FREETYPE_H  

#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp> 
#include <map>


namespace kyra {
	
	typedef struct {
		unsigned int id;
		glm::ivec2 size;
		glm::ivec2 bearing;
		long int advance;
	}Character;

	class Font {
		
		FT_Library m_FreeType;
		FT_Face    m_Face;
		
		std::map<char, Character> m_Characters;
		
		public:
		Font() : m_FreeType(NULL), m_Face(NULL) {
			
		}
		
		~Font() {
			for(auto& character : m_Characters) {
				glDeleteTextures(1,&(character.second.id));
			}
			if(m_Face) {
				FT_Done_Face(m_Face);
			}
			if(m_FreeType) {
				FT_Done_FreeType(m_FreeType);
			}
		}
		
		Character getCharacter(char c) {
			return m_Characters[c];
		}
		
		bool loadFromFile(const std::string& file, unsigned int charSize) {
			
			if(FT_Init_FreeType(&m_FreeType)) {
				std::cout << "[ERROR] Can not initialize FreeType" << std::endl;
				return false;
			}
			if(FT_New_Face(m_FreeType, file.c_str(), 0, &m_Face)) {
				std::cout << "[ERROR] Can not load font " << file << std::endl;
				return false;
			}
			
			FT_Set_Pixel_Sizes(m_Face,0,charSize);
			GL_CHECK(glPixelStorei(GL_UNPACK_ALIGNMENT,1));
			for(unsigned char c = 0; c < 128; c++) {
				if(FT_Load_Char(m_Face,c,FT_LOAD_RENDER)) {
					std::cout << "ERROR::FREETYPE: Failed to load glyph" << c << std::endl;
					continue;
				}
				
				// generate texture
				unsigned int texture;
				GL_CHECK(glGenTextures(1, &texture));
				GL_CHECK(glBindTexture(GL_TEXTURE_2D, texture));
				GL_CHECK(glTexImage2D(
					GL_TEXTURE_2D,
					0,
					GL_RED,
					m_Face->glyph->bitmap.width,
					m_Face->glyph->bitmap.rows,
					0,
					GL_RED,
					GL_UNSIGNED_BYTE,
					m_Face->glyph->bitmap.buffer
				));
				
				// set texture options
				GL_CHECK(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE));
				GL_CHECK(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE));
				GL_CHECK(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR));
				GL_CHECK(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR));
				
				// now store character for later use
				Character character = {
					texture, 
					glm::ivec2(m_Face->glyph->bitmap.width, m_Face->glyph->bitmap.rows),
					glm::ivec2(m_Face->glyph->bitmap_left, m_Face->glyph->bitmap_top),
					m_Face->glyph->advance.x
				};
				m_Characters.insert(std::pair<char, Character>(c, character));
			}
			return true;
		}
		
		
		
		
	};
	
	
	
	
};

#endif