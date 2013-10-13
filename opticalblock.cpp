#include "opticalblock.h"

OpticalBlock::OpticalBlock(int p_position)
{
    this->m_position = p_position;
    this->m_lights[Light::POSITION_LIGHT] = new PositionLight();
    this->m_lights[Light::BLINKER] = new TurnSignal();
}

int OpticalBlock::getPosition() {
    return this->m_position;
}

Light * OpticalBlock::getLight(int index) {
    return m_lights[index];
}
