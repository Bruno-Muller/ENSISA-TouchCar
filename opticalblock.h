#ifndef OPTICALBLOCK_H
#define OPTICALBLOCK_H

#include "light.h"
#include "turnsignal.h"
#include "positionlight.h"

class OpticalBlock
{
public:
    static int const FRONT_LEFT = 0;
    static int const FRONT_RIGHT = 1;
    static int const REAR_LEFT = 2;
    static int const REAR_RIGHT = 3;

    int getPosition();
    Light * getLight(int index);

protected:
    Light * m_lights[4];

    OpticalBlock(int);

private:
    int m_position;

};

#endif // OPTICALBLOCK_H
