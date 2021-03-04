#pragma once
#include "Asset.h"

namespace QG
{
	class cube : public Asset
	{
	public:
		cube();
	};

	class sphere :public Asset
	{
	public:
		sphere();
	};

	class torus : public Asset
	{
	private:
		float m_ratio;
		float torusDist(QG::Vertex& A, QG::Vertex& B);
	public:
		torus(float ratio = 1.5f);
	};

	class tetrahedron : public Asset
	{
	private:
		std::vector<QM::vector<3>> norms;
	public:
		tetrahedron();
	};

	class octahedron :public Asset
	{
	private:
		std::vector<QM::vector<3>> norms;
	public:
		octahedron();
	};

	class icosohedron : public Asset
	{
	private:
		std::vector<QM::vector<3>> norms;
	public:
		icosohedron();
	};
	
	class dodecahedron : public Asset
	{
	private:
		std::vector<QM::vector<3>> norms;
	public:
		dodecahedron();
	};

}