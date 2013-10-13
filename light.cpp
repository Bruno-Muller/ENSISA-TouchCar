#include "light.h"

Light::Light(int p_kind) :
    m_isOn(false),
    m_kind(p_kind)
{
}

void Light::setOn()
{
    this->m_isOn = true;
}

void Light::setOff()
{
    this->m_isOn = false;
}

bool Light::isOn()
{
    return this->m_isOn;
}

bool Light::isOff()
{
    return !this->m_isOn;
}

void Light::toggle()
{
    this->m_isOn = !this->m_isOn;
}

int Light::getKind()
{
    return this->m_kind;
}
