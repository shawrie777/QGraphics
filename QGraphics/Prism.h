#pragma once
#include "Frustum.h"

namespace QG
{
	template<int baseSides>
	class prism :public frustum<baseSides>
	{
	public:
		prism() :frustum<baseSides>(1.0f) {};
	};

	template<int baseSides>
	class pyramid :public frustum<baseSides>
	{
	public:
		pyramid() :frustum<baseSides>(0.0f) {};
	};
}