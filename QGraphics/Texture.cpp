#include "Texture.h"

namespace QG
{
	void initTexSlots()
	{
		if (texSlots.size() == 0)
			for (int i = 0; i < 32; i++)
			{
				texSlots.push_back(false);
			}
	}

	Texture::Texture(const char* filepath)
	{
		initTexSlots();

		glGenTextures(1, &ID);
		Bind();
		data = stbi_load(filepath, &width, &height, &components, 0);

		if (data)
		{
			switch (components)
			{
			case 1:
				format = GL_RED;
				break;
			case 3:
				format = GL_RGB;
				break;
			case 4:
				format = GL_RGBA;
				break;
			default:
				format = 1;
				break;
			}

			glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
			glGenerateMipmap(GL_TEXTURE_2D);

			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		}
		else
		{
			std::cout << "Texture failed to load at path: " << filepath << std::endl;
			
		}
		stbi_image_free(data);
		Unbind();
	}

	void Texture::Bind()
	{
		if (bound)
			return;

		auto empty = std::find(texSlots.begin(), texSlots.end(), false);
		if (empty == texSlots.end())
			throw("No available texture slots.");

		int pos = (int)(empty - texSlots.begin());
		slot = GL_TEXTURE0 + pos;
		*empty = true;

		glActiveTexture(slot);
		glBindTexture(GL_TEXTURE_2D, ID);
		bound = true;
	}

	void Texture::Unbind()
	{
		if (!bound)
			return;
		int pos = slot - GL_TEXTURE0;
		texSlots[pos] = false;
		glBindTexture(GL_TEXTURE_2D, 0);
		bound = false;
	}

	CubeMap::CubeMap(std::vector<std::string> faces)
	{
		initTexSlots();

		glGenTextures(1, &ID);
		Bind();

		for (unsigned int i = 0; i < faces.size(); i++)
		{
			data = stbi_load(faces[i].c_str(), &width, &height, &components, 0);
			if (data)
				glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
			else
				std::cout << "Cubemap texture failed to load at path: " << faces[i] << std::endl;
			stbi_image_free(data);
		}

		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

		Unbind();
	}

	CubeMap::CubeMap(std::string right, std::string left, std::string top, std::string bottom, std::string front, std::string back)
	{
		std::vector<std::string> vec;
		vec.push_back(right);
		vec.push_back(left);
		vec.push_back(top);
		vec.push_back(bottom);
		vec.push_back(front);
		vec.push_back(back);
		*this = CubeMap(vec);
	}

	void CubeMap::Bind()
	{
		if (bound)
			return;
		auto empty = std::find(texSlots.begin(), texSlots.end(), false);
		if (empty == texSlots.end())
			throw("No available texture slots.");

		int pos = (int)(empty - texSlots.begin());
		slot = GL_TEXTURE0 + pos;
		*empty = true;

		glActiveTexture(slot);
		glBindTexture(GL_TEXTURE_CUBE_MAP, ID);
		bound = true;
	}

	void CubeMap::Unbind()
	{
		if (!bound)
			return;
		int pos = slot - GL_TEXTURE0;
		texSlots[pos] = false;
		glBindTexture(GL_TEXTURE_CUBE_MAP, 0);
		bound = false;
	}
}