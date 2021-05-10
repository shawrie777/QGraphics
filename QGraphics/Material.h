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
		Material(Colour diff, Colour spec, float shine);
		Material(const char* diff, const char* spec, float shine);
		Material();

		bool usingDifTex();
		bool usingSpecTex();
		std::variant<Colour, unsigned int> getDiff();
		std::variant<Colour, unsigned int> getSpec();
		float getShininess();

		void Bind();
		void Unbind();
	};
}