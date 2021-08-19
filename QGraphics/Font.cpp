#include "Font.h"
#include "Window.h"

namespace QG
{
	Font::Font(std::string filePath): m_shader("F:/C++/QGraphics/QGraphics/Text.vs", "F:/C++/QGraphics/QGraphics/Text.fs")
	{
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

        QG::Projection proj(0, getWindow()->getWidth(), 0, getWindow()->getHeight(), -1, 1);
        m_shader.use();
        m_shader.setMatrix<4,4>("projection", proj);

        FT_Library ft;
        // All functions return a value different than 0 whenever an error occurred
        if (FT_Init_FreeType(&ft))
            throw("ERROR::FREETYPE: Could not init FreeType Library");

        // find path to font
        std::string font_name = filePath;
        if (font_name.empty())
            throw("ERROR::FREETYPE: Failed to load font_name");

        // load font as face
        FT_Face face;
        if (FT_New_Face(ft, font_name.c_str(), 0, &face))
            throw("ERROR::FREETYPE: Failed to load font");
        else {
            // set size to load glyphs as
            FT_Set_Pixel_Sizes(face, 0, 48);

            // disable byte-alignment restriction
            glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

            // load first 128 characters of ASCII set
            for (unsigned char c = 0; c < 128; c++)
            {
                // Load character glyph 
                if (FT_Load_Char(face, c, FT_LOAD_RENDER))
                {
                    std::cout << "ERROR::FREETYTPE: Failed to load Glyph" << std::endl;
                    continue;
                }
                // generate texture
                unsigned int texture;
                glGenTextures(1, &texture);
                glBindTexture(GL_TEXTURE_2D, texture);
                glTexImage2D(
                    GL_TEXTURE_2D,
                    0,
                    GL_RED,
                    face->glyph->bitmap.width,
                    face->glyph->bitmap.rows,
                    0,
                    GL_RED,
                    GL_UNSIGNED_BYTE,
                    face->glyph->bitmap.buffer
                );
                // set texture options
                glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
                glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
                glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
                glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
                // now store character for later use
                QG::Character character = {
                    texture,
                    QM::vector<2,int>(face->glyph->bitmap.width, face->glyph->bitmap.rows),
                    QM::vector<2,int>(face->glyph->bitmap_left, face->glyph->bitmap_top),
                    static_cast<unsigned int>(face->glyph->advance.x)
                };
                Characters.insert(std::pair<char, QG::Character>(c, character));
            }
            glBindTexture(GL_TEXTURE_2D, 0);
        }
        // destroy FreeType once we're finished
        FT_Done_Face(face);
        FT_Done_FreeType(ft);
	}
    Shader& Font::getShader()
    {
        return m_shader;
    }
    Character Font::getCharacter(char letter)
    {
        return Characters[letter];
    }
}