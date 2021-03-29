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
		frustum(float ratio);
	};

	template<int baseSides>
	//ratio should be between 0 and 1
	inline frustum<baseSides>::frustum(float ratio): m_ratio(ratio)
	{
		shape2D<baseSides> base;
		
		QM::vector<3> shift(0.0f, 0.0f, 1.0f);
		QM::vector<2> zero(0.0f, 0.0f);

		norms.push_back(QM::vector<3>(0.0f, 0.0f, 1.0f));
		norms.push_back(QM::vector<3>(0.0f, 0.0f, -1.0f));
				
		//the ends
		for (auto i = base.vertices.begin(); i != base.vertices.end(); i++)
		{
			vertices.push_back(QG::Vertex(ratio*(i->getPosition()) + shift,GRAY,zero,norms[0]));//z=1
			vertices.push_back(QG::Vertex(i->getPosition() - shift, GRAY, zero, norms[1]));//z=-1
		}

		norms.push_back(base.vertices.begin()->getPosition() + (base.vertices.end() - 1)->getPosition());
		vertices.push_back(QG::Vertex(ratio*(base.vertices.begin()->getPosition()) + shift, GRAY, zero, norms[2]));
		vertices.push_back(QG::Vertex(base.vertices.begin()->getPosition() - shift, GRAY, zero, norms[2]));
		vertices.push_back(QG::Vertex(ratio*((base.vertices.end()-1)->getPosition()) + shift, GRAY, zero, norms[2]));
		vertices.push_back(QG::Vertex((base.vertices.end()-1)->getPosition() - shift, GRAY, zero, norms[2]));

		for (auto i = base.vertices.begin(); i + 1 != base.vertices.end(); i++)
		{
			auto norm = i->getPosition() + (i + 1)->getPosition();
			norms.push_back(norm);
			
			vertices.push_back(QG::Vertex(ratio*(i->getPosition()) + shift, GRAY, zero, norm));
			vertices.push_back(QG::Vertex(i->getPosition() - shift, GRAY, zero, norm));
			vertices.push_back(QG::Vertex(ratio*((i + 1)->getPosition()) + shift, GRAY, zero, norm));
			vertices.push_back(QG::Vertex((i + 1)->getPosition() - shift, GRAY, zero, norm));
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
			while(index+2<currentSet.size())
			{
				int bestIndex = index + 1;
				float bestDist = dist(vertices[currentSet[index + 1]], vertices[currentSet[index]]);
				for (int i = index + 2; i < currentSet.size(); i++)
				{
					float D = dist(vertices[currentSet[i]], vertices[currentSet[index]]);
					if (D < bestDist)
					{
						bestIndex = i;
						bestDist = D;
					}
				}
				std::swap(currentSet[index + 1], currentSet[bestIndex]);
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