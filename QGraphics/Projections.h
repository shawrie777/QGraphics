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
		//create a perspective projection matrix
		//fovX is the horizontal field of view
		Projection(double fovX, double aspect, double near, double far) : m_fovX(fovX), m_aspect(aspect), m_near(near), m_far(far),
			Type(camType::perspective), Top(0), Bottom(0), Left(0), Right(0)
		{
			updateMatrix();
		};

		//create an orthographic projection matrix
		//for simplest case, set near=-1, far=1
		Projection(int left, int right, int bottom, int top, int near, int far) : Left(left), Right(right), Bottom(bottom), Top(top), m_near(near), m_far(far),
			Type(camType::orthographic), m_fovX(0), m_aspect(0)
		{
			updateMatrix();
		};
		//check if matrix is perspective or orthographic
		camType getType() const { return Type; };

		//get field of view
		//only applies to perpective case
		double getFOV() const;
		//get aspect ratio
		double getAspect() const;
		//get distance to near plane
		double getNear() const;
		//get distance to far plane
		double getFar() const;

		//return top position
		//only applies to orthographic case
		int getTop() const;
		//return bottom position
		//only applies to orthographic case
		int getBottom() const;
		//return left position
		//only applies to orthographic case
		int getLeft() const;
		//return right position
		//only applies to orthographic case
		int getRight() const;

	};
}
