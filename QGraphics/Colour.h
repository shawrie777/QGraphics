#pragma once

#include "Core.h"

namespace QG
{
	class Colour : public QM::vector<4, float>
	{
	public:
		//creates a colour, black by default
		Colour();
		//create a colour using values between 0 and 1
		Colour(float r, float g, float b, float alpha = 1.0f);
		//create a colour using a hex code
		Colour(int hex);
		~Colour() {};

		//get red component
		float red();
		//get green component
		float green();
		//get blue component
		float blue();
		//get alpha component
		float alpha();

		//increase the red component
		void addRed(float x);
		//increase the blue component
		void addBlue(float x);
		//increase the green component
		void addGreen(float x);
		//increase the alpha component
		void addAlpha(float x);

		//decrease the red component
		void subtractRed(float x);
		//decrease the blue component
		void subtractBlue(float x);
		//decrease the green component
		void subtractGreen(float x);
		//decrease the alpha component
		void subtractAlpha(float x);
	};

	//mixes the two colours by taking an average
	Colour mix(Colour first, Colour second);
}