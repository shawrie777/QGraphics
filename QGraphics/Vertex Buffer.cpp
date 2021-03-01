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

		for (auto& x : data)
		{
			state = std::max(state, x.state);
		}

		_int64 offset = 0;
		int attrib = 0;

		int memSize = 12;
		if (usingColour())
			memSize += 16;
		if (usingTexCoords())
			memSize += 8;
		if (usingNormal())
			memSize += 12;

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

		if (state > v.state)
		{
			if (usingColour() && !v.usingColour())
				v.setColour(GREY);
			if (usingTexCoords() && !v.usingTexCoords())
				v.setTexCoords(QM::vector<2>(0.0f, 0.0f));
			if (usingNormal() && !v.usingNormal())
				v.setNormal(QM::vector<3>(0.0f, 0.0f, 0.0f));
		}
		else if (state < v.state)
		{
			if (!built)
			{
				if (!usingColour() && v.usingColour())
					enableColour();
				if (!usingTexCoords() && v.usingTexCoords())
					enableTexCoords();
				if (!usingNormal() && v.usingNormal())
					enableNormal();
			}
			else
			{
				if (!usingColour() && v.usingColour())
					v.disableColour();
				if (!usingTexCoords() && v.usingTexCoords())
					v.disableTexCoords();
				if (!usingNormal() && v.usingNormal())
					v.disableNormal();
			}
		}
		state = built ? state : std::max(state, v.state);

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

	bool VertexBuffer::usingColour()
	{
		return state > 3;
	}
	bool VertexBuffer::usingTexCoords()
	{
		return state % 4 > 1;
	}
	bool VertexBuffer::usingNormal()
	{
		return state % 2 == 1;
	}

	void VertexBuffer::enableColour()
	{
		if (!usingColour() && !built)
			state += 4;
		for (auto& x : data)
			x.setColour(GREY);
	}

	void VertexBuffer::enableTexCoords()
	{
		if (!usingTexCoords() && !built)
			state += 2;
		for (auto& x : data)
			x.setTexCoords(QM::vector<2>(0.0f, 0.0f));
	}

	void VertexBuffer::enableNormal()
	{
		if (!usingNormal() && !built)
			state += 1;
		for (auto& x : data)
			x.setNormal(QM::vector<3>(0.0f, 0.0f, 0.0f));
	}

	void VertexBuffer::disableColour()
	{
		if(!built)
			state -= 4;

		for (auto& x : data)
			x.disableColour();
	}

	void VertexBuffer::disableTexCoords()
	{
		if (!built)
			state -= 2;

		for (auto& x : data)
			x.disableTexCoords();
	}
	void VertexBuffer::disableNormal()
	{
		if (!built)
			state -= 1;

		for (auto& x : data)
			x.disableNormal();
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