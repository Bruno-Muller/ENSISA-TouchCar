#include "canmodul.h"

CanModul::CanModul(OpticalBlock  * p_opticalBlock)
{
    int MASK[] = {CanMessage::FRONT_LEFT, CanMessage::FRONT_RIGHT, CanMessage::REAR_LEFT, CanMessage::REAR_RIGHT};

    this->m_opticalBlock = p_opticalBlock;
    this->m_state = new CanMessage(MASK[m_opticalBlock->getPosition()], CanMessage::ALL_OFF, 0);
}

OpticalBlock * CanModul::getOpticalBlock()
{
    return this->m_opticalBlock;
}

void CanModul::acceptCanMessage(CanMessage canMessage)
{
    if (isTarget(canMessage))
    {
        for (int i=0; i<4; i++) {
            switch (canMessage.getLightState(i))
            {
            case CanMessage::LIGHT_OFF:
                this->m_state->setLightState(i, CanMessage::LIGHT_OFF);
                this->m_opticalBlock->getLight(i)->setOff();
                break;
            case CanMessage::LIGHT_ON:
                this->m_state->setLightState(i, CanMessage::LIGHT_ON);
                this->m_opticalBlock->getLight(i)->setOn();
                break;
            case CanMessage::LIGHT_BLINKING:
                this->m_state->setLightState(i, CanMessage::LIGHT_BLINKING);
                this->m_opticalBlock->getLight(i)->setOn();
                break;
            }
        }
        if (this->m_state->getDataHigh() != (canMessage.getDataHigh() & 0xFC))
            this->m_state->setDataHigh(canMessage.getDataHigh() & 0xFC);
    }
}

int CanModul::getLightState(int light)
{
    return this->m_state->getLightState(light);
}

bool CanModul::isTarget(CanMessage canMessage)
{
    if ((canMessage.getId() & this->m_state->getId()) == this->m_state->getId())
        return true;
    return false;
}

bool CanModul::getError(int mask)
{
    return this->m_state->getError(mask);
}
