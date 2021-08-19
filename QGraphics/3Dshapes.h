#pragma once
#include "Asset.h"

namespace QG
{
	class cube : public Asset
	{
	public:
		//create 2x2x2 cube
		//centered at origin
		cube();
	};

	class sphere :public Asset
	{
	public:
		//create sphere with radius 1
		//approximation using 32 rows and 64 columns
		sphere();
	};

	class torus : public Asset
	{
	private:
		float m_ratio;
	public:
		//create a torus
		//the ratio is between distance to centre of tube
		//and the radius of the tube
		torus(float ratio = 1.5f);
	};

	class tetrahedron : public Asset
	{
	private:
		std::vector<QM::vector<3>> norms;
	public:
		//create a regular tetrahedron
		tetrahedron();
	};

	class octahedron :public Asset
	{
	private:
		std::vector<QM::vector<3>> norms;
	public:
		//create a regular octahedron
		octahedron();
	};

	class icosohedron : public Asset
	{
	private:
		std::vector<QM::vector<3>> norms;
	public:
		//create an regular icosohedron
		icosohedron();
	};
	
	class dodecahedron : public Asset
	{
	private:
		std::vector<QM::vector<3>> norms;
	public:
		//create a regular dodecahedron
		dodecahedron();
	};

}