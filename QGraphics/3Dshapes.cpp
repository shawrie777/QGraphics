#include "3Dshapes.h"
#include <cassert>

namespace QG
{
	cube::cube()
	{
		QM::vector<3> frontNorm(0.0f, 0.0f, 1.0f);
		QM::vector<3> backNorm(0.0f, 0.0f, -1.0f);
		QM::vector<3> topNorm(0.0f, 1.0f, 0.0f);
		QM::vector<3> bottomNorm(0.0f, -1.0f, 0.0f);
		QM::vector<3> rightNorm(1.0f, 0.0f, 0.0f);
		QM::vector<3> leftNorm(-1.0f, 0.0f, 0.0f);

		QM::vector<2> zero(0.0f, 0.0f);

		QM::vector<3> TFR( 1.0f,  1.0f,  1.0f);
		QM::vector<3> TFL(-1.0f,  1.0f,  1.0f);
		QM::vector<3> TBR( 1.0f,  1.0f, -1.0f);
		QM::vector<3> TBL(-1.0f,  1.0f, -1.0f);
		QM::vector<3> BFR( 1.0f, -1.0f,  1.0f);
		QM::vector<3> BFL(-1.0f, -1.0f,  1.0f);
		QM::vector<3> BBR( 1.0f, -1.0f, -1.0f);
		QM::vector<3> BBL(-1.0f, -1.0f, -1.0f);

		vertices.push_back(QG::Vertex(TFR, QM::vector<2>(0.5f, 0.5f), topNorm));
		vertices.push_back(QG::Vertex(TFR, QM::vector<2>(0.5f, 0.5f), frontNorm));
		vertices.push_back(QG::Vertex(TFR, QM::vector<2>(0.5f, 0.5f), rightNorm)); //2.

		vertices.push_back(QG::Vertex(TFL, QM::vector<2>(0.25f, 0.5f), topNorm));
		vertices.push_back(QG::Vertex(TFL, QM::vector<2>(0.25f, 0.5f), frontNorm));
		vertices.push_back(QG::Vertex(TFL, QM::vector<2>(0.25f, 0.5f), leftNorm)); //5

		vertices.push_back(QG::Vertex(TBR, QM::vector<2>(0.5f, 0.25f), topNorm));
		vertices.push_back(QG::Vertex(TBR, QM::vector<2>(0.75f, 0.5f), backNorm));
		vertices.push_back(QG::Vertex(TBR, QM::vector<2>(0.75f, 0.5f), rightNorm)); //8

		vertices.push_back(QG::Vertex(TBL, QM::vector<2>(0.25f, 0.25f), topNorm));
		vertices.push_back(QG::Vertex(TBL, QM::vector<2>(1.0f, 0.5f), backNorm));
		vertices.push_back(QG::Vertex(TBL, QM::vector<2>(0.0f, 0.5f), leftNorm)); //11
		
		vertices.push_back(QG::Vertex(BFR, QM::vector<2>(0.5f, 0.75f), bottomNorm));
		vertices.push_back(QG::Vertex(BFR, QM::vector<2>(0.5f, 0.75f), frontNorm));
		vertices.push_back(QG::Vertex(BFR, QM::vector<2>(0.5f, 0.75f), rightNorm)); //14

		vertices.push_back(QG::Vertex(BFL, QM::vector<2>(0.25f, 0.75f), bottomNorm));
		vertices.push_back(QG::Vertex(BFL, QM::vector<2>(0.25f, 0.75f), frontNorm));
		vertices.push_back(QG::Vertex(BFL, QM::vector<2>(0.25f, 0.75f), leftNorm)); //17
		
		vertices.push_back(QG::Vertex(BBR, QM::vector<2>(0.5f, 1.0f), bottomNorm));
		vertices.push_back(QG::Vertex(BBR, QM::vector<2>(0.75f, 0.75f), backNorm));
		vertices.push_back(QG::Vertex(BBR, QM::vector<2>(0.75f, 0.75f), rightNorm)); //20

		vertices.push_back(QG::Vertex(BBL, QM::vector<2>(0.25f, 1.0f), bottomNorm));
		vertices.push_back(QG::Vertex(BBL, QM::vector<2>(1.0f, 0.75f), backNorm));
		vertices.push_back(QG::Vertex(BBL, QM::vector<2>(0.0f, 0.75f), leftNorm)); //23
		
		indices.AddIndices({16,13,1,16,4,1,3,9,6,3,6,0,14,2,8,14,8,20,23,11,5,23,17,5,21,15,12,21,12,18,22,19,10,10,7,19});		
	}

	tetrahedron::tetrahedron()
	{
		QM::vector<3>point0(0.0f, 1.0f, 0.0f);
		QM::vector<3>point1(sqrt(8.0f)/3.0f, -1.0f/3.0f, 0.0f);
		QM::vector<3>point2(-sqrt(2.0f)/3.0f, -1.0f / 3.0f, sqrt(2.0f/3.0f));
		QM::vector<3>point3(-sqrt(2.0f) / 3.0f, -1.0f / 3.0f, -sqrt(2.0f / 3.0f));

		QM::vector<3> side0 = point1 - point0;
		QM::vector<3> side1 = point2 - point0;
		QM::vector<3> side2 = point3 - point0;
		QM::vector<3> side3 = point2 - point1;
		QM::vector<3> side4 = point3 - point1;

		QM::vector<3>norm0 = side0.cross(side1);
		if (norm0.get(2) < 0)
			norm0 = -1 * norm0;
		norms.push_back(norm0);
		QM::vector<3>norm1 = side0.cross(side2);
		if (norm1.get(2) < 0)
			norm1 = -1 * norm1;
		norms.push_back(norm1);
		QM::vector<3>norm2 = side1.cross(side2);
		if (norm2.get(2) < 0)
			norm2 = -1 * norm2;
		norms.push_back(norm2);
		QM::vector<3>norm3 = side3.cross(side4);
		if (norm3.get(2) > 0)
			norm3 = -1 * norm3;
		norms.push_back(norm3);

		float h = sqrt(3.0f) / 4.0f;

		vertices.push_back(QG::Vertex(point0, QM::vector<2>(0.0f, 0.5f), norm0));
		vertices.push_back(QG::Vertex(point1, QM::vector<2>(h, 0.25f), norm0));
		vertices.push_back(QG::Vertex(point2, QM::vector<2>(h, 0.75f), norm0));//2

		vertices.push_back(QG::Vertex(point0, QM::vector<2>(2.0f * h, 0.0f), norm1));
		vertices.push_back(QG::Vertex(point1, QM::vector<2>(h, 0.25f), norm1));
		vertices.push_back(QG::Vertex(point3, QM::vector<2>(2.0f * h, 0.5f), norm1));//5

		vertices.push_back(QG::Vertex(point0, QM::vector<2>(2.0f * h, 1.0f), norm2));
		vertices.push_back(QG::Vertex(point2, QM::vector<2>(h, 0.75f), norm2));
		vertices.push_back(QG::Vertex(point3, QM::vector<2>(2.0f * h, 0.5f), norm2));//8

		vertices.push_back(QG::Vertex(point1, QM::vector<2>(h, 0.25f), norm3));
		vertices.push_back(QG::Vertex(point2, QM::vector<2>(h, 0.75f), norm3));
		vertices.push_back(QG::Vertex(point3, QM::vector<2>(2.0f * h, 0.5f), norm3));//11

		indices.AddIndices({ 0,1,2,3,4,5,6,7,8,9,10,11 });
	}
	
	octahedron::octahedron()
	{
		QM::vector<3>point0( 0.0f,  1.0f,  0.0f);
		QM::vector<3>point1( 1.0f,  0.0f,  0.0f);
		QM::vector<3>point2( 0.0f,  0.0f,  1.0f);
		QM::vector<3>point3(-1.0f,  0.0f,  0.0f);
		QM::vector<3>point4( 0.0f,  0.0f, -1.0f);
		QM::vector<3>point5( 0.0f, -1.0f,  0.0f);

		QM::vector<2> zero(0.0f, 0.0f);
		float h = 2.0f / (3.0f * sqrt(3.0f));

		norms.push_back(QM::vector<3>(1.0f, 1.0f, 1.0f));
		norms.push_back(QM::vector<3>(-1.0f, 1.0f, 1.0f));
		norms.push_back(QM::vector<3>(-1.0f, 1.0f, -1.0f));
		norms.push_back(QM::vector<3>(1.0f, 1.0f, -1.0f));
		norms.push_back(QM::vector<3>(1.0f, -1.0f, 1.0f));
		norms.push_back(QM::vector<3>(-1.0f, -1.0f, 1.0f));
		norms.push_back(QM::vector<3>(-1.0f, -1.0f, -1.0f));
		norms.push_back(QM::vector<3>(1.0f, -1.0f, -1.0f));

		vertices.push_back(QG::Vertex(point0, QM::vector<2>(h / 2.0f, 2.0f/3.0f), norms[0]));
		vertices.push_back(QG::Vertex(point1, QM::vector<2>(h, 1.0f), norms[0]));
		vertices.push_back(QG::Vertex(point2, QM::vector<2>(0.0f, 1.0f), norms[0])); //2

		vertices.push_back(QG::Vertex(point3, QM::vector<2>(h, 1.0f /3.0f), norms[1]));
		vertices.push_back(QG::Vertex(point0, QM::vector<2>(h/2.0f, 0.0f), norms[1]));
		vertices.push_back(QG::Vertex(point2, QM::vector<2>(1.5f * h, 0.0f), norms[1])); //5

		vertices.push_back(QG::Vertex(point3, QM::vector<2>(h, 1.0f / 3.0f), norms[2]));
		vertices.push_back(QG::Vertex(point0, QM::vector<2>(h / 2.0f, 2.0f / 3.0f), norms[2]));
		vertices.push_back(QG::Vertex(point4, QM::vector<2>(1.5f *h, 2.0f/3.0f), norms[2])); //8

		vertices.push_back(QG::Vertex(point1, QM::vector<2>(h, 1.0f), norms[3]));
		vertices.push_back(QG::Vertex(point0, QM::vector<2>(h / 2.0f, 2.0f / 3.0f), norms[3]));
		vertices.push_back(QG::Vertex(point4, QM::vector<2>(1.5f * h, 2.0f / 3.0f), norms[3])); //11

		vertices.push_back(QG::Vertex(point5, QM::vector<2>(2.0f * h, 1.0f / 3.0f), norms[4]));
		vertices.push_back(QG::Vertex(point1, QM::vector<2>(2.5f * h, 0.0f), norms[4]));
		vertices.push_back(QG::Vertex(point2, QM::vector<2>(1.5f * h, 0.0f), norms[4])); //14

		vertices.push_back(QG::Vertex(point3, QM::vector<2>(h, 1.0f / 3.0f), norms[5]));
		vertices.push_back(QG::Vertex(point5, QM::vector<2>(2.0f * h, 1.0f / 3.0f), norms[5]));
		vertices.push_back(QG::Vertex(point2, QM::vector<2>(1.5f * h, 0.0f), norms[5])); //17

		vertices.push_back(QG::Vertex(point3, QM::vector<2>(h, 1.0f / 3.0f), norms[6]));
		vertices.push_back(QG::Vertex(point5, QM::vector<2>(2.0f * h, 1.0f / 3.0f), norms[6]));
		vertices.push_back(QG::Vertex(point4, QM::vector<2>(1.5f * h, 2.0f / 3.0f), norms[6])); //20

		vertices.push_back(QG::Vertex(point1, QM::vector<2>(h, 1.0f), norms[7]));
		vertices.push_back(QG::Vertex(point5, QM::vector<2>(2.0f *h , 1.0f), norms[7]));
		vertices.push_back(QG::Vertex(point4, QM::vector<2>(1.5f * h, 2.0f / 3.0f), norms[7])); //23

		indices.AddIndices({ 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23 });
	}

	dodecahedron::dodecahedron()
	{
		float phi = (1.0f + sqrt(5.0f)) / 2.0f;
		float s = 2.0f / (7.0f * phi + 5.0f);
		float d = phi * s;
		float h = sqrt(phi * phi - 0.25f) * s;
		float t = sqrt(4.0f - (phi * phi)) * s / 2.0f;

		norms.push_back(QM::vector<3>(1.0f, phi, 0.0f));
		norms.push_back(QM::vector<3>(1.0f, -phi, 0.0f));
		norms.push_back(QM::vector<3>(-1.0f, phi, 0.0f));
		norms.push_back(QM::vector<3>(-1.0f, -phi, 0.0f));
		norms.push_back(QM::vector<3>(0.0f, 1.0f, phi));
		norms.push_back(QM::vector<3>(0.0f, 1.0f, -phi));
		norms.push_back(QM::vector<3>(0.0f, -1.0f, phi));
		norms.push_back(QM::vector<3>(0.0f, -1.0f, -phi));
		norms.push_back(QM::vector<3>(phi, 0.0f, 1.0f));
		norms.push_back(QM::vector<3>(phi, 0.0f, -1.0f));
		norms.push_back(QM::vector<3>(-phi, 0.0f, 1.0f));
		norms.push_back(QM::vector<3>(-phi, 0.0f, -1.0f));

		QM::vector<3>point00(1.0f, 1.0f, 1.0f);
		QM::vector<3>point01(-1.0f, 1.0f, 1.0f);
		QM::vector<3>point02(1.0f, -1.0f, 1.0f);
		QM::vector<3>point03(1.0f, 1.0f, -1.0f);
		QM::vector<3>point04(1.0f, -1.0f, -1.0f);
		QM::vector<3>point05(-1.0f, 1.0f, -1.0f);
		QM::vector<3>point06(-1.0f, -1.0f, -1.0f);
		QM::vector<3>point07(-1.0f, -1.0f, 1.0f);

		QM::vector<3>point08(1.0f / phi, 0.0f, phi);
		QM::vector<3>point09(-1.0f / phi, 0.0f, phi);
		QM::vector<3>point10(1.0f / phi, 0.0f, -phi);
		QM::vector<3>point11(-1.0f / phi, 0.0f, -phi);

		QM::vector<3>point12(0.0f, phi, 1.0f / phi);
		QM::vector<3>point13(0.0f, phi, -1.0f / phi);
		QM::vector<3>point14(0.0f, -phi, 1.0f / phi);
		QM::vector<3>point15(0.0f, -phi, -1.0f / phi);

		QM::vector<3>point16(phi, -1.0f / phi, 0.0f);
		QM::vector<3>point17(phi, 1.0f / phi, 0.0f);
		QM::vector<3>point18(-phi, 1.0f / phi, 0.0f);
		QM::vector<3>point19(-phi, -1.0f / phi, 0.0f);
		
		vertices.push_back(QG::Vertex(point00, QM::vector<2>(h - t, (2.5f * d) + (2.0f * s)), norms[0]));
		vertices.push_back(QG::Vertex(point17, QM::vector<2>(0.0f, (3.0f * d) + (1.5f * s)), norms[0]));
		vertices.push_back(QG::Vertex(point03, QM::vector<2>(0.0f, (3.0f * d) + (2.5f * s)), norms[0]));
		vertices.push_back(QG::Vertex(point13, QM::vector<2>(h - t, (3.5f * d) + (2.0f * s)), norms[0]));
		vertices.push_back(QG::Vertex(point12, QM::vector<2>(h, (3.0f * d) + (s * 2.0f)), norms[0]));

		vertices.push_back(QG::Vertex(point02, QM::vector<2>(h, 2.0f * d + s), norms[1]));
		vertices.push_back(QG::Vertex(point16, QM::vector<2>(h - t, 1.5f * d + s), norms[1]));
		vertices.push_back(QG::Vertex(point04, QM::vector<2>(h, d+s), norms[1]));
		vertices.push_back(QG::Vertex(point15, QM::vector<2>(2.0f * h - t, (3.0f * d + s)/2.0f), norms[1]));
		vertices.push_back(QG::Vertex(point14, QM::vector<2>(2.0f * h - t, 1.5f * (s + d)), norms[1]));

		vertices.push_back(QG::Vertex(point01, QM::vector<2>(2.0f * h - t, 2.5f * (d+s)), norms[2]));
		vertices.push_back(QG::Vertex(point12, QM::vector<2>(h, (3.0f * d) + (s * 2.0f)), norms[2]));
		vertices.push_back(QG::Vertex(point13, QM::vector<2>(h, (d + s) * 3.0f), norms[2]));
		vertices.push_back(QG::Vertex(point05, QM::vector<2>(2.0f * h - t, 1.0f), norms[2]));
		vertices.push_back(QG::Vertex(point18, QM::vector<2>(2.0f * h, (3.0f * d) + (2.5f * s)), norms[2]));

		vertices.push_back(QG::Vertex(point14, QM::vector<2>(2.0f * h, (2.0f * d) + (s / 2.0f)), norms[3]));
		vertices.push_back(QG::Vertex(point15, QM::vector<2>(2.0f * h - t, (3.0f * d + s) / 2.0f), norms[3]));
		vertices.push_back(QG::Vertex(point06, QM::vector<2>(2.0f * h, s/2.0f + d), norms[3]));
		vertices.push_back(QG::Vertex(point19, QM::vector<2>(3.0f * h - t, 1.5f * d), norms[3]));
		vertices.push_back(QG::Vertex(point07, QM::vector<2>(3.0f * h - t, 1.5f * d + s), norms[3]));

		vertices.push_back(QG::Vertex(point00, QM::vector<2>(h - t, (2.5f * d) + (2.0f * s)), norms[4]));
		vertices.push_back(QG::Vertex(point12, QM::vector<2>(h, (3.0f * d) + (s * 2.0f)), norms[4]));
		vertices.push_back(QG::Vertex(point01, QM::vector<2>(2.0f * h - t, 2.5f * (d + s)), norms[4]));
		vertices.push_back(QG::Vertex(point09, QM::vector<2>(2.0f * h - t, (2.5f * d) + (1.5f * s)), norms[4]));
		vertices.push_back(QG::Vertex(point08, QM::vector<2>(h, 2.0f * (d+s)), norms[4]));

		vertices.push_back(QG::Vertex(point13, QM::vector<2>(h, 0.0f), norms[5]));
		vertices.push_back(QG::Vertex(point03, QM::vector<2>(h - t, d/2.0f), norms[5]));
		vertices.push_back(QG::Vertex(point10, QM::vector<2>(h, d), norms[5]));
		vertices.push_back(QG::Vertex(point11, QM::vector<2>(2.0f * h - t, (d + s) /2.0f), norms[5]));
		vertices.push_back(QG::Vertex(point05, QM::vector<2>(2.0f * h - t, (d - s) / 2.0f), norms[5]));
		
		vertices.push_back(QG::Vertex(point09, QM::vector<2>(2.0f * h - t, (2.5f * d) + (1.5f * s)), norms[6]));
		vertices.push_back(QG::Vertex(point08, QM::vector<2>(h, 2.0f * (d + s)), norms[6]));
		vertices.push_back(QG::Vertex(point02, QM::vector<2>(h, 2.0f * d + s), norms[6]));
		vertices.push_back(QG::Vertex(point14, QM::vector<2>(2.0f * h - t, 1.5f * (s + d)), norms[6]));
		vertices.push_back(QG::Vertex(point07, QM::vector<2>(2.0f * h, (2.0f * d) + (1.5f * s)), norms[6]));
		
		vertices.push_back(QG::Vertex(point15, QM::vector<2>(2.0f * h - t, (3.0f * d + s) / 2.0f), norms[7]));
		vertices.push_back(QG::Vertex(point04, QM::vector<2>(h, d + s), norms[7]));
		vertices.push_back(QG::Vertex(point10, QM::vector<2>(h, d), norms[7]));
		vertices.push_back(QG::Vertex(point11, QM::vector<2>(2.0f * h - t, (d + s) / 2.0f), norms[7]));
		vertices.push_back(QG::Vertex(point06, QM::vector<2>(2.0f * h, s / 2.0f + d), norms[7]));

		vertices.push_back(QG::Vertex(point00, QM::vector<2>(h - t, (2.5f * d) + (2.0f * s)), norms[8]));
		vertices.push_back(QG::Vertex(point17, QM::vector<2>(0.0f, (2.0f * d) + (2.5f * s)), norms[8]));
		vertices.push_back(QG::Vertex(point16, QM::vector<2>(0.0f, (2.0f * d) + (1.5f * s)), norms[8]));
		vertices.push_back(QG::Vertex(point02, QM::vector<2>(h - t, (1.5f * d) + (2.0f * s)), norms[8]));
		vertices.push_back(QG::Vertex(point08, QM::vector<2>(h, 2.0f * (d + s)), norms[8]));
		
		vertices.push_back(QG::Vertex(point03, QM::vector<2>(t, (d+s)/2.0f), norms[9]));
		vertices.push_back(QG::Vertex(point17, QM::vector<2>(0.0f, s/2.0f + d), norms[9]));
		vertices.push_back(QG::Vertex(point16, QM::vector<2>(t, (3.0f * d + s) / 2.0f), norms[9]));
		vertices.push_back(QG::Vertex(point04, QM::vector<2>(h, d + s), norms[9]));
		vertices.push_back(QG::Vertex(point10, QM::vector<2>(h, d), norms[9]));

		vertices.push_back(QG::Vertex(point01, QM::vector<2>(2.0f * h - t, 2.5f * (d + s)), norms[10]));
		vertices.push_back(QG::Vertex(point18, QM::vector<2>(3.0f * h - (2.0f * t), (3.0f * d) + (2.0f * s)), norms[10]));
		vertices.push_back(QG::Vertex(point19, QM::vector<2>(3.0f * h - t, (2.5f * d) + (2.0f * s)), norms[10]));
		vertices.push_back(QG::Vertex(point07, QM::vector<2>((3.0f * h) - (2.0f * t), (d + s) * 2.0f), norms[10]));
		vertices.push_back(QG::Vertex(point09, QM::vector<2>(2.0f * h - t, (2.5f * d) + (1.5f * s)), norms[10]));
		
		vertices.push_back(QG::Vertex(point05, QM::vector<2>(2.0f * h, s/2.0f), norms[11]));
		vertices.push_back(QG::Vertex(point18, QM::vector<2>(3.0f * h - t, d / 2.0f), norms[11]));
		vertices.push_back(QG::Vertex(point19, QM::vector<2>(3.0f * h - t, d/2.0f + s), norms[11]));
		vertices.push_back(QG::Vertex(point06, QM::vector<2>(2.0f * h, s / 2.0f + d), norms[11]));
		vertices.push_back(QG::Vertex(point11, QM::vector<2>(2.0f * h - t, (d + s) / 2.0f), norms[11]));

		indices.AddIndices({ 0,1,2,0,2,3,0,3,4 });
		indices.AddIndices({ 5,6,7,5,7,8,5,8,9 });
		indices.AddIndices({ 10,11,12,10,12,13,10,13,14 });
		indices.AddIndices({ 15,16,17,15,17,18,15,18,19 });
		indices.AddIndices({ 20,21,22,20,22,23,20,23,24 });
		indices.AddIndices({ 25,26,27,25,27,28,25,28,29 });
		indices.AddIndices({ 30,31,32,30,32,33,30,33,34 });
		indices.AddIndices({ 35,36,37,35,37,38,35,38,39 });
		indices.AddIndices({ 40,41,42,40,42,43,40,43,44 });
		indices.AddIndices({ 45,46,47,45,47,48,45,48,49 });
		indices.AddIndices({ 50,51,52,50,52,53,50,53,54 });
		indices.AddIndices({ 55,56,57,55,57,58,55,58,59 });
	}

	icosohedron::icosohedron()
	{
		float phi = (1.0f + sqrt(5.0f)) / 2.0f;
		float W = 1.0f / (3.0f * sqrt(3.0f));

		QM::vector<3>point00(0.0f, 1.0f, phi);
		QM::vector<3>point01(0.0f, 1.0f, -phi);
		QM::vector<3>point02(0.0f, -1.0f, phi);
		QM::vector<3>point03(0.0f, -1.0f, -phi);
		QM::vector<3>point04(phi, 0.0f, 1.0f);
		QM::vector<3>point05(phi, 0.0f, -1.0f);
		QM::vector<3>point06(-phi, 0.0f, 1.0f);
		QM::vector<3>point07(-phi, 0.0f, -1.0f);
		QM::vector<3>point08(1.0f, phi, 0.0f);
		QM::vector<3>point09(1.0f, -phi, 0.0f);
		QM::vector<3>point10(-1.0f, phi, 0.0f);
		QM::vector<3>point11(-1.0f, -phi, 0.0f);

		norms.push_back(point00 + point02 + point04);
		vertices.push_back(QG::Vertex(point00, QM::vector<2>(2.0f * W, 1.0f), norms[0]));
		vertices.push_back(QG::Vertex(point02, QM::vector<2>(1.5f * W, 5.0f/6.0f), norms[0]));
		vertices.push_back(QG::Vertex(point04, QM::vector<2>(W, 1.0f), norms[0]));

		norms.push_back(point00 + point02 + point06);
		vertices.push_back(QG::Vertex(point00, QM::vector<2>(2.5f * W, 5.0f/6.0f), norms[1]));
		vertices.push_back(QG::Vertex(point02, QM::vector<2>(1.5f * W, 5.0f / 6.0f), norms[1]));
		vertices.push_back(QG::Vertex(point06, QM::vector<2>(2.0f * W, 2.0f / 3.0f), norms[1]));

		norms.push_back(point02 + point06 + point11);
		vertices.push_back(QG::Vertex(point02, QM::vector<2>(1.5f * W, 5.0f / 6.0f), norms[2]));
		vertices.push_back(QG::Vertex(point06, QM::vector<2>(2.0f * W, 2.0f / 3.0f), norms[2]));
		vertices.push_back(QG::Vertex(point11, QM::vector<2>(W,2.0f / 3.0f), norms[2]));
		
		norms.push_back(point02 + point09 + point11);
		vertices.push_back(QG::Vertex(point02, QM::vector<2>(1.5f * W, 5.0f / 6.0f), norms[3]));
		vertices.push_back(QG::Vertex(point09, QM::vector<2>(0.5f * W, 5.0f/6.0f), norms[3]));
		vertices.push_back(QG::Vertex(point11, QM::vector<2>(W, 2.0f / 3.0f), norms[3]));
		
		norms.push_back(point00 + point06 + point10);
		vertices.push_back(QG::Vertex(point00, QM::vector<2>(3.0f * W, 2.0f/3.0f), norms[4]));
		vertices.push_back(QG::Vertex(point06, QM::vector<2>(2.0f * W, 2.0f / 3.0f), norms[4]));
		vertices.push_back(QG::Vertex(point10, QM::vector<2>(2.5f * W, 0.5f), norms[4]));
			
		norms.push_back(point00 + point08 + point10);
		vertices.push_back(QG::Vertex(point00, QM::vector<2>(3.5f * W, 0.5f), norms[5]));
		vertices.push_back(QG::Vertex(point08, QM::vector<2>(3.0f * W, 1.0f / 3.0f), norms[5]));
		vertices.push_back(QG::Vertex(point10, QM::vector<2>(2.5f * W, 0.5f), norms[5]));

		norms.push_back(point00 + point04 + point08);
		vertices.push_back(QG::Vertex(point00, QM::vector<2>(4.0f * W, 1.0f/3.0f), norms[6]));
		vertices.push_back(QG::Vertex(point04, QM::vector<2>(3.5f * W, 1.0f/6.0f), norms[6]));
		vertices.push_back(QG::Vertex(point08, QM::vector<2>(3.0f * W, 1.0f / 3.0f), norms[6]));

		norms.push_back(point01 + point03 + point05);
		vertices.push_back(QG::Vertex(point01, QM::vector<2>(2.0f * W, 1.0f / 3.0f), norms[7]));
		vertices.push_back(QG::Vertex(point03, QM::vector<2>(1.5f * W, 1.0f / 6.0f), norms[7]));
		vertices.push_back(QG::Vertex(point05, QM::vector<2>(2.5f * W, 1.0f/6.0f), norms[7]));

		norms.push_back(point01 + point03 + point07);
		vertices.push_back(QG::Vertex(point01, QM::vector<2>(2.0f * W, 1.0f / 3.0f), norms[8]));
		vertices.push_back(QG::Vertex(point03, QM::vector<2>(W, 1.0f/3.0f), norms[8]));
		vertices.push_back(QG::Vertex(point07, QM::vector<2>(1.5f * W, 0.5f), norms[8]));

		norms.push_back(point01 + point05 + point08);
		vertices.push_back(QG::Vertex(point01, QM::vector<2>(2.0f * W, 1.0f / 3.0f), norms[9]));
		vertices.push_back(QG::Vertex(point05, QM::vector<2>(2.5f * W, 1.0f / 6.0f), norms[9]));
		vertices.push_back(QG::Vertex(point08, QM::vector<2>(3.0f * W, 1.0f / 3.0f), norms[9]));

		norms.push_back(point01 + point07 + point10);
		vertices.push_back(QG::Vertex(point01, QM::vector<2>(2.0f * W, 1.0f / 3.0f), norms[10]));
		vertices.push_back(QG::Vertex(point07, QM::vector<2>(1.5f * W, 0.5f), norms[10]));
		vertices.push_back(QG::Vertex(point10, QM::vector<2>(2.5f * W, 0.5f), norms[10]));

		norms.push_back(point01 + point08 + point10);
		vertices.push_back(QG::Vertex(point01, QM::vector<2>(2.0f * W, 1.0f / 3.0f), norms[11]));
		vertices.push_back(QG::Vertex(point08, QM::vector<2>(3.0f * W, 1.0f / 3.0f), norms[11]));
		vertices.push_back(QG::Vertex(point10, QM::vector<2>(2.5f * W, 0.5f), norms[11]));

		norms.push_back(point02 + point04 + point09);
		vertices.push_back(QG::Vertex(point02, QM::vector<2>(1.5f * W, 5.0f / 6.0f), norms[12]));
		vertices.push_back(QG::Vertex(point04, QM::vector<2>(W, 1.0f), norms[12]));
		vertices.push_back(QG::Vertex(point09, QM::vector<2>(0.5f * W, 5.0f / 6.0f), norms[12]));

		norms.push_back(point03 + point05 + point09);
		vertices.push_back(QG::Vertex(point03, QM::vector<2>(2.0f * W,0.0f), norms[13]));
		vertices.push_back(QG::Vertex(point05, QM::vector<2>(2.5f * W, 1.0f / 6.0f), norms[13]));
		vertices.push_back(QG::Vertex(point09, QM::vector<2>(3.0f * W, 0.0f), norms[13]));

		norms.push_back(point03 + point07 + point11);
		vertices.push_back(QG::Vertex(point03, QM::vector<2>(0.5f * W, 0.5f), norms[14]));
		vertices.push_back(QG::Vertex(point07, QM::vector<2>(1.5f * W, 0.5f), norms[14]));
		vertices.push_back(QG::Vertex(point11, QM::vector<2>(W, 2.0f / 3.0f), norms[14]));

		norms.push_back(point03 + point09 + point11);
		vertices.push_back(QG::Vertex(point03, QM::vector<2>(0.0f, 2.0f / 3.0f), norms[15]));
		vertices.push_back(QG::Vertex(point09, QM::vector<2>(0.5f * W, 5.0f / 6.0f), norms[15]));
		vertices.push_back(QG::Vertex(point11, QM::vector<2>(W, 2.0f / 3.0f), norms[15]));

		norms.push_back(point04 + point05 + point08);
		vertices.push_back(QG::Vertex(point04, QM::vector<2>(3.5f * W, 1.0f / 6.0f), norms[16]));
		vertices.push_back(QG::Vertex(point05, QM::vector<2>(2.5f * W, 1.0f / 6.0f), norms[16]));
		vertices.push_back(QG::Vertex(point08, QM::vector<2>(3.0f * W, 1.0f / 3.0f), norms[16]));

		norms.push_back(point04 + point05 + point09);
		vertices.push_back(QG::Vertex(point04, QM::vector<2>(3.5f * W, 1.0f / 6.0f), norms[17]));
		vertices.push_back(QG::Vertex(point05, QM::vector<2>(2.5f * W, 1.0f / 6.0f), norms[17]));
		vertices.push_back(QG::Vertex(point09, QM::vector<2>(3.0f * W, 0.0f), norms[17]));

		norms.push_back(point06 + point07 + point10);
		vertices.push_back(QG::Vertex(point06, QM::vector<2>(2.0f * W, 2.0f / 3.0f), norms[18]));
		vertices.push_back(QG::Vertex(point07, QM::vector<2>(1.5f * W, 0.5f), norms[18]));
		vertices.push_back(QG::Vertex(point10, QM::vector<2>(2.5f * W, 0.5f), norms[18]));

		norms.push_back(point06 + point07 + point11);
		vertices.push_back(QG::Vertex(point06, QM::vector<2>(2.0f * W, 2.0f / 3.0f), norms[19]));
		vertices.push_back(QG::Vertex(point07, QM::vector<2>(1.5f * W, 0.5f), norms[19]));
		vertices.push_back(QG::Vertex(point11, QM::vector<2>(W, 2.0f / 3.0f), norms[19]));

		for (int i = 0; i < 60; i++)
			indices.AddIndices({i});

	}

	sphere::sphere()
	{
		for (float theta = 0.0f; theta < 181.0f; theta += 5.625f)
			for (float phi = 0.0f; phi < 361.0f; phi += 5.625f)
			{
				float xValue = (float)(sin(QM::rad(theta)) * cos(QM::rad(phi)));
				float yValue = (float)(sin(QM::rad(theta)) * sin(QM::rad(phi)));
				float zValue = (float)(cos(QM::rad(theta)));

				QM::vector<3>P(xValue, yValue, zValue);
				assert(abs(P.magnitude() - 1) < 0.000001);

				QM::vector<2>Tcoord;
				float xIncrement = 0.015625f;
				float yIncrement = 0.03125f;
				float phiCheck = (phi / 5.625f) * xIncrement;
				phiCheck = phiCheck > 1.0f ? (phiCheck - 1.0f) : phiCheck;
				Tcoord.set(1, phiCheck);
				Tcoord.set(2, (theta / 5.625f) * yIncrement);
				if (theta == 0.0f || theta == 180.0f)
					Tcoord += QM::vector<2>(0.0078125f, 0.0f);

				if (Tcoord.get(1) <= 1.0f && Tcoord.get(2) <= 1.0f)
					vertices.push_back(Vertex(P, Tcoord, P));
			}
	
		for (int i = 0; i < 64; i++)
			indices.AddIndices({ i, i + 64, i + 65 });

		for (int i = 2079; i < 2143; i++)
			indices.AddIndices({i, i - 64, i - 65});

		for (int i = 64; i < 2015; i++)
			if (i % 65 != 63)
				indices.AddIndices({ i, i + 1, i + 65,i + 1,i + 65,i + 66 });


		/*
		for (int i = 1; i < 64; i++)
			indices.AddIndices({ 0,i,i+1 });
		indices.AddIndices({ 0,64,1 });

		for (int i = 1921; i < 1984; i++)
			indices.AddIndices({ 1985,i,i+1 });
		indices.AddIndices({ 1985,1984,1921 });

		for (int i = 1; i < 1921; i++)
		{
			if (i % 64 == 0)
				indices.AddIndices({ i,i - 63,i + 1,i,i + 1,i + 64 });
			else			
				indices.AddIndices({ i,i + 1,i + 64,i + 1,i + 64,i + 65 });
		}
		*/

	}

	torus::torus(float ratio): m_ratio(ratio)
	{
		float increment = 1.0f / 64.0f;
		bool secondPass = false;
		for (float phi = 0.0f; phi < 360.0f; phi += 5.625f)
		{
			for (float theta = 0.0f; theta < 360.0f; theta += 5.625f)
			{
				float xValue = (float)((1 + cos(QM::rad(theta)) / ratio) * cos(QM::rad(phi)));
				float yValue = (float)((1 + cos(QM::rad(theta)) / ratio) * sin(QM::rad(phi)));
				float zValue = (float)(sin(QM::rad(theta)) / ratio);

				QM::vector<3>P(xValue, yValue, zValue);

				float normX = (float)(cos(QM::rad(theta)) * cos(QM::rad(phi)) / ratio);
				float normY = (float)(cos(QM::rad(theta)) * sin(QM::rad(phi)) / ratio);

				QM::vector<3>norm(normX, normY, zValue);

				QM::vector<2> TCoord;
				float xCoord = (phi * increment) / 5.625f + 0.5f;
				xCoord = xCoord > 1.0f ? xCoord - 1.0f : xCoord;
				if (secondPass)
					xCoord = 0.0f;
				TCoord.set(1, xCoord);

				float yCoord = 0.5f - ((theta * increment) / 5.625f);
				yCoord = yCoord < 0.0f ? yCoord + 1.0f : yCoord;
				TCoord.set(2, yCoord);
				vertices.push_back(Vertex(P, TCoord, norm));

				if (theta == 180.0f)
				{
					TCoord.set(2, 1.0f);
					vertices.push_back(Vertex(P, TCoord, norm));
				}
			}
			if (phi == 180.0f)			
				secondPass = !secondPass;			
			if (secondPass)
				phi -= 5.625f;
		}

		for (int i = 0; i < 4225; i++)
		{
			if (i % 65 != 32 && (i <= 2080 || i >= 2144))
			{
				int a = (i + 1) % 4225;
				int b = (i + 65) % 4225;
				int c = (i + 66) % 4225;
				indices.AddIndices({ i,a,b,a,b,c });
			}
		}
	}
	
}