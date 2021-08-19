#pragma once
#include "Core.h"
#include "Shader.h"
#include "Projections.h"

#include <ft2build.h>
#include FT_FREETYPE_H

namespace QG
{
	struct Character {
		unsigned int TextureID; // ID handle of the glyph texture
		QM::vector<2, int>   Size;      // Size of glyph
		QM::vector<2, int>   Bearing;   // Offset from baseline to left/top of glyph
		unsigned int Advance;   // Horizontal offset to advance to next glyph
	};

	class Font
	{
	private:
		Shader m_shader;
		std::map<char, QG::Character> Characters;
	public:
		//load a font from a ttf file
		Font(std::string filePath);
		//access the font shader
		Shader& getShader();
		//get a specific character from this font
		Character getCharacter(char letter);
	};

}