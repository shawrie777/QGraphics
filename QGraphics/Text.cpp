#include "Text.h"

namespace Texts
{
	std::vector<QG::Text*> Texts;
}

namespace QG
{
	Text::Text() : m_font(nullptr), m_string(""), m_col(BLACK), m_position(QM::vector<2>()), m_scale(1.0f)
	{
		Texts::Texts.push_back(this);

		glGenVertexArrays(1, &VAO);
		glGenBuffers(1, &VBO);
		glBindVertexArray(VAO);
		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 6 * 4, NULL, GL_DYNAMIC_DRAW);
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), 0);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindVertexArray(0);
	}

	Text::Text(std::string string) : m_font(nullptr), m_string(string), m_col(BLACK), m_position(QM::vector<2>()),
		m_scale(1.0f)
	{
		Texts::Texts.push_back(this);

		glGenVertexArrays(1, &VAO);
		glGenBuffers(1, &VBO);
		glBindVertexArray(VAO);
		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 6 * 4, NULL, GL_DYNAMIC_DRAW);
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), 0);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindVertexArray(0);
	}

	Text::Text(std::string string, Font* font) :
		m_font(font), m_string(string), m_col(BLACK), m_position(QM::vector<2>()), m_scale(1.0f)
	{
		Texts::Texts.push_back(this);

		glGenVertexArrays(1, &VAO);
		glGenBuffers(1, &VBO);
		glBindVertexArray(VAO);
		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 6 * 4, NULL, GL_DYNAMIC_DRAW);
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), 0);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindVertexArray(0);
	}

	Text::~Text()
	{
		for (auto i = Texts::Texts.begin(); i != Texts::Texts.end(); i++)
			if (*i == this)
			{
				Texts::Texts.erase(i);
				break;
			}
	}

	void Text::write()
	{
		if (!m_font)
			throw("No font selected.");

		 //activate corresponding render state	
		m_font->getShader().use();
		m_font->getShader().setVector<4>("textColor", m_col);
		glActiveTexture(GL_TEXTURE0);
		glBindVertexArray(VAO);

		float x = m_position.get(1);
		// iterate through all characters
		std::string::const_iterator c;
		for (c = m_string.begin(); c != m_string.end(); c++)
		{
			QG::Character ch = m_font->getCharacter(*c);

			float xpos = x + ch.Bearing.get(1) * m_scale;
			float ypos = m_position.get(2) - (ch.Size.get(2) - ch.Bearing.get(2)) * m_scale;

			float h = ch.Size.get(2) * m_scale;
			float w = ch.Size.get(1) * m_scale;
			// update VBO for each character
			float vertices[6][4] = {
				{ xpos,     ypos + h,   0.0f, 0.0f },
				{ xpos,     ypos,       0.0f, 1.0f },
				{ xpos + w, ypos,       1.0f, 1.0f },

				{ xpos,     ypos + h,   0.0f, 0.0f },
				{ xpos + w, ypos,       1.0f, 1.0f },
				{ xpos + w, ypos + h,   1.0f, 0.0f }
			};
			// render glyph texture over quad
			glBindTexture(GL_TEXTURE_2D, ch.TextureID);
			// update content of VBO memory
			glBindBuffer(GL_ARRAY_BUFFER, VBO);
			glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices); // be sure to use glBufferSubData and not glBufferData

			glBindBuffer(GL_ARRAY_BUFFER, 0);
			// render quad
			glDrawArrays(GL_TRIANGLES, 0, 6);
			// now advance cursors for next glyph (note that advance is number of 1/64 pixels)
			x += (ch.Advance >> 6) * m_scale; // bitshift by 6 to get value in pixels (2^6 = 64 (divide amount of 1/64th pixels by 64 to get amount of pixels))
		}
		glBindVertexArray(0);
		glBindTexture(GL_TEXTURE_2D, 0);
	}
	void Text::write(Font* font)
	{
		m_font = font;
		write();
	}
	void Text::write(QM::vector<2> position)
	{
		m_position = position;
		write();
	}
	void Text::setFont(Font* font)
	{
		m_font = font;
	}
	void Text::setString(std::string string)
	{
		m_string = string;
	}
	void Text::setColour(Colour col)
	{
		m_col = col;
	}
	void Text::setPosition(QM::vector<2> pos)
	{
		m_position = pos;
	}
	void Text::setScale(float scale)
	{
		m_scale = scale;
	}
	Font* Text::getFont()
	{
		return m_font;
	}
	std::string Text::getString()
	{
		return m_string;
	}
	Colour Text::getColour()
	{
		return m_col;
	}
	QM::vector<2> Text::getPosition()
	{
		return m_position;
	}
	float Text::getScale()
	{
		return m_scale;
	}
	bool Text::isShown() const
	{
		return m_shown;
	}
	void Text::show()
	{
		m_shown = true;
	}
	void Text::hide()
	{
		m_shown = false;
	}
}