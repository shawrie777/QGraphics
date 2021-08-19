#pragma once
#include "Core.h"
#include "Material.h"

namespace QG
{
	class Vertex
	{
		friend class VertexBuffer;
	private:
		QM::vector<3> position;
		QM::vector<2> texCoords;
		QM::vector<3> normal;

		std::vector<float> getFloats();
	public:
		//create a vertex, consisting of position, texture coordinates, and a normal vector
		Vertex();
		//create a vertex, consisting of position, texture coordinates, and a normal vector
		Vertex(QM::vector<3> pos);
		//create a vertex, consisting of position, texture coordinates, and a normal vector
		Vertex(QM::vector<3> pos, QM::vector<2> tex, QM::vector<3> norm);
		//create a vertex, consisting of position, texture coordinates, and a normal vector
		Vertex(float x, float y, float z);

		QM::vector<3> getPosition();
		QM::vector<2> getTexCoords();
		QM::vector<3> getNormal();

		void setPosition(QM::vector<3> pos);
		void setTexCoords(QM::vector<2> coords);
		void setNormal(QM::vector<3> norm);
	};

	//gets the distance between the positions of two vertices
	float dist(Vertex& v1, Vertex& v2);
}