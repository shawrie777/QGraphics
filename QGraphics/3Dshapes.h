#pragma once
#include "Asset.h"

namespace QG
{
	class cube : public Asset
	{
	public:
		cube();
		void setFaceColour(int face, Colour col);
		void setColour(Colour col);
	};

	class sphere :public Asset
	{
	public:
		sphere();
		void colourSection(QM::vector<3> centre, float radius, Colour col);
		void setColour(Colour col);
	};

	class torus : public Asset
	{
	private:
		float m_ratio;
		float torusDist(QG::Vertex& A, QG::Vertex& B);
	public:
		torus(float ratio = 1.5f);
		void colourSection(QM::vector<3> centre, float radius, Colour col);
		void setColour(Colour col);
	};

	class tetrahedron : public Asset
	{
	private:
		std::vector<QM::vector<3>> norms;
	public:
		tetrahedron();
		void setFaceColour(int face, Colour col);
		void setColour(Colour col);
	};

	class octahedron :public Asset
	{
	private:
		std::vector<QM::vector<3>> norms;
	public:
		octahedron();
		void setFaceColour(int face, Colour col);
		void setColour(Colour col);
	};

	class icosohedron : public Asset
	{
	private:
		std::vector<QM::vector<3>> norms;
	public:
		icosohedron();
		void setFaceColour(int face, Colour col);
		void setColour(Colour col);
	};
	
	class dodecahedron : public Asset
	{
	private:
		std::vector<QM::vector<3>> norms;
	public:
		dodecahedron();
		void setFaceColour(int face, Colour col);
		void setColour(Colour col);
	};

}