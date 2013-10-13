#include "frontopticalblock.h"

FrontOpticalBlock::FrontOpticalBlock(int p_position) :
    OpticalBlock(p_position)
{
    this->m_lights[Light::MAINBEAM] = new MainBeam();
    this->m_lights[Light::LOWBEAM] = new LowBeam();
}
