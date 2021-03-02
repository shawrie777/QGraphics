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
}