#pragma once
#include "2Dshape.h"

namespace QG
{
	template<int baseSides>
	class frustum : public Asset
	{
	protected:
		std::vector<QM::vector<3>> norms;
		float m_ratio = 1.0f;
	public:
		//create frustrum with given number of base sides
		//the ratio is between the size of one end to the other
		//setting this to 0 will give a pyramid, 1 will give a prism
		frustum(float ratio);
	};

	template<int baseSides>
	//ratio should be between 0 and 1
	inline frustum<baseSides>::frustum(float ratio): m_ratio(ratio)
	{
		shape2D<baseSides> base;
		
		QM::vector<3> shift(0.0f, 0.0f, 1.0f);
		//QM::vector<2> zero(0.0f, 0.0f);

		//texture coordinates
		bool TWidthLarger = (cos(QM::pi / (double)baseSides) + 2.0) / ((double)baseSides * sin(QM::pi / (double)baseSides)) <= 1.0;

		QM::vector<2>TexBaseCentre;
		float TexSideLength = 0.0f;
		float TexRadius = 0.0f;
		float TexSideHeight = 0.0f;
		float TexAngle = 2.0f * (float)QM::pi / (float)baseSides;
		float TexAngleOffset = 0.0f;
		float alpha;

		if (baseSides % 4 == 3)
			alpha = (baseSides - 3) / 4;
		else
			alpha = (baseSides - baseSides % 4) / 4 - 1;
		TexAngleOffset = (alpha + 1.5f) * (2.0f * (float)QM::pi / (float)baseSides) - (float)QM::pi / 2.0f;

		norms.push_back(QM::vector<3>(0.0f, 0.0f, 1.0f));
		norms.push_back(QM::vector<3>(0.0f, 0.0f, -1.0f));


		if (TWidthLarger)
		{
			TexSideLength = 1.0f / baseSides;
			TexRadius = 1.0f / (2.0f * (float)baseSides * sin((float)QM::pi / (float)baseSides));
			TexSideHeight = 2.0f * TexRadius;
			TexBaseCentre.set(1, 1.5f * TexSideLength);
			TexBaseCentre.set(2, 1.0f / (2.0f * (float)baseSides * tan((float)QM::pi / (float)baseSides)) + TexRadius + 0.5f);
		}
		else
		{
			TexSideLength = sin((float)QM::pi / (float)baseSides) / (cos((float)QM::pi / (float)baseSides) + 2.0f);
			TexRadius = TexSideLength / (2.0f * sin((float)QM::pi / (float)baseSides));
			TexSideHeight = 2.0f * TexRadius;
			TexBaseCentre.set(1, TexRadius);
			TexBaseCentre.set(2, 1.0f - TexRadius);
		}

		float TContacts = (1.5f * ((float)QM::pi - TexAngleOffset)) / TexAngle;
		int TContact1 = (int)floor(TContacts);
		QM::vector<2> TContact1Coords;
		int TContact2 = (int)ceil(TContacts);
				
		//the ends
		for (auto i = base.vertices.begin(); i != base.vertices.end(); i++)
		{
			QM::vector<2> TCoord(TexRadius * cos((i-base.vertices.begin()) * TexAngle + TexAngleOffset) + TexBaseCentre.get(1), TexRadius * sin((i - base.vertices.begin()) * TexAngle + TexAngleOffset) + TexBaseCentre.get(2));
			if (i - base.vertices.begin() == TContact1) TContact1Coords = TCoord;
			vertices.push_back(QG::Vertex(ratio*(i->getPosition()) + shift,TCoord,norms[0]));//z=1
			TCoord.set(2, 1.0f - TCoord.get(2));
			vertices.push_back(QG::Vertex(i->getPosition() - shift, TCoord, norms[1]));//z=-1
		}

		QM::vector<2> TCoordTop(0.0f, TexSideHeight / 2.0f + 0.5f);
		QM::vector<2> TCoordBottom(0.0f, 1.0f - TCoordTop.get(2));

		int dist2 = baseSides - TContact1;
		TCoordTop.set(1, TContact1Coords.get(1) + (float)dist2 * TexSideLength);
		TCoordBottom.set(1, TContact1Coords.get(1) + (float)dist2 * TexSideLength);

		norms.push_back(base.vertices.begin()->getPosition() + (base.vertices.end() - 1)->getPosition());
		vertices.push_back(QG::Vertex(ratio*(base.vertices.begin()->getPosition()) + shift, TCoordTop, norms[2]));
		vertices.push_back(QG::Vertex(base.vertices.begin()->getPosition() - shift, TCoordBottom, norms[2]));

		dist2 -= 1;
		TCoordTop.set(1, TContact1Coords.get(1) + (float)dist2 * TexSideLength);
		TCoordBottom.set(1, TContact1Coords.get(1) + (float)dist2 * TexSideLength);

		vertices.push_back(QG::Vertex(ratio*((base.vertices.end()-1)->getPosition()) + shift, TCoordTop, norms[2]));
		vertices.push_back(QG::Vertex((base.vertices.end()-1)->getPosition() - shift, TCoordBottom, norms[2]));

		int k = 3;
		for (auto i = base.vertices.begin(); i + 1 != base.vertices.end(); i++)
		{
			dist2 = k < TContact1 + 2 ? baseSides - TContact1 + k - 3 : k - TContact1 - 3;

			TCoordTop.set(1, TContact1Coords.get(1) + (float)dist2 * TexSideLength);
			TCoordBottom.set(1, TContact1Coords.get(1) + (float)dist2 * TexSideLength);

			auto norm = i->getPosition() + (i + 1)->getPosition();
			norms.push_back(norm);
			
			vertices.push_back(QG::Vertex(ratio*(i->getPosition()) + shift, TCoordTop, norm));
			vertices.push_back(QG::Vertex(i->getPosition() - shift, TCoordBottom, norm));

			dist2++;
			TCoordTop.set(1, TContact1Coords.get(1) + (float)dist2 * TexSideLength);
			TCoordBottom.set(1, TContact1Coords.get(1) + (float)dist2 * TexSideLength);

			vertices.push_back(QG::Vertex(ratio*((i + 1)->getPosition()) + shift, TCoordTop, norm));
			vertices.push_back(QG::Vertex((i + 1)->getPosition() - shift, TCoordBottom, norm));

			k++;
		}

		for (auto& x : norms)
		{
			//find all points with given norm
			std::vector<int> currentSet;
			for (int y = 0; y < vertices.vertexCount(); y++)
			{
				if (vertices[y].getNormal() == x)
					currentSet.push_back(y);
			}

			int index = 0;
			while (index + 2 < (int)currentSet.size())
			{
				int bestIndex = index + 1;
				float bestDist = dist(vertices[currentSet[static_cast<std::vector<int, std::allocator<int>>::size_type>(index) + 1]], vertices[currentSet[index]]);
				for (int i = index + 2; i < currentSet.size(); i++)
				{
					float D = dist(vertices[currentSet[i]], vertices[currentSet[index]]);
					if (D < bestDist)
					{
						bestIndex = i;
						bestDist = D;
					}
				}
				std::swap(currentSet[static_cast<std::vector<int, std::allocator<int>>::size_type>(index) + 1], currentSet[bestIndex]);
				index++;
			}
			//arrange triangle fan around one point, add to indices
			auto first = currentSet.begin();
			for (auto y = first + 1; y + 1 != currentSet.end(); y++)
			{
				indices.AddIndices({*first, *y, *(y+1)});
			}
		}
	}
}