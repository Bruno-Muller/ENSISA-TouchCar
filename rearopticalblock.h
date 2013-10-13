#ifndef REAROPTICALBLOCK_H
#define REAROPTICALBLOCK_H

#include "opticalblock.h"
#include "stoplight.h"
#include "backlight.h"

class RearOpticalBlock : public OpticalBlock
{
public:
    RearOpticalBlock(int p_position);
};

#endif // REAROPTICALBLOCK_H
