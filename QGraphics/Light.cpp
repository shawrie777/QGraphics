#include "2Dshape.h"
#include "Light.h"

namespace lighting
{
    std::vector<QG::spotLight*> spotLights;
    std::vector<QG::pointLight*> pointLights;
    std::vector<QG::directionalLight*> directionalLights;
    std::vector<QG::areaLight*> areaLights;
}


namespace QG
{
    Light::Light() : m_col(WHITE), m_position(QM::vector<3>(0.0f,0.0f,0.0f)), m_asset(nullptr)
    {
        m_attenuation.set(3, 1.0f);
    }

    Light::~Light() {};

    Colour Light::getColour() const
    {
        return m_col;
    }

    void Light::setColour(Colour col)
    {
        m_col = col;
    }

    QM::vector<3> Light::getPosition() const
    {
        return m_position;
    }

    void Light::setPosition(QM::vector<3> pos)
    {
        m_position = pos;
    }

    Asset* Light::getAsset()
    {
        return m_asset;
    }

    void Light::setAsset(Asset* A)
    {
        m_asset = A;
    }
    void Light::removeAsset()
    {
        m_asset = nullptr;
    }
    QM::vector<3> Light::getAttenuation() const
    {
        return m_attenuation;
    }
    void Light::setAttenuation(float quadratic, float linear, float constant)
    {
        if (quadratic < 0.0f || linear < 0.0f || constant <= 0.0f)
            throw ("Invalid attenuation values.");

        m_attenuation.set(1, quadratic);
        m_attenuation.set(2, linear);
        m_attenuation.set(3, constant);
    }

    spotLight::spotLight(QM::vector<3> position, QM::vector<3> direction, float angle)
    {
        lighting::spotLights.push_back(this);

        m_col = WHITE;
        m_position = position;
        m_asset = nullptr;
        setDirection(direction);
        setAngle(angle);
        
    }

    spotLight::~spotLight()
    {
        for (auto i = lighting::spotLights.begin(); i != lighting::spotLights.end(); i++)
            if (*i == this)
            {
                lighting::spotLights.erase(i);
                break;
            }
    }

    QM::vector<3> spotLight::getDirection()
    {
        return m_direction;
    }

    void spotLight::setDirection(QM::vector<3> direction)
    {
        if (direction.magnitude() == 0)
            throw("Invalid light direction.");

        m_direction = direction.normalise();
    }
    float spotLight::getAngle()
    {
        return m_angle;
    }
    void spotLight::setAngle(float angle)
    {
        if (angle < 0.1f)
            m_angle = 0.1f;
        else if (angle > 180.0f)
            m_angle = 180.0f;
        else
            m_angle = angle;

        if (m_angle > m_outerAngle)
            setOuterAngle(m_angle);
    }
    float spotLight::getOuterAngle()
    {
        return m_outerAngle;
    }
    void spotLight::setOuterAngle(float angle)
    {
        if (angle < m_angle)
            m_outerAngle = m_angle;
        else if (angle > 180.0f)
            m_outerAngle = 180.0f;
        else
            m_outerAngle = angle;
    }

    directionalLight::directionalLight(QM::vector<3> position, QM::vector<3> direction)
    {
        lighting::directionalLights.push_back(this);

        m_col = WHITE;
        m_position = position;
        m_asset = nullptr;
        setDirection(direction);        
    }

    directionalLight::~directionalLight()
    {
        for (auto i = lighting::directionalLights.begin(); i != lighting::directionalLights.end(); i++)
            if (*i == this)
            {
                lighting::directionalLights.erase(i);
                break;
            }
    }

    QM::vector<3> directionalLight::getDirection()
    {
        return m_direction;
    }
    void directionalLight::setDirection(QM::vector<3> direction)
    {
        if (direction.magnitude() == 0)
            throw("Invalid light direction.");

        m_direction = direction.normalise();
    }
    Asset* areaLight::getArea()
    {
        return m_area;
    }

    void areaLight::setArea(Asset* shape)
    {
        if (shape2Dbase* S = dynamic_cast<shape2Dbase*>(shape))
            m_area = S;
        else
            throw ("Invalid asset for area.");
    }
    
    //must use 2D shape
    areaLight::areaLight(Asset& shape)
    {
        lighting::areaLights.push_back(this);
        m_area = &shape;
        m_col = WHITE;
        m_position = m_area->getPosition();
    }

    areaLight::~areaLight()
    {
        for (auto i = lighting::areaLights.begin(); i != lighting::areaLights.end(); i++)
            if (*i == this)
            {
                lighting::areaLights.erase(i);
                break;
            }
    }

    QM::vector<3> areaLight::getPosition() const
    {
        return m_area->getPosition();
    }

    void areaLight::setPosition(QM::vector<3> pos)
    {
        m_area->setPosition(pos);
    }

    pointLight::pointLight()
    {
        lighting::pointLights.push_back(this);
    }

    pointLight::pointLight(QM::vector<3> position)
    {
        lighting::pointLights.push_back(this);
        m_position = position;
    }

    pointLight::~pointLight()
    {
        for (auto i = lighting::pointLights.begin(); i != lighting::pointLights.end(); i++)
            if (*i == this)
            {
                lighting::pointLights.erase(i);
                break;
            }
    }
}

