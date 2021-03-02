#include "Vertex Buffer.h"

namespace QG
{
	VertexBuffer::VertexBuffer(): state(0)
	{
		glGenBuffers(1, &BufferID);
		glGenVertexArrays(1, &ArrayID);
	}

	VertexBuffer::VertexBuffer(std::initializer_list<Vertex> list) : state(0)
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

		int memSize = 12;//4*3
		if (usingColour())
			memSize += 16;//4*4
		if (usingTexCoords())
			memSize += 8;//4*2
		if (usingNormal())
			memSize += 12;//4*1

		std::vector<float> floatData;

		for (auto& x : data)
			for (auto y : x.getFloats())
				floatData.push_back(y);


		glBufferData(GL_ARRAY_BUFFER, sizeof(float) * floatData.size(), floatData.data(), GL_DYNAMIC_DRAW);


		glEnableVertexAttribArray(attrib);
		glVertexAttribPointer(attrib, 3, GL_FLOAT, false, memSize, (const void*)offset);
		offset += 12;
		attrib++;

		if (usingColour())
		{
			glEnableVertexAttribArray(attrib);
			glVertexAttribPointer(attrib, 4, GL_FLOAT, false, memSize, (const void*)offset);
			offset += 16;
			attrib++;
		}
		if (usingTexCoords())
		{
			glEnableVertexAttribArray(attrib);
			glVertexAttribPointer(attrib, 2, GL_FLOAT, false, memSize, (const void*)offset);
			offset += 8;
			attrib++;
		}
		if (usingNormal())
		{
			glEnableVertexAttribArray(attrib);
			glVertexAttribPointer(attrib, 3, GL_FLOAT, false, memSize, (const void*)offset);
		}

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