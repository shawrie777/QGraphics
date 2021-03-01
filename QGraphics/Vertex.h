#pragma once
#include "Core.h"
#include "Colour.h"

namespace QG
{
	class Vertex
	{
		friend class VertexBuffer;
	private:
		QM::vector<3> position;
		Colour colour;
		QM::vector<2> texCoords;
		QM::vector<3> normal;
		int state = 7;

		std::vector<float> getFloats();
	public:
		Vertex();
		Vertex(QM::vector<3> pos, Colour col = GREY);
		Vertex(QM::vector<3> pos, Colour col, QM::vector<2> tex, QM::vector<3> norm);
		Vertex(float x, float y, float z);
		

		bool usingColour();
		bool usingTexCoords();
		bool usingNormal();

		void disableColour();
		void disableTexCoords();
		void disableNormal();

		QM::vector<3> getPosition();
		Colour getColour();
		QM::vector<2> getTexCoords();
		QM::vector<3> getNormal();

		void setPosition(QM::vector<3> pos);
		void setColour(Colour col);
		void setTexCoords(QM::vector<2> coords);
		void setNormal(QM::vector<3> norm);

		//add transforms
	};


	float dist(Vertex& v1, Vertex& v2);
}