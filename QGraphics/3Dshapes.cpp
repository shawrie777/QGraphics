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

		vertices.push_back(QG::Vertex(TFR, zero, topNorm));
		vertices.push_back(QG::Vertex(TFR, zero, frontNorm));
		vertices.push_back(QG::Vertex(TFR, zero, rightNorm)); //2

		vertices.push_back(QG::Vertex(TFL, zero, topNorm));
		vertices.push_back(QG::Vertex(TFL, zero, frontNorm));
		vertices.push_back(QG::Vertex(TFL, zero, leftNorm)); //5

		vertices.push_back(QG::Vertex(TBR, zero, topNorm));
		vertices.push_back(QG::Vertex(TBR, zero, backNorm));
		vertices.push_back(QG::Vertex(TBR, zero, rightNorm)); //8

		vertices.push_back(QG::Vertex(TBL, zero, topNorm));
		vertices.push_back(QG::Vertex(TBL, zero, backNorm));
		vertices.push_back(QG::Vertex(TBL, zero, leftNorm)); //11
		
		vertices.push_back(QG::Vertex(BFR, zero, bottomNorm));
		vertices.push_back(QG::Vertex(BFR, zero, frontNorm));
		vertices.push_back(QG::Vertex(BFR, zero, rightNorm)); //14

		vertices.push_back(QG::Vertex(BFL, zero, bottomNorm));
		vertices.push_back(QG::Vertex(BFL, zero, frontNorm));
		vertices.push_back(QG::Vertex(BFL, zero, leftNorm)); //17

		vertices.push_back(QG::Vertex(BBR, zero, bottomNorm));
		vertices.push_back(QG::Vertex(BBR, zero, backNorm));
		vertices.push_back(QG::Vertex(BBR, zero, rightNorm)); //20

		vertices.push_back(QG::Vertex(BBL, zero, bottomNorm));
		vertices.push_back(QG::Vertex(BBL, zero, backNorm));
		vertices.push_back(QG::Vertex(BBL, zero, leftNorm)); //23
		
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
		if (norm0.get(2) < 0)
			norm2 = -1 * norm2;
		norms.push_back(norm2);
		QM::vector<3>norm3 = side3.cross(side4);
		if (norm3.get(2) > 0)
			norm3 = -1 * norm3;
		norms.push_back(norm3);

		QM::vector<2> zero(0.0f, 0.0f);

		vertices.push_back(QG::Vertex(point0, zero, norm0));
		vertices.push_back(QG::Vertex(point1, zero, norm0));
		vertices.push_back(QG::Vertex(point2, zero, norm0));//2

		vertices.push_back(QG::Vertex(point0, zero, norm1));
		vertices.push_back(QG::Vertex(point1, zero, norm1));
		vertices.push_back(QG::Vertex(point3, zero, norm1));//5

		vertices.push_back(QG::Vertex(point0, zero, norm2));
		vertices.push_back(QG::Vertex(point2, zero, norm2));
		vertices.push_back(QG::Vertex(point3, zero, norm2));//8

		vertices.push_back(QG::Vertex(point1, zero, norm3));
		vertices.push_back(QG::Vertex(point2, zero, norm3));
		vertices.push_back(QG::Vertex(point3, zero, norm3));//11

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

		norms.push_back(QM::vector<3>(1.0f, 1.0f, 1.0f));
		norms.push_back(QM::vector<3>(-1.0f, 1.0f, 1.0f));
		norms.push_back(QM::vector<3>(-1.0f, 1.0f, -1.0f));
		norms.push_back(QM::vector<3>(1.0f, 1.0f, -1.0f));
		norms.push_back(QM::vector<3>(1.0f, -1.0f, 1.0f));
		norms.push_back(QM::vector<3>(-1.0f, -1.0f, 1.0f));
		norms.push_back(QM::vector<3>(-1.0f, -1.0f, -1.0f));
		norms.push_back(QM::vector<3>(1.0f, -1.0f, -1.0f));

		vertices.push_back(QG::Vertex(point0, zero, norms[0]));
		vertices.push_back(QG::Vertex(point1, zero, norms[0]));
		vertices.push_back(QG::Vertex(point2, zero, norms[0])); //2

		vertices.push_back(QG::Vertex(point3, zero, norms[1]));
		vertices.push_back(QG::Vertex(point0, zero, norms[1]));
		vertices.push_back(QG::Vertex(point2, zero, norms[1])); //5

		vertices.push_back(QG::Vertex(point3, zero, norms[2]));
		vertices.push_back(QG::Vertex(point0, zero, norms[2]));
		vertices.push_back(QG::Vertex(point4, zero, norms[2])); //8

		vertices.push_back(QG::Vertex(point1, zero, norms[3]));
		vertices.push_back(QG::Vertex(point0, zero, norms[3]));
		vertices.push_back(QG::Vertex(point4, zero, norms[3])); //11

		vertices.push_back(QG::Vertex(point5, zero, norms[4]));
		vertices.push_back(QG::Vertex(point1, zero, norms[4]));
		vertices.push_back(QG::Vertex(point2, zero, norms[4])); //14

		vertices.push_back(QG::Vertex(point3, zero, norms[5]));
		vertices.push_back(QG::Vertex(point5, zero, norms[5]));
		vertices.push_back(QG::Vertex(point2, zero, norms[5])); //17

		vertices.push_back(QG::Vertex(point3, zero, norms[6]));
		vertices.push_back(QG::Vertex(point5, zero, norms[6]));
		vertices.push_back(QG::Vertex(point4, zero, norms[6])); //20

		vertices.push_back(QG::Vertex(point1, zero, norms[7]));
		vertices.push_back(QG::Vertex(point5, zero, norms[7]));
		vertices.push_back(QG::Vertex(point4, zero, norms[7])); //23

		indices.AddIndices({ 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23 });
	}

	dodecahedron::dodecahedron()
	{
		float phi = (1.0f + sqrt(5.0f)) / 2.0f;
		QM::vector<2> zero(0.0f, 0.0f);

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
		
		vertices.push_back(QG::Vertex(point00, zero, norms[0]));
		vertices.push_back(QG::Vertex(point17, zero, norms[0]));
		vertices.push_back(QG::Vertex(point03, zero, norms[0]));
		vertices.push_back(QG::Vertex(point13, zero, norms[0]));
		vertices.push_back(QG::Vertex(point12, zero, norms[0]));

		vertices.push_back(QG::Vertex(point02, zero, norms[1]));
		vertices.push_back(QG::Vertex(point16, zero, norms[1]));
		vertices.push_back(QG::Vertex(point04, zero, norms[1]));
		vertices.push_back(QG::Vertex(point15, zero, norms[1]));
		vertices.push_back(QG::Vertex(point14, zero, norms[1]));

		vertices.push_back(QG::Vertex(point01, zero, norms[2]));
		vertices.push_back(QG::Vertex(point12, zero, norms[2]));
		vertices.push_back(QG::Vertex(point13, zero, norms[2]));
		vertices.push_back(QG::Vertex(point05, zero, norms[2]));
		vertices.push_back(QG::Vertex(point18, zero, norms[2]));

		vertices.push_back(QG::Vertex(point14, zero, norms[3]));
		vertices.push_back(QG::Vertex(point15, zero, norms[3]));
		vertices.push_back(QG::Vertex(point06, zero, norms[3]));
		vertices.push_back(QG::Vertex(point19, zero, norms[3]));
		vertices.push_back(QG::Vertex(point07, zero, norms[3]));

		vertices.push_back(QG::Vertex(point00, zero, norms[4]));
		vertices.push_back(QG::Vertex(point12, zero, norms[4]));
		vertices.push_back(QG::Vertex(point01, zero, norms[4]));
		vertices.push_back(QG::Vertex(point09, zero, norms[4]));
		vertices.push_back(QG::Vertex(point08, zero, norms[4]));

		vertices.push_back(QG::Vertex(point13, zero, norms[5]));
		vertices.push_back(QG::Vertex(point03, zero, norms[5]));
		vertices.push_back(QG::Vertex(point10, zero, norms[5]));
		vertices.push_back(QG::Vertex(point11, zero, norms[5]));
		vertices.push_back(QG::Vertex(point05, zero, norms[5]));
		
		vertices.push_back(QG::Vertex(point09, zero, norms[6]));
		vertices.push_back(QG::Vertex(point08, zero, norms[6]));
		vertices.push_back(QG::Vertex(point02, zero, norms[6]));
		vertices.push_back(QG::Vertex(point14, zero, norms[6]));
		vertices.push_back(QG::Vertex(point07, zero, norms[6]));
		
		vertices.push_back(QG::Vertex(point15, zero, norms[7]));
		vertices.push_back(QG::Vertex(point04, zero, norms[7]));
		vertices.push_back(QG::Vertex(point10, zero, norms[7]));
		vertices.push_back(QG::Vertex(point11, zero, norms[7]));
		vertices.push_back(QG::Vertex(point06, zero, norms[7]));

		vertices.push_back(QG::Vertex(point00, zero, norms[8]));
		vertices.push_back(QG::Vertex(point17, zero, norms[8]));
		vertices.push_back(QG::Vertex(point16, zero, norms[8]));
		vertices.push_back(QG::Vertex(point02, zero, norms[8]));
		vertices.push_back(QG::Vertex(point08, zero, norms[8]));
		
		vertices.push_back(QG::Vertex(point03, zero, norms[9]));
		vertices.push_back(QG::Vertex(point17, zero, norms[9]));
		vertices.push_back(QG::Vertex(point16, zero, norms[9]));
		vertices.push_back(QG::Vertex(point04, zero, norms[9]));
		vertices.push_back(QG::Vertex(point10, zero, norms[9]));

		vertices.push_back(QG::Vertex(point01, zero, norms[10]));
		vertices.push_back(QG::Vertex(point18, zero, norms[10]));
		vertices.push_back(QG::Vertex(point19, zero, norms[10]));
		vertices.push_back(QG::Vertex(point07, zero, norms[10]));
		vertices.push_back(QG::Vertex(point09, zero, norms[10]));
		
		vertices.push_back(QG::Vertex(point05, zero, norms[11]));
		vertices.push_back(QG::Vertex(point18, zero, norms[11]));
		vertices.push_back(QG::Vertex(point19, zero, norms[11]));
		vertices.push_back(QG::Vertex(point06, zero, norms[11]));
		vertices.push_back(QG::Vertex(point11, zero, norms[11]));

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
		QM::vector<2>zero(0.0f, 0.0f);

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
		vertices.push_back(QG::Vertex(point00, zero, norms[0]));
		vertices.push_back(QG::Vertex(point02, zero, norms[0]));
		vertices.push_back(QG::Vertex(point04, zero, norms[0]));

		norms.push_back(point00 + point02 + point06);
		vertices.push_back(QG::Vertex(point00, zero, norms[1]));
		vertices.push_back(QG::Vertex(point02, zero, norms[1]));
		vertices.push_back(QG::Vertex(point06, zero, norms[1]));

		norms.push_back(point02 + point06 + point11);
		vertices.push_back(QG::Vertex(point02, zero, norms[2]));
		vertices.push_back(QG::Vertex(point06, zero, norms[2]));
		vertices.push_back(QG::Vertex(point11, zero, norms[2]));
		
		norms.push_back(point02 + point09 + point11);
		vertices.push_back(QG::Vertex(point02, zero, norms[3]));
		vertices.push_back(QG::Vertex(point09, zero, norms[3]));
		vertices.push_back(QG::Vertex(point11, zero, norms[3]));
		
		norms.push_back(point00 + point06 + point10);
		vertices.push_back(QG::Vertex(point00, zero, norms[4]));
		vertices.push_back(QG::Vertex(point06, zero, norms[4]));
		vertices.push_back(QG::Vertex(point10, zero, norms[4]));
			
		norms.push_back(point00 + point08 + point10);
		vertices.push_back(QG::Vertex(point00, zero, norms[5]));
		vertices.push_back(QG::Vertex(point08, zero, norms[5]));
		vertices.push_back(QG::Vertex(point10, zero, norms[5]));

		norms.push_back(point00 + point04 + point08);
		vertices.push_back(QG::Vertex(point00, zero, norms[6]));
		vertices.push_back(QG::Vertex(point04, zero, norms[6]));
		vertices.push_back(QG::Vertex(point08, zero, norms[6]));

		norms.push_back(point01 + point03 + point05);
		vertices.push_back(QG::Vertex(point01, zero, norms[7]));
		vertices.push_back(QG::Vertex(point03, zero, norms[7]));
		vertices.push_back(QG::Vertex(point05, zero, norms[7]));

		norms.push_back(point01 + point03 + point07);
		vertices.push_back(QG::Vertex(point01, zero, norms[8]));
		vertices.push_back(QG::Vertex(point03, zero, norms[8]));
		vertices.push_back(QG::Vertex(point07, zero, norms[8]));

		norms.push_back(point01 + point05 + point08);
		vertices.push_back(QG::Vertex(point01, zero, norms[9]));
		vertices.push_back(QG::Vertex(point05, zero, norms[9]));
		vertices.push_back(QG::Vertex(point08, zero, norms[9]));

		norms.push_back(point01 + point07 + point10);
		vertices.push_back(QG::Vertex(point01, zero, norms[10]));
		vertices.push_back(QG::Vertex(point07, zero, norms[10]));
		vertices.push_back(QG::Vertex(point10, zero, norms[10]));

		norms.push_back(point01 + point08 + point10);
		vertices.push_back(QG::Vertex(point01, zero, norms[11]));
		vertices.push_back(QG::Vertex(point08, zero, norms[11]));
		vertices.push_back(QG::Vertex(point10, zero, norms[11]));

		norms.push_back(point02 + point04 + point09);
		vertices.push_back(QG::Vertex(point02, zero, norms[12]));
		vertices.push_back(QG::Vertex(point04, zero, norms[12]));
		vertices.push_back(QG::Vertex(point09, zero, norms[12]));

		norms.push_back(point03 + point05 + point09);
		vertices.push_back(QG::Vertex(point03, zero, norms[13]));
		vertices.push_back(QG::Vertex(point05, zero, norms[13]));
		vertices.push_back(QG::Vertex(point09, zero, norms[13]));

		norms.push_back(point03 + point07 + point11);
		vertices.push_back(QG::Vertex(point03, zero, norms[14]));
		vertices.push_back(QG::Vertex(point07, zero, norms[14]));
		vertices.push_back(QG::Vertex(point11, zero, norms[14]));

		norms.push_back(point03 + point09 + point11);
		vertices.push_back(QG::Vertex(point03, zero, norms[15]));
		vertices.push_back(QG::Vertex(point09, zero, norms[15]));
		vertices.push_back(QG::Vertex(point11, zero, norms[15]));

		norms.push_back(point04 + point05 + point08);
		vertices.push_back(QG::Vertex(point04, zero, norms[16]));
		vertices.push_back(QG::Vertex(point05, zero, norms[16]));
		vertices.push_back(QG::Vertex(point08, zero, norms[16]));

		norms.push_back(point04 + point05 + point09);
		vertices.push_back(QG::Vertex(point04, zero, norms[17]));
		vertices.push_back(QG::Vertex(point05, zero, norms[17]));
		vertices.push_back(QG::Vertex(point09, zero, norms[17]));

		norms.push_back(point06 + point07 + point10);
		vertices.push_back(QG::Vertex(point06, zero, norms[18]));
		vertices.push_back(QG::Vertex(point07, zero, norms[18]));
		vertices.push_back(QG::Vertex(point10, zero, norms[18]));

		norms.push_back(point06 + point07 + point11);
		vertices.push_back(QG::Vertex(point06, zero, norms[19]));
		vertices.push_back(QG::Vertex(point07, zero, norms[19]));
		vertices.push_back(QG::Vertex(point11, zero, norms[19]));

		for (int i = 0; i < 60; i++)
			indices.AddIndices({i});

	}

	sphere::sphere()
	{
		QM::vector<2>zero(0.0f, 0.0f);

		QM::vector<3>point(0.0f, 0.0f, 1.0f);
		vertices.push_back(Vertex(point, zero, point));


		for (float theta = 5.625f;theta<180.0f;theta+=5.625f)
			for (float phi = 0.0f; phi < 360.0f; phi += 5.625f)
			{
				float xValue = (float)(sin(QM::rad(theta)) * cos(QM::rad(phi)));
				float yValue = (float)(sin(QM::rad(theta)) * sin(QM::rad(phi)));
				float zValue = (float)(cos(QM::rad(theta)));

				QM::vector<3>P(xValue, yValue, zValue);
				assert(abs(P.magnitude() - 1)<0.000001);
				vertices.push_back(Vertex(P, zero, P));
			}

		point.set(3, -1.0f);
		vertices.push_back(Vertex(point, zero, point));

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

	}
	
	float torus::torusDist(QG::Vertex& A, QG::Vertex& B)
	{
		/*double ATheta = asin(m_ratio * A.getPosition().get(3));
		float AMag = A.getPosition().magnitude();
		float checkDist = sqrt(1 + (1 / (m_ratio * m_ratio)));

		QM::rangeCheck(ATheta);

		if(ATheta>QM::pi)

		else if (ATheta<QM::pi)


		QM::rangeCheck(ATheta);

		double APhi = asin(A.getPosition().get(2) / (1.0 + cos(ATheta) / m_ratio));
		QM::rangeCheck(APhi);

		if (A.getPosition().get(1) < 0)
			APhi = QM::pi - APhi;
		QM::rangeCheck(APhi);
		
		double BTheta = asin(m_ratio * B.getPosition().get(3));
		float BMag = B.getPosition().magnitude();

		QM::rangeCheck(BTheta);

		if (BMag > checkDist)
		{
			//theta should be more than 3pi/4 or less than pi/4		
			if (BTheta > QM::pi / 4 && BTheta < 3 * QM::pi / 4)
				BTheta = QM::pi - BTheta;
		}
		else if (BMag < checkDist)
		{
			if (BTheta < QM::pi / 4 || BTheta > 3 * QM::pi / 4)
				BTheta = QM::pi - BTheta;
		}

		QM::rangeCheck(BTheta);

		double BPhi = asin(B.getPosition().get(2) / (1.0 + cos(BTheta) / m_ratio));
		QM::rangeCheck(BPhi);

		if (B.getPosition().get(1) < 0)
			BPhi = QM::pi - BPhi;
		QM::rangeCheck(BPhi);*/

		double APhi = atan2(A.getPosition().get(2), A.getPosition().get(1));
		QM::rangeCheck(APhi);
		double ATheta1 = acos(m_ratio * ((A.getPosition().get(2) / sin(APhi)) - 1));
		double ATheta = asin(m_ratio * A.getPosition().get(3));

		if (isnan(ATheta1))
			ATheta1 = acos(m_ratio * ((A.getPosition().get(1) / cos(APhi)) - 1));

		QM::rangeCheck(ATheta1);
		QM::rangeCheck(ATheta);
		
		if (abs(ATheta1 - ATheta) > 0.01)
			ATheta1 = 2 * QM::pi - ATheta1;
		if (abs(ATheta1 - ATheta) > 0.01)
			ATheta = QM::pi - ATheta;
		
		QM::rangeCheck(ATheta);

		double BPhi = atan2(B.getPosition().get(2), B.getPosition().get(1));
		QM::rangeCheck(BPhi);
		double BTheta1 = acos(m_ratio * ((B.getPosition().get(2) / sin(BPhi)) - 1));
		double BTheta = asin(m_ratio * B.getPosition().get(3));

		if (isnan(BTheta1))
			BTheta1 = acos(m_ratio * ((B.getPosition().get(1) / cos(BPhi)) - 1));

		QM::rangeCheck(BTheta1);
		QM::rangeCheck(BTheta);

		if (abs(BTheta1 - BTheta) > 0.01)
			BTheta1 = 2 * QM::pi - BTheta1;
		if (abs(BTheta1 - BTheta) > 0.01)
			BTheta = QM::pi - BTheta;
		
		QM::rangeCheck(BTheta);

		double dTheta = abs(BTheta - ATheta);
		if (dTheta > QM::pi) dTheta = 2 * QM::pi - dTheta;

		double dPhi = abs(BPhi - APhi);
		if (dPhi > QM::pi) dPhi = 2 * QM::pi - dPhi;

		dTheta /= m_ratio;

		double L = (dTheta * dTheta) + (dPhi * dPhi);

		return (float)sqrt(L);
	}

	torus::torus(float ratio): m_ratio(ratio)
	{
		QM::vector<2> zero(0.0f, 0.0f);

		for (float phi = 0.0f; phi < 360.0f; phi += 5.625)
			for (float theta = 0.0f; theta < 360.0f; theta += 5.625)
			{
				float xValue = (float)((1 + cos(QM::rad(theta)) / ratio) * cos(QM::rad(phi)));
				float yValue = (float)((1 + cos(QM::rad(theta)) / ratio) * sin(QM::rad(phi)));
				float zValue = (float)(sin(QM::rad(theta)) / ratio);

				QM::vector<3>P(xValue, yValue, zValue);				
				vertices.push_back(Vertex(P, zero, P));
			}

		for (int i = 0; i < 4032; i++)
		{
			if (i % 64 == 63)
				indices.AddIndices({ i,i - 63,i + 64,i - 63 ,i + 1,i + 64 });
			else
				indices.AddIndices({ i,i + 1,i + 64,i + 1,i + 65,i + 64 });
		}

		for (int i = 4032; i < 4095; i++)
			indices.AddIndices({ i,i + 1,i - 4032,i + 1,i - 4032,i - 4031 });
		indices.AddIndices({ 4095,4032,63,4032,63,0 });
	}

}