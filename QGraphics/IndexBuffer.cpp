#include "IndexBuffer.h"

namespace QG
{
	IndexBuffer::IndexBuffer()
	{
		glGenBuffers(1, &ID);
	}

	IndexBuffer::IndexBuffer(std::initializer_list<int> input)
	{
		glGenBuffers(1, &ID);
		for (auto x : input)
			data.push_back(x);
	}

	IndexBuffer::~IndexBuffer()
	{
		glDeleteBuffers(1, &ID);
	}

	void IndexBuffer::AddIndices(std::initializer_list<int> input)
	{
		for (auto x : input)
			data.push_back(x);
	}

	void IndexBuffer::Build()
	{
		Bind();
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, count() * sizeof(unsigned int), data.data(), GL_DYNAMIC_DRAW);
	}

	void IndexBuffer::Bind()
	{
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ID);
	}

	void IndexBuffer::Unbind()
	{
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	}

	int IndexBuffer::count()
	{
		return (int)data.size();
	}
}