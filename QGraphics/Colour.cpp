#include "Colour.h"

namespace QG
{
	Colour::Colour() : QM::vector<4, float>(0.0f, 0.0f, 0.0f, 1.0f)
	{
	}

	Colour::Colour(float r, float g, float b, float alpha) : QM::vector<4, float>(r, g, b, alpha)
	{
	}
	Colour::Colour(int hex)
	{
		int temp = hex / 256;
		float blue = (float)hex - 256.0f * temp;
		int temp2 = temp / 256;
		float green = (float)temp - (float)temp2 * 256.0f;
		float red = (float)temp2;

		//blue -= 1;
		//green -= 1;
		//red -= 1;
		blue /= 255;
		green /= 255;
		red /= 255;

		set(1, red);
		set(2, green);
		set(3, blue);
		set(4, 1.0f);
	}
	
	float Colour::red()
	{
		return get(1);
	}

	float Colour::green()
	{
		return get(2);
	}

	float Colour::blue()
	{
		return get(3);
	}

	float Colour::alpha()
	{
		return get(4);
	}

	void Colour::addRed(float x)
	{
		set(1, fmin(red() + x, 1.0f));
	}

	void Colour::addBlue(float x)
	{
		set(2, fmin(blue() + x, 1.0f));
	}

	void Colour::addGreen(float x)
	{
		set(3, fmin(green() + x, 1.0f));
	}

	void Colour::addAlpha(float x)
	{
		set(4, fmin(alpha() + x, 1.0f));
	}

	void Colour::subtractRed(float x)
	{
		set(1, fmax(red() - x, 0.0f));
	}

	void Colour::subtractBlue(float x)
	{
		set(2, fmax(blue() - x, 0.0f));
	}

	void Colour::subtractGreen(float x)
	{
		set(3, fmax(green() - x, 0.0f));
	}

	void Colour::subtractAlpha(float x)
	{
		set(4, fmax(alpha() - x, 0.0f));
	}

	Colour mix(Colour first, Colour second)
	{
		return Colour((first.red() + second.red()) / 2, (first.green() + second.green()) / 2, (first.blue() + second.blue()) / 2, (first.alpha() + second.alpha()) / 2);
	}
}