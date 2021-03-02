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
		Material* material;
		QM::vector<2> texCoords;
		QM::vector<3> normal;
		int state = 7;

		std::vector<float> getFloats();
	public:
		Vertex();
		Vertex(QM::vector<3> pos, Material Mat);
		Vertex(QM::vector<3> pos, Material Mat, QM::vector<2> tex, QM::vector<3> norm);
		Vertex(float x, float y, float z);

		bool usingTexCoords();
		bool usingNormal();

		void disableTexCoords();
		void disableNormal();

		QM::vector<3> getPosition();
		Material* getMaterial();
		QM::vector<2> getTexCoords();
		QM::vector<3> getNormal();

		void setPosition(QM::vector<3> pos);
		void setMaterial(Material mat);
		void setTexCoords(QM::vector<2> coords);
		void setNormal(QM::vector<3> norm);
	};


	float dist(Vertex& v1, Vertex& v2);
}