#pragma once

#include "3Dshapes.h"

namespace QG
{
	class Skybox : public cube
	{
	public:
		CubeMap texture;

		//create a skybox using a vector of image paths
		//must be in order: right, left, top, bottom, front, back
		Skybox(std::vector<std::string> faces);
		//create a skybox from a set of image paths
		Skybox(std::string right, std::string left, std::string top, std::string bottom, std::string front, std::string back);

		void draw();
	};
}