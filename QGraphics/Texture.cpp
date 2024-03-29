#include "Texture.h"

std::vector<bool> texSlots;

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

	Texture::Texture() :
		ID(0),
		width(32),
		height(32),
		components(4),
		data(nullptr),
		format(GL_RGBA),
		slot(0),
		bound(false)
	{
		glGenTextures(1, &ID);

		glBindTexture(GL_TEXTURE_2D, ID);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, 32, 32, 0, GL_RGBA, GL_UNSIGNED_BYTE, NULL);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	}

	void Texture::setActive()
	{
		if (!bound)
			Bind();
		glActiveTexture(slot);
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
		glActiveTexture(slot);
		glBindTexture(GL_TEXTURE_2D, 0);
		bound = false;
	}

	void Texture::doubleSize()
	{
		width *= 2;
		height *= 2;
	}

	CubeMap::CubeMap()
	{
		width = 0;
		height = 0;
		ID = 0;
		components = 0;
		slot = 0;
		format = 0;
		data = NULL;
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

	void CubeMap::setActive()
	{
		if (!bound)
			Bind();
		glActiveTexture(slot);
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
		glActiveTexture(slot);
		if (!bound)
			return;
		int pos = slot - GL_TEXTURE0;
		texSlots[pos] = false;
		glBindTexture(GL_TEXTURE_CUBE_MAP, 0);
		bound = false;
	}


	shadowMap::shadowMap()
	{
		initTexSlots();

		glGenFramebuffers(1, &FBO);
		glGenTextures(1, &ID);
;
		width = 1024;
		height = 1024;

		Bind();
		BindFBO();

		for (unsigned int i = 0; i < 6; ++i)
		{
			glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_DEPTH_COMPONENT, width, height, 0, GL_DEPTH_COMPONENT, GL_FLOAT, NULL);
		}

		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

		glFramebufferTexture(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, ID, 0);
		glDrawBuffer(GL_NONE);
		glReadBuffer(GL_NONE);

		Unbind();
		UnbindFBO();
	}

	void shadowMap::Bind()
	{
		if (bound)
			return;
		CubeMap::Bind();
		
		bound = true;
	}

	void shadowMap::Unbind()
	{
		if (!bound)
			return;
		CubeMap::Unbind();		
		bound = false;
	}

	void shadowMap::BindFBO()
	{
		if (FBObound)
			return;
		glBindFramebuffer(GL_FRAMEBUFFER, FBO);
		FBObound = true;
	}
	void shadowMap::UnbindFBO()
	{
		if (!FBObound)
			return;
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
		FBObound = false;
	}
}