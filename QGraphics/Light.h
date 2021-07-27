#pragma once
#include "Core.h"
#include "Colour.h"
#include "Asset.h"

namespace QG
{
	class Light
	{
	protected:
		Colour m_col;
		QM::vector<3> m_position;
		Asset* m_asset = nullptr;
		QM::vector<3> m_attenuation;
		std::shared_ptr<Shader> shader;

		float shadowWidth = 1024;
		float shadowHeight = 1024;
		float shadowDepth = 25.0f;

		std::shared_ptr<Shader> getShader();

		shadowMap SM;	

	public:
		Light();
		~Light();

		Colour getColour() const;
		void setColour(Colour col);
		QM::vector<3> getPosition() const;
		virtual void setPosition(QM::vector<3> pos);
		Asset* getAsset();
		void setAsset(Asset* A);
		void removeAsset();
		QM::vector<3> getAttenuation() const;
		void setAttenuation(float quadratic, float linear, float constant);

		std::vector <QM::matrix<4, 4>> shadowTransforms;
		void fillShadowMap();
		shadowMap* getShadowMap();

		void createShadowTransform();
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
	};


}

namespace lighting
{
	extern std::vector<QG::spotLight*> spotLights;
	extern std::vector<QG::pointLight*> pointLights;
	extern std::vector<QG::directionalLight*> directionalLights;
	extern std::vector<QG::areaLight*> areaLights;
}