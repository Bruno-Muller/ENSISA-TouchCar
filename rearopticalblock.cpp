#include "rearopticalblock.h"

RearOpticalBlock::RearOpticalBlock(int p_position) :
    OpticalBlock(p_position)
{
    this->m_lights[Light::STOP_LIGHT] = new StopLight();
    this->m_lights[Light::BACK_LIGHT] = new BackLight();
}
