#pragma once
#include "Frustum.h"

namespace QG
{
	template<int baseSides>
	class prism :public frustum<baseSides>
	{
	public:
		//special case of frustrum with ratio 1
		prism() :frustum<baseSides>(1.0f) {};
	};

	template<int baseSides>
	class pyramid :public frustum<baseSides>
	{
	public:
		//special case of frustrum with ratio 0
		pyramid() :frustum<baseSides>(0.0f) {};
	};
}