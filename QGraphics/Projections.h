#pragma once

#include "Core.h"

namespace QG
{
	enum class camType
	{
		orthographic,
		perspective
	};

	class Projection : public QM::matrix<4, 4, float>
	{
	private:
		double m_fovX, m_aspect, m_near, m_far;
		camType Type;
		int Top, Bottom, Left, Right;
		void updateMatrix();
	public:
		//only for perspective projection
		Projection(double fovX, double aspect, double near, double far) : m_fovX(fovX), m_aspect(aspect), m_near(near), m_far(far),
			Type(camType::perspective), Top(0), Bottom(0), Left(0), Right(0)
		{
			updateMatrix();
		};

		//only for orthographic projection
		Projection(int left, int right, int bottom, int top, int near, int far) : Left(left), Right(right), Bottom(bottom), Top(top), m_near(near), m_far(far),
			Type(camType::orthographic), m_fovX(0), m_aspect(0)
		{
			updateMatrix();
		};

		camType getType() const { return Type; };
	};
}
