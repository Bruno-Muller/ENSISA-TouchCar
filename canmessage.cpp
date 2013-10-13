#include "canmessage.h"

CanMessage::CanMessage(int p_id, int p_dataLow, int p_dataHigh)
{
    this->m_id = p_id;
    this->m_dataLow = p_dataLow;
    this->m_dataHigh = p_dataHigh;
}

CanMessage::CanMessage(QByteArray bytes)
{
    this->m_id = (bytes.at(0)<<24) | (bytes.at(1)<<16) | (bytes.at(2)<<8) | bytes.at(3);
    this->m_dataLow = (0x0FF & bytes.at(4));
    this->m_dataHigh = (0x0FF & bytes.at(5));
}

void CanMessage::setId(int p_id)
{
    this->m_id = p_id;
}

int CanMessage::getId()
{
    return this->m_id;
}

void CanMessage::setDataLow(int p_dataLow)
{
    this->m_dataLow = p_dataLow;
}

int CanMessage::getDataLow()
{
    return this->m_dataLow;
}

void CanMessage::setDataHigh(int p_dataHigh)
{
    this->m_dataHigh = p_dataHigh;
}

int CanMessage::getDataHigh()
{
    return this->m_dataHigh;
}

int CanMessage::getLightState(int p_light)
{
    int LIGHT[4] = {0, 2, 4, 6};
    int LIGHT_MASK[4] = {0x3, 0xC, 0x30, 0xC0};
    return (this->m_dataLow & LIGHT_MASK[p_light])>>LIGHT[p_light];
}

void CanMessage::setLightState(int p_light, int p_state)
{
    int LIGHT[4] = {0, 2, 4, 6};
    int LIGHT_MASK[4] = {0x3, 0xC, 0x30, 0xC0};
    this->m_dataLow = ((this->m_dataLow & ~LIGHT_MASK[p_light]) | (p_state<<LIGHT[p_light]));
}

bool CanMessage::isUseless()
{
    if ((this->getDataHigh() == 0) && (this->getDataHigh() == 0))
        return false;
    return true;
}

QByteArray CanMessage::getBytes()
{
    QByteArray bytes;
    bytes.append((char) (this->m_id>>24));
    bytes.append((char) (this->m_id>>16));
    bytes.append((char) (this->m_id>>8));
    bytes.append((char) (this->m_id));
    bytes.append((char) this->m_dataLow);
    bytes.append((char) this->m_dataHigh);
    return bytes;
}

bool CanMessage::getError(int p_mask)
{
    if ((this->m_dataHigh & p_mask) == p_mask)
        return true;
    return false;
}
