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
		//abstract base class for all light types
		Light();
		~Light();

		//get current light colour
		Colour getColour() const;
		//set the lights colour
		void setColour(Colour col);
		//get the current position of the light
		QM::vector<3> getPosition() const;
		//set the lights position
		virtual void setPosition(QM::vector<3> pos);
		//if an asset if bound, return a pointer to it
		Asset* getAsset();
		//attach an asset to the light, an object to act as the light source
		void setAsset(Asset* A);
		//remove the attached asset
		void removeAsset();
		//get attenuation as a vector
		//attenuation is a quadratic function of distance
		//the first component is the quadratic coefficient, the second is the linear,
		//and the third is the constant
		QM::vector<3> getAttenuation() const;
		//set the attenuation over distance
		void setAttenuation(float quadratic, float linear, float constant);

		std::vector <QM::matrix<4, 4>> shadowTransforms;
		//renders the scene from the lights perspective to work out where it casts shadows
		void fillShadowMap();
		//get the map of shadows from this lights perspective
		shadowMap* getShadowMap();
		//generate the required transformation matrices to fill the shadow map
		void createShadowTransform();
	};

	class spotLight : public Light
	{
	private:
		QM::vector<3> m_direction;
		float m_angle;
		float m_outerAngle;
	public:
		//create spotlight, centered on given direction, with a spread of the given angle
		spotLight(QM::vector<3> position, QM::vector<3> direction, float angle);
		~spotLight();
		//find where the spotlight currently points
		QM::vector<3> getDirection();
		//choose where the spotlight currently points
		void setDirection(QM::vector<3> direction);
		//how wide is the beam
		float getAngle();
		//set how wide the beam is
		void setAngle(float angle);
		float getOuterAngle();
		//set an outer angle, so that the light will fade at its edges
		void setOuterAngle(float angle);
	};

	class pointLight : public Light
	{
	public:
		//create a multi-directional light
		pointLight();
		//create a multi-directional light at the given position
		pointLight(QM::vector<3> position);
		~pointLight();
	};

	class directionalLight : public Light
	{
	private:
		QM::vector<3> m_direction;
	public:
		//create a directional light with the specified position and direction
		//directional lights are for sources that are far away e.g. the sun
		directionalLight(QM::vector<3> position, QM::vector<3> direction);
		~directionalLight();
		//find which way the light currently points
		QM::vector<3> getDirection();
		//set which way the light points
		void setDirection(QM::vector<3> direction);
	};

	class areaLight : public Light
	{
	private:
		Asset* m_area;
	public:
		//get the asset which determines the area
		Asset* getArea();
		//set a different asset to be the area
		//must use a 2D shape
		void setArea(Asset* shape);

		//area light is light from a screen or other object
		//must use a 2D shape
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