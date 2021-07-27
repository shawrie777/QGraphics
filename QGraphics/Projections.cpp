#include "Projections.h"

namespace QG
{
	void Projection::updateMatrix()
	{
		if (Type == camType::perspective)
		{
			this->set(1, 1, 1.0f / (float)(tan(QM::rad(m_fovX) / 2.0f)));
			this->set(2, 2, (float)m_aspect / (float)(tan(QM::rad(m_fovX) / 2.0f)));
			this->set(3, 3, ((float)m_far + (float)m_near) / ((float)m_near - (float)m_far));
			this->set(3, 4, 2 * (float)m_far * (float)m_near / ((float)m_near - (float)m_far));
			this->set(4, 3, -1.0f);
		}
		else if (Type == camType::orthographic)
		{
			this->set(1, 1, 2 / ((float)Right - (float)Left));
			this->set(1, 4, -((float)Right + (float)Left) / ((float)Right - (float)Left));
			this->set(2, 2, 2 / ((float)Top - (float)Bottom));
			this->set(2, 4, -((float)Top + (float)Bottom) / ((float)Top - (float)Bottom));
			this->set(3, 3, -2 / ((float)m_far - (float)m_near));
			this->set(3, 4, -((float)m_far + (float)m_near) / ((float)m_far - (float)m_near));
			this->set(4, 4, 1);
		}
	}

	double Projection::getFOV() const
	{
		if (Type == camType::orthographic)
			throw("Wrong projection type.");
		return m_fovX;
	}
	double Projection::getAspect() const
	{
		if (Type == camType::orthographic)
			throw("Wrong projection type.");
		return m_aspect;
	}
	double Projection::getNear() const
	{
		return m_near;
	}
	double Projection::getFar() const
	{
		return m_far;
	}
	int Projection::getTop() const
	{
		if (Type == camType::perspective)
			throw("Wrong projection type.");
		return Top;
	}
	int Projection::getBottom() const
	{
		if (Type == camType::perspective)
			throw("Wrong projection type.");
		return Bottom;
	}
	int Projection::getLeft() const
	{
		if (Type == camType::perspective)
			throw("Wrong projection type.");
		return Left;
	}
	int Projection::getRight() const
	{
		if (Type == camType::perspective)
			throw("Wrong projection type.");
		return Right;
	}
}