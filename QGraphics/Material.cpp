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
	std::variant<Colour, unsigned int> Material::getDiff()
	{
		if (auto value = std::get_if<Texture>(&Diffuse))
			return value->getSlot();
		else if (auto value = std::get_if<Colour>(&Diffuse))
			return *value;
		else
			throw;
	}

	std::variant<Colour, unsigned int> Material::getSpec()
	{
		if (auto value = std::get_if<Texture>(&Specular))
			return value->getSlot();
		else if (auto value = std::get_if<Colour>(&Specular))
			return *value;
		else
			throw;
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