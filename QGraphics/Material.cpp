#include "Material.h"

namespace QG
{
	Material::Material(Colour diff, Colour spec, float shine):Diffuse(diff),Specular(spec),shininess(shine)
	{
	}

	Material::Material(const char* diff, const char* spec, float shine)
	{
		Diffuse = Texture(diff);
		Specular = Texture(spec);
		shininess = shine;
	}
	Material::Material() : Material(GRAY, GRAY, 0.0f)
	{		
	}

	bool Material::usingDifTex()
	{
		return std::holds_alternative<Texture>(Diffuse);
	}

	bool Material::usingSpecTex()
	{
		return std::holds_alternative<Texture>(Specular);
	}
	std::variant<Colour, Texture> Material::getDiff()
	{
		return Diffuse;
	}

	std::variant<Colour, Texture> Material::getSpec()
	{
		return Specular;
	}
	float Material::getShininess()
	{
		return shininess;
	}

	void Material::Bind()
	{
		if (std::holds_alternative<Texture>(Diffuse))
			std::get<Texture>(Diffuse).Bind();
		if (std::holds_alternative<Texture>(Specular))
			std::get<Texture>(Specular).Bind();
	}
	void Material::Unbind()
	{
		if (std::holds_alternative<Texture>(Diffuse))
			std::get<Texture>(Diffuse).Unbind();
		if (std::holds_alternative<Texture>(Specular))
			std::get<Texture>(Specular).Unbind();
	}
}