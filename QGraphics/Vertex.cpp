#include "Vertex.h"

namespace QG
{
	std::vector<float> Vertex::getFloats()
	{
		std::vector<float> result;
		result.push_back(position.get(1));
		result.push_back(position.get(2));
		result.push_back(position.get(3));
		
		//if (usingColour())
		//{
		//	result.push_back(colour.get(1));
		//	result.push_back(colour.get(2));
		//	result.push_back(colour.get(3));
		//	result.push_back(colour.get(4));
		//}

		if (usingTexCoords())
		{
			result.push_back(texCoords.get(1));
			result.push_back(texCoords.get(2));
		}

		if (usingNormal())
		{
			result.push_back(normal.get(1));
			result.push_back(normal.get(2));
			result.push_back(normal.get(3));
		}

		return result;
	}

	Vertex::Vertex() : Vertex(QM::vector<3>(0.0f, 0.0f, 0.0f), Material(GREY,GREY,0.0f))
	{
	}

	Vertex::Vertex(QM::vector<3> pos, Material mat): Vertex(pos,mat,QM::vector<2>(0.0f,0.0f), QM::vector<3>(0.0f,0.0f,0.0f))
	{
		state = 4;
	}

	Vertex::Vertex(QM::vector<3> pos, Material mat, QM::vector<2> tex, QM::vector<3> norm): material(&mat)
	{
		state = 7;
		position = pos;
		texCoords = tex;
		normal = norm;
	}

	Vertex::Vertex(float x, float y, float z) : Vertex(QM::vector<3>(x, y, z), Material(GREY,GREY,0.0f))
	{
	}

	bool Vertex::usingTexCoords()
	{
		return state % 4 > 1;
	}
	bool Vertex::usingNormal()
	{
		return state % 2 == 1;
	}

	void Vertex::disableTexCoords()
	{
		if (usingTexCoords())
			state -= 2;
	}

	void Vertex::disableNormal()
	{
		if (usingNormal())
			state -= 1;
	}

	QM::vector<3> Vertex::getPosition()
	{
		return position;
	}
	Material* Vertex::getMaterial()
	{
		return material;
	}
	QM::vector<2> Vertex::getTexCoords()
	{
		return texCoords;
	}
	QM::vector<3> Vertex::getNormal()
	{
		return normal;
	}
	void Vertex::setPosition(QM::vector<3> pos = QM::vector<3>(0,0,0))
	{
		position = pos;
	}

	void Vertex::setMaterial(Material mat)
	{
		material = &mat;
	}
	void Vertex::setTexCoords(QM::vector<2> coords)
	{
		if (!usingTexCoords())
			state += 2;
		texCoords = coords;
	}

	void Vertex::setNormal(QM::vector<3> norm)
	{
		if (!usingNormal())
			state += 1;
		normal = norm.normalise();
	}
	float dist(Vertex& v1, Vertex& v2)
	{
		return QM::dist<3,float>(v1.getPosition(),v2.getPosition());
	}
}