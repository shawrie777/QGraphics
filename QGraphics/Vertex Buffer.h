#pragma once
#include "Vertex.h"

namespace QG
{

	class VertexBuffer
	{
	private:
		unsigned int BufferID;
		unsigned int ArrayID;

		int state;
		bool built = false;
		std::vector<Vertex> data;
	public:
		VertexBuffer();
		VertexBuffer(std::initializer_list<Vertex> list);
		~VertexBuffer();

		void Bind();
		void Unbind();

		void Build();
		
		void push_back(Vertex v);
		Vertex& operator[](int i);
		int vertexCount();

		bool usingColour();
		bool usingTexCoords();
		bool usingNormal();

		void enableColour();
		void enableTexCoords();
		void enableNormal();

		void disableColour();
		void disableTexCoords();
		void disableNormal();

		std::vector<Vertex>::iterator begin();
		std::vector<Vertex>::iterator end();
	};

}