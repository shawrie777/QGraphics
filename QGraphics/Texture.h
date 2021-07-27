#pragma once
#include "Core.h"

static std::vector<bool> texSlots;

namespace QG
{
	void initTexSlots();

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


		bool bound = false;
	public:
		Texture(const char* filepath);
		void Bind();
		void Unbind();

		void setActive();

		const unsigned int getID() { return ID; };
		const unsigned int getSlot() { return slot - 0x84C0; };
	};

	class CubeMap
	{
	protected:
		unsigned int ID;
		int width;
		int height;
		int components;
		unsigned char* data;
		GLenum format;
		GLenum slot;

		bool bound = false;

		CubeMap();
	public:
		//must be in order: right, left, top, bottom, front, back
		CubeMap(std::vector<std::string> faces);
		CubeMap(std::string right, std::string left, std::string top, std::string bottom, std::string front, std::string back);

		void setActive();

		virtual void Bind();
		virtual void Unbind();
		const unsigned int getID() { return ID; };
		const unsigned int getSlot() { return slot - 0x84C0; };
	};

	class shadowMap : public CubeMap
	{
	private:
		unsigned int FBO;
		bool FBObound = false;
	public:
		shadowMap();

		void Bind();
		void Unbind();

		void BindFBO();
		void UnbindFBO();
	};
}