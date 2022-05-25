#ifndef KYRAGAMEFRAMEWORK_RENDERDEVICEGL_FONT_HPP
#define KYRAGAMEFRAMEWORK_RENDERDEVICEGL_FONT_HPP

#include <ft2build.h>
#include FT_FREETYPE_H  

#include <iostream>
#include <map>

#include <KyraGameFramework/AbstractRenderDevice/IFont.hpp>
#include <KyraGameFramework/RenderDeviceGL/Texture.hpp>
#include <KyraGameFramework/GLExtensionLoader/GLExtensionLoader.hpp>

/// \todo Could we move this to the AbstractRenderDevice? Need some abstraction but could be possible!

namespace kyra {
	
    /// Holds the texture and all informations for a character
	typedef struct {
		Texture::Ptr texture;			///< The texture of the character
		math::Vector2<int> size; 		///< The size the character
		math::Vector2<int> bearing; 	///< The bearing informations of this character
		long int advance; 				///< Number of pixels to advance after this character
	}Character;
	
	/// The font loads, renders and hold all character informations for the font and its characters
	class Font : public IFont {
		
		// Can we do this all in LoadFromFile? We need m_FreeType and m_Face only there
		FT_Library m_FreeType;	///< Handle to the freetype-system-handle
		FT_Face    m_Face;		///< Handle to the freetype-face
		
		std::map<char, Character> m_Characters;	///< Maps the char to the rendered character
		unsigned int m_CharacterSize;			///< The character-size the characters were rendered for
		
		public:
		Font() : m_FreeType(NULL), m_Face(NULL), m_CharacterSize(12) {
			
		}
		
		~Font() {
			// Release the font-face
			if(m_Face) {
				FT_Done_Face(m_Face);
			}
			// Release the freetype-system
			if(m_FreeType) {
				FT_Done_FreeType(m_FreeType);
			}
		}
		
		/// Returns the data for the character c
		/// \todo Check if there is an entry for the character
		inline Character getCharacter(char c) {
			return m_Characters[c];
		}
		
		/// Loads a ttf-file and renders the characters	
		/// \param file the ttf-file to load
		/// \param charSize the character size used for character-rendering
		bool loadFromFile(const std::string& file, unsigned int charSize) final {
						
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
		
			int textureWidth = 0;
			int textureHeight = 0;
			
			//CALCULATE SIZE OF THE CHARACTERS-TEXTURE (ALL-IN-ONE) - PROTOTYPE
			
			for(unsigned char c = 0; c < 128; c++) {
				if(FT_Load_Char(m_Face,c,FT_LOAD_RENDER)) {
					std::cout << "ERROR::FREETYPE: Failed to load glyph" << c << std::endl;
					continue;
				}
				if(m_Face->glyph->bitmap.rows > textureHeight) {
					textureHeight = m_Face->glyph->bitmap.rows;
				}
				textureWidth += m_Face->glyph->bitmap.width;
			}
			std::cout << "Font-Texture Size = " << textureWidth << " " << textureHeight << std::endl;

			Texture::Ptr packedTexture = Texture::Ptr(new Texture());
			packedTexture->create( math::Vector2<int>(textureWidth, textureHeight), 0);
			
			// END OF CALCULATION	- PROTOTYPE
			
			for(unsigned char c = 0; c < 128; c++) {
				if(FT_Load_Char(m_Face,c,FT_LOAD_RENDER)) {
					std::cout << "ERROR::FREETYPE: Failed to load glyph" << c << std::endl;
					continue;
				}
								
				Texture::Ptr text = Texture::Ptr(new Texture());
				text->create( math::Vector2<int>(m_Face->glyph->bitmap.width, m_Face->glyph->bitmap.rows), m_Face->glyph->bitmap.buffer);
											
				// now store character for later use
				Character character = {
					text,
					math::Vector2<int>(m_Face->glyph->bitmap.width, m_Face->glyph->bitmap.rows),
					math::Vector2<int>(m_Face->glyph->bitmap_left, m_Face->glyph->bitmap_top),
					m_Face->glyph->advance.x
				};
				m_Characters.insert(std::pair<char, Character>(c, character));
			}
			m_CharacterSize = charSize;
			return true;
		}


		/// Returns the size of the character
		/// \todo Why do we not get the information from getCharacter(c)
		inline math::Vector2<int> getCharacterSize(char c) final {
			 return m_Characters[c].size;
		}
			
		/// Returns the bearing of the character
		/// \todo Why do we not get the information from getCharacter(c)
		inline math::Vector2<int> getCharacterBearing(char c) final {
			 return m_Characters[c].bearing;
		}
		
		/// Returns the needed advancement after the character
		/// \todo Why do we not get the information from getCharacter(c)
		inline float getCharacterAdvance(char c) final {
			return m_Characters[c].advance >> 6;
		}
		
		/// Binds the charater-texture
		/// \todo Couldn't we move this to the RenderDevice
		inline void bindCharacterTexture(char c) final {
			if(m_Characters[c].texture) {
				m_Characters[c].texture->bind(0);
			} 
		}
		
		/// Returns the character size of this font
		float getFontSize() const final {
			return (float)(m_CharacterSize);
		}
		
	};
	

	
	
	
	
};

#endif