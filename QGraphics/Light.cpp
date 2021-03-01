#include "Light.h"

namespace QG
{
    Light::Light() : m_col(WHITE), m_position(QM::vector<3>(0.0f,0.0f,0.0f)), m_asset(nullptr)
    {
        m_attenuation.push_back(0.0f);
        m_attenuation.push_back(0.0f);
        m_attenuation.push_back(1.0f);        
    }

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
    std::vector<float> Light::getAttenuation() const
    {
        return m_attenuation;
    }
    void Light::setAttenuation(float quadratic, float linear, float constant)
    {
        if (quadratic < 0.0f || linear < 0.0f || constant <= 0.0f)
            throw ("Invalid attenuation values.");

        m_attenuation[0] = quadratic;
        m_attenuation[1] = linear;
        m_attenuation[2] = constant;
    }

    spotLight::spotLight(QM::vector<3> position, QM::vector<3> direction, float angle)
    {
        lights.push_back(this);

        m_col = WHITE;
        m_position = position;
        m_asset = nullptr;
        setDirection(direction);
        setAngle(angle);
        
    }

    spotLight::~spotLight()
    {
        for (auto i = lights.begin(); i != lights.end(); i++)
            if (*i == this)
            {
                lights.erase(i);
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
        lights.push_back(this);

        m_col = WHITE;
        m_position = position;
        m_asset = nullptr;
        setDirection(direction);        
    }

    directionalLight::~directionalLight()
    {
        for (auto i = lights.begin(); i != lights.end(); i++)
            if (*i == this)
            {
                lights.erase(i);
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
        m_area = &shape;
        m_col = WHITE;
        m_position = m_area->getPosition();
    }

    areaLight::~areaLight()
    {
        for (auto i = lights.begin(); i != lights.end(); i++)
            if (*i == this)
            {
                lights.erase(i);
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
        lights.push_back(this);
    }

    pointLight::pointLight(QM::vector<3> position)
    {
        lights.push_back(this);
        m_position = position;
    }

    pointLight::~pointLight()
    {
        for (auto i = lights.begin(); i != lights.end(); i++)
            if (*i == this)
            {
                lights.erase(i);
                break;
            }
    }
}