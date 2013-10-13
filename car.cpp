#include "car.h"

Car::Car()
{    
    this->m_opticalBlock[OpticalBlock::FRONT_LEFT] = new FrontLeftOpticalBlock();
    this->m_opticalBlock[OpticalBlock::FRONT_RIGHT] = new FrontRightOpticalBlock();
    this->m_opticalBlock[OpticalBlock::REAR_LEFT] = new RearLeftOpticalBlock();
    this->m_opticalBlock[OpticalBlock::REAR_RIGHT] = new RearRightOpticalBlock();

    for (int i=0; i<4; i++)
        this->m_canModul[i]= new CanModul(this->m_opticalBlock[i]);
}

Car::~Car()
{
    /* ????
    delete [] this->m_canModul;
    delete [] this->m_opticalBlock;
    */
}


int Car::getLightState(int p_position, int p_light)
{
    return this->m_canModul[p_position]->getLightState(p_light);
}

Light * Car::getLight(int p_position, int p_light)
{
    return this->m_opticalBlock[p_position]->getLight(p_light);
}

bool Car::getError(int p_position, int p_mask)
{
    return this->m_canModul[p_position]->getError(p_mask);
}

void Car::acceptCanMessage(CanMessage p_canMessage)
{
    for (int i=0; i<4; i++)
        this->m_canModul[i]->acceptCanMessage(p_canMessage);
}
