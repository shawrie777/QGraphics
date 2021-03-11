#pragma once
#include "Core.h"
#include "Colour.h"
//#include "Asset.h"

namespace QG
{
	class Light
	{
	protected:
		Colour m_col;
		QM::vector<3> m_position;
		Asset* m_asset;
		QM::vector<3> m_attenuation;


	public:
		Light();
		~Light();

		virtual Colour getColour() const;
		virtual void setColour(Colour col);
		virtual QM::vector<3> getPosition() const;
		virtual void setPosition(QM::vector<3> pos);
		virtual Asset* getAsset();
		virtual void setAsset(Asset* A);
		virtual void removeAsset();
		virtual QM::vector<3> getAttenuation() const;
		virtual void setAttenuation(float quadratic, float linear, float constant);
	};

	class spotLight : public Light
	{
	private:
		QM::vector<3> m_direction;
		float m_angle;
		float m_outerAngle;
	public:
		spotLight(QM::vector<3> position, QM::vector<3> direction, float angle);
		~spotLight();

		QM::vector<3> getDirection();
		void setDirection(QM::vector<3> direction);
		float getAngle();
		void setAngle(float angle);
		float getOuterAngle();
		void setOuterAngle(float angle);
	};

	class pointLight : public Light
	{
	public:
		pointLight();
		pointLight(QM::vector<3> position);
		~pointLight();
	};

	class directionalLight : public Light
	{
	private:
		QM::vector<3> m_direction;
	public:
		directionalLight(QM::vector<3> position, QM::vector<3> direction);
		~directionalLight();
		QM::vector<3> getDirection();
		void setDirection(QM::vector<3> direction);
	};

	class areaLight : public Light
	{
	private:
		Asset* m_area;
	public:
		Asset* getArea();
		void setArea(Asset* shape);

		//must use 2D shape
		areaLight(Asset& shape);
		~areaLight();
		QM::vector<3> getPosition() const;
		void setPosition(QM::vector<3> pos);
	};

	std::vector<spotLight*> spotLights;
	std::vector<pointLight*> pointLights;
	std::vector<directionalLight*> directionalLights;
	std::vector<areaLight*> areaLights;
}