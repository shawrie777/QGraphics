#pragma once

#include "3Dshapes.h"

namespace QG
{

	class Skybox : public cube
	{
	public:
		CubeMap texture;

		//must be in order: right, left, top, bottom, front, back
		Skybox(std::vector<std::string> faces);
		Skybox(std::string right, std::string left, std::string top, std::string bottom, std::string front, std::string back);

		void draw();
	};

}