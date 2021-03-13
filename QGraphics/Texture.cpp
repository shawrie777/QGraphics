#include "Texture.h"

namespace QG
{
	void Texture::initTexSlots()
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

			//glBindTexture(GL_TEXTURE_2D, ID);
			//glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
			//glGenerateMipmap(GL_TEXTURE_2D);

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
	}

	void Texture::Bind()
	{
		auto empty = std::find(texSlots.begin(), texSlots.end(), false);
		if (empty == texSlots.end())
			throw("No available texture slots.");

		int pos = (int)(empty - texSlots.begin());
		slot = GL_TEXTURE0 + pos;
		*empty = true;

		glActiveTexture(slot);
		glBindTexture(GL_TEXTURE_2D, ID);
	}

	void Texture::Unbind()
	{
		int pos = slot - GL_TEXTURE0;
		texSlots[pos] = false;
	}
}