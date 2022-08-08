#pragma once
#include "Core.h"
#include "Window.h"
#include <functional>

namespace QG
{
	class Curve
	{
	private:
		std::function<float(float)> x_func;
		std::function<float(float)> y_func;
		std::function<float(float)> z_func;
		float m_duration;
		bool m_rotate = false;
		float m_startTime = 0.0f;
		QM::vector<3> m_lastTangent;
	public:
		//create a curve as parameterised vector function, using function pointers for each component
		//each fuction should take runtime as a parameter and output a position component
		//curve can be followed indefinitely by setting duration to INFINITE
		Curve(std::function<float(float)> x, std::function<float(float)> y, std::function<float(float)> z, float duration);

		//get the position along the curve at a given time
		//by default gets position at current time
		QM::vector<3> getPosition(float t = QG::getWindow()->runtime());
		//get time at which the associated asset starts following the curve
		float startTime();
		//get time at which the associated asset stops following the curve
		float endTime();
		//get duration for which the curve is followed
		float duration();
		//check if asset should rotate as it traverses the curve
		bool rotating();
		//make asset rotate as it traverses the curve
		void setRotate(bool rotate = true);
		//get the tangent vector at a given time
		//numerical approximation, generally sufficient
		QM::vector<3> tangent(float t);
		//find how much the tangent has rotated since the previous frame
		QM::Quaternion getRotation();
		//set the time at which the object starts following the curve
		//usually the moment the curve is assigned to the asset
		void setStartTime(float time);
	};
}

namespace Curves
{
	extern std::vector<std::shared_ptr<QG::Curve>> curves;
}