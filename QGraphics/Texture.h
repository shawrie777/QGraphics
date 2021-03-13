#pragma once
#include "Core.h"

static std::vector<bool> texSlots;

namespace QG
{
	class Texture
	{
	private:
		unsigned int ID;
		int width;
		int height;
		int components;
		unsigned char* data;
		GLenum format;
		GLenum slot;
		void initTexSlots();
	public:
		Texture(const char* filepath);
		void Bind();
		void Unbind();

		const unsigned int getID() { return ID; };
		const unsigned int getSlot() { return slot - 0x84C0; };
	};

}