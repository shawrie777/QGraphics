#pragma once
#include "Core.h"

namespace QG
{

	class IndexBuffer
	{
	private:
		unsigned int ID;
		std::vector<unsigned int> data;
	public:
		IndexBuffer();
		IndexBuffer(std::initializer_list<int> input);
		~IndexBuffer();

		void AddIndices(std::initializer_list<int> input);
		
		void Build();
		void Bind();
		void Unbind();
		int count();
	};

}