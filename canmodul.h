#ifndef CANMODUL_H
#define CANMODUL_H

#include "canmessage.h"
#include "opticalblock.h"

class CanModul
{
public:
    CanModul(OpticalBlock * p_opticalBLock);
    OpticalBlock * getOpticalBlock();
    void acceptCanMessage(CanMessage canMessage);
    int getLightState(int light);
    bool isTarget(CanMessage canMessage);
    bool getError(int mask);

private:
    CanMessage  * m_state;
    OpticalBlock * m_opticalBlock;

};

#endif // CANMODUL_H
