#include "Vertex Buffer.h"

namespace QG
{
	VertexBuffer::VertexBuffer()
	{
		glGenBuffers(1, &BufferID);
		glGenVertexArrays(1, &ArrayID);
	}

	VertexBuffer::VertexBuffer(std::initializer_list<Vertex> list)
	{
		glGenBuffers(1, &BufferID);
		glGenVertexArrays(1, &ArrayID);
		for (auto& x : list)
			push_back(x);
	}

	VertexBuffer::~VertexBuffer()
	{
		glDeleteBuffers(1, &BufferID);
		glDeleteVertexArrays(1, &ArrayID);
	}

	void VertexBuffer::Bind()
	{
		glBindBuffer(GL_ARRAY_BUFFER, BufferID);
		glBindVertexArray(ArrayID);
	}

	void VertexBuffer::Unbind()
	{
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindVertexArray(0);
	}

	void VertexBuffer::Build()
	{
		if (built)
			return;

		Bind();

		_int64 offset = 0;
		int attrib = 0;

		int memSize = 32;//4*(3 pos + 2 texCoord + 3 norm)

		std::vector<float> floatData;

		for (auto& x : data)
			for (auto y : x.getFloats())
				floatData.push_back(y);


		glBufferData(GL_ARRAY_BUFFER, sizeof(float) * floatData.size(), floatData.data(), GL_STATIC_DRAW);


		glEnableVertexAttribArray(attrib);
		glVertexAttribPointer(attrib, 3, GL_FLOAT, false, memSize, (const void*)offset);
		offset += 12;
		attrib++;

		//tex coords
		glEnableVertexAttribArray(attrib);
		glVertexAttribPointer(attrib, 2, GL_FLOAT, false, memSize, (const void*)offset);
		offset += 8;
		attrib++;
		
		//normal
		glEnableVertexAttribArray(attrib);
		glVertexAttribPointer(attrib, 3, GL_FLOAT, false, memSize, (const void*)offset);
		

		built = true;

	}

	void VertexBuffer::push_back(Vertex v)
	{
		data.push_back(v);
	}

	Vertex& VertexBuffer::operator[](int i)
	{
		return data[i];
	}

	int VertexBuffer::vertexCount()
	{
		return (int)data.size();
	}

	std::vector<Vertex>::iterator VertexBuffer::begin()
	{
		return data.begin();
	}

	std::vector<Vertex>::iterator VertexBuffer::end()
	{
		return data.end();
	}
}