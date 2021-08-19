#include "Curve.h"

namespace QG
{
	Curve::Curve(float(*x)(float), float(*y)(float), float(*z)(float), float duration)
	{
		x_func = x;
		y_func = y;
		z_func = z;
		m_duration = duration;
	}
	QM::vector<3> Curve::getPosition(float t)
	{
		return QM::vector<3>(x_func(t), y_func(t), z_func(t));
	}
	float Curve::startTime()
	{
		return m_startTime;
	}
	float Curve::endTime()
	{
		return m_startTime + m_duration;
	}
	float Curve::duration()
	{
		return m_duration;
	}
	bool Curve::rotating()
	{
		return m_rotate;
	}
	void Curve::setRotate(bool rotate)
	{
		m_rotate = rotate;
	}
	QM::vector<3> Curve::tangent(float t)
	{
		float epsilon = 0.1f;
		return (1.0f / (2.0f * epsilon)) * (getPosition(t + epsilon) - getPosition(t - epsilon));
	}
	QM::Quaternion Curve::getRotation()
	{
		auto tan_current = tangent(getWindow()->runtime());
		tan_current = tan_current.normalise();
		float angle = -tan_current.angle(m_lastTangent);
		auto axis = (tan_current.cross(m_lastTangent)).normalise();
		QM::Quaternion rotation = QM::rotation(angle, axis);
		m_lastTangent = tan_current;
		return rotation;
	}
	void Curve::setStartTime(float time)
	{
		m_startTime = time;
		m_lastTangent = tangent(time);
	}
}