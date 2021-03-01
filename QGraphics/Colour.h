#pragma once

#include "Core.h"

namespace QG
{
	class Colour : public QM::vector<4, float>
	{
	public:
		Colour();
		Colour(float r, float g, float b, float alpha = 1.0f);
		Colour(int hex);

		float red();
		float green();
		float blue();
		float alpha();

		void addRed(float x);
		void addBlue(float x);
		void addGreen(float x);
		void addAlpha(float x);

		void subtractRed(float x);
		void subtractBlue(float x);
		void subtractGreen(float x);
		void subtractAlpha(float x);
	};

	Colour mix(Colour first, Colour second);
}