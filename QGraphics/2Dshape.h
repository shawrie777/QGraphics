#pragma once
#include "Asset.h"

namespace QG
{
	class shape2Dbase : public Asset
	{

	};

	template<int edges>
	class shape2D : public shape2Dbase
	{
	protected:
		QM::vector<3> normal;
	public:
		void build() override;
		shape2D();
	};

	template<int edges>
	void shape2D<edges>::build()
	{
		if (vertices.vertexCount() < 3)
			throw("There aren't enough vertices to create a shape.");
		
		//for (auto& x : vertices)
		//	if (std::abs(static_cast<QM::vector<3>>(x.getPosition() - vertices[0].getPosition()) * normal) > 0.01)
		//		throw("Not all points are in the same plane.");

		Asset::build();
	}

	template<int edges>
	shape2D<edges>::shape2D()
	{
		if (edges < 3)
			throw("There aren't enough edges to create a shape.");

		double angle = 360.0 / edges;
		QM::vector<3> pos(1.0f, 0.0f, 0.0f);
		QM::vector<3> norm(0.0f, 0.0f, 1.0f);

		QM::matrix<3, 3> rot = QM::identity<3>();
		rot.set(1, 1, (float)cos(QM::rad(angle)));
		rot.set(1, 2, -(float)sin(QM::rad(angle)));
		rot.set(2, 1, (float)sin(QM::rad(angle)));
		rot.set(2, 2, (float)cos(QM::rad(angle)));

		//just for squares
		QM::matrix<2, 2> A;
		A.set(1, 1, 0.5);
		A.set(1, 2, -0.5);
		A.set(2, 1, 0.5);
		A.set(2, 2, 0.5);

		QM::vector<2> B;
		B.set(1, 0.5);
		B.set(2, 0.5);

		for (int i = 0; i < edges; i++)
		{
			QM::vector<2> Tcoord((pos.get(1) + 1.0f)/2.0f, (pos.get(2) + 1.0f)/2.0f);
			if (edges == 4)
				Tcoord = A * Tcoord + B;
			vertices.push_back(QG::Vertex(pos, Tcoord, norm));
			pos = rot * pos;
			indices.AddIndices({ i });
		}

		QM::vector<3> planeVec1 = vertices[2].getPosition() - vertices[1].getPosition();
		QM::vector<3> planeVec2 = vertices[2].getPosition() - vertices[0].getPosition();

		normal = planeVec1.cross(planeVec2).normalise();

		drawType = GL_TRIANGLE_FAN;

	}


	class circle : public shape2D<45>
	{

	};
}
