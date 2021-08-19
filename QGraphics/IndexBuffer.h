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
		//create an empty index buffer
		IndexBuffer();
		//create an index buffer, immediately adding the given indices
		IndexBuffer(std::initializer_list<int> input);
		~IndexBuffer();

		//add the listed indices to the buffer
		void AddIndices(std::initializer_list<int> input);
		
		//prepare the buffer to be used by openGL
		//only use when all indices are added
		void Build();
		//bind the buffer for openGL to use
		void Bind();
		//unbind the buffer
		void Unbind();
		//the number of indices
		int count();
	};

}