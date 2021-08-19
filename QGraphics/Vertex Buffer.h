#pragma once
#include "Vertex.h"

namespace QG
{

	class VertexBuffer
	{
	private:
		unsigned int BufferID;
		unsigned int ArrayID;

		bool built = false;
		std::vector<Vertex> data;
	public:
		//creates an empty vertex buffer, a list of all vertices in an object
		VertexBuffer();
		//creates a vertex buffer, a list of all vertices in an object
		VertexBuffer(std::initializer_list<Vertex> list);
		~VertexBuffer();

		//bind the buffer for the next draw call
		void Bind();
		//unbind the buffer
		void Unbind();

		//prepare the buffer so that it is ready to draw
		void Build();
		
		//add a vertex to the buffer
		void push_back(Vertex v);
		//access the vertex at index i
		Vertex& operator[](int i);
		//how many vertices are in the buffer
		int vertexCount();

		//iterator to first element
		std::vector<Vertex>::iterator begin();
		//iterator to immediately after last element
		std::vector<Vertex>::iterator end();
	};

}