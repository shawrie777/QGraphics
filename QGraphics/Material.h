#pragma once
#include "Core.h"
#include "Colour.h"
#include "Texture.h"
#include <variant>

namespace QG
{
	class Material
	{
	private:
		std::variant<Colour,Texture> Diffuse;
		std::variant<Colour,Texture> Specular;
		float shininess;
	public:
		//create a material by specifying colours
		Material(Colour diff, Colour spec, float shine);
		//create a material by specifying texture paths
		Material(const char* diff, const char* spec, float shine);
		//create a default material, a shiny grey
		Material();

		//check if the diffuse component uses a texture or a colour
		bool usingDifTex();
		//check if the specular component uses a texture or a colour
		bool usingSpecTex();
		//gets the diffuse component, as a variant
		std::variant<Colour, Texture> getDiff();
		//gets the specular component, as a variant
		std::variant<Colour, Texture> getSpec();
		//get the shininess
		float getShininess();
		//bind the texture components for openGL
		void Bind();
		//unbind the texture components for openGL
		void Unbind();
	};
}