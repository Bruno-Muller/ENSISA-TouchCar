#ifndef CAR_H
#define CAR_H

#include "opticalblock.h"
#include "frontleftopticalblock.h"
#include "frontrightopticalblock.h"
#include "rearleftopticalblock.h"
#include "rearrightopticalblock.h"

#include "light.h"
#include "canmodul.h"
#include "canmessage.h"

class Car
{
public:
    Car();
    ~Car();
    int getLightState(int p_position, int p_light);
    Light * getLight(int p_position, int p_light);
    bool getError(int p_position, int p_mask);
    void acceptCanMessage(CanMessage p_canMessage);

private:
    OpticalBlock * m_opticalBlock[4];
    CanModul * m_canModul[4];
};

#endif // CAR_H
