#pragma once
#include "Font.h"
#include "Colour.h"

namespace QG
{
	class Text
	{
	private:
		Font* m_font;
		std::string m_string;
		QG::Colour m_col;
		QM::vector<2> m_position;
		float m_scale;

		unsigned int VAO = 0;
		unsigned int VBO = 0;

		bool m_shown = true;
	public:
		//create a default text object
		//a font must be added before writing
		Text();
		//create a text object with the given string
		Text(std::string string);
		//create a text object with the given string and font
		Text(std::string string, Font* font);
		~Text();

		//write the text using the assigned font
		void write();
		//assign the given font and then write the text
		void write(Font* font);
		//set the position of the text in screen coordinates,
		//then write the text
		void write(QM::vector<2> position);

		//set the font
		//must be set before writing
		void setFont(Font* font);
		void setString(std::string string);
		void setColour(Colour col);
		//set the position of the text in screen coordinates
		void setPosition(QM::vector<2> pos);
		void setScale(float scale);

		Font* getFont();
		std::string getString();
		Colour getColour();
		QM::vector<2> getPosition();
		float getScale();

		//determine if the text is currently rendered
		bool isShown() const;
		//causes the text to be shown in subsequent frames
		void show();
		//hides the text in subsequent frames
		void hide();
	};

}

namespace Texts
{
	extern std::vector<QG::Text*> Texts;
}