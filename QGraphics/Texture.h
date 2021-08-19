#pragma once
#include "Core.h"

extern std::vector<bool> texSlots;

namespace QG
{
	//prepares a vector to monitor which texture slots are bound
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
		//create a texture using the image at the specified path
		Texture(const char* filepath);
		//create an empty texture
		//only intended for font creation
		Texture();
		
		//binds the texture for openGl to work with
		void Bind();
		//unbinds the texture
		void Unbind();

		//assigns the texture to the first available slot
		void setActive();

		//get the ID number for the texture
		const unsigned int getID() { return ID; };
		//find which texture slot is being used
		const unsigned int getSlot() { return slot - 0x84C0; };
		//get the dimensions of the image used
		QM::vector<2, int> getSize() { return QM::vector<2, int>(width, height); };

		//double the size of the texture, only used for fonts
		void doubleSize();
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
		//create a cubeMap, a 3D texture, using a vector of image paths
		//must be in order: right, left, top, bottom, front, back
		CubeMap(std::vector<std::string> faces);
		//create a cubeMap, a 3D texture, using a set of image paths
		CubeMap(std::string right, std::string left, std::string top, std::string bottom, std::string front, std::string back);

		//assigns the texture to the first available slot
		void setActive();

		//binds the texture for openGl to work with
		virtual void Bind();
		
		//unbinds the texture
		virtual void Unbind();
		//get the ID number for the texture
		const unsigned int getID() { return ID; };
		//find which texture slot this is using
		const unsigned int getSlot() { return slot - 0x84C0; };
	};

	class shadowMap : public CubeMap
	{
	private:
		unsigned int FBO;
		bool FBObound = false;
	public:
		//create a shadowMap
		//used by light objects
		//combines a cube map with a framebuffer to record where shadows go
		shadowMap();

		//bind the texture for openGL to use
		void Bind();
		//unbind the texture
		void Unbind();

		//bind the frame buffer for openGL to use
		void BindFBO();
		//unbind the frame buffer
		void UnbindFBO();
	};
}