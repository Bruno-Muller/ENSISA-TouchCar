#ifndef FRONTOPTICALBLOCK_H
#define FRONTOPTICALBLOCK_H

#include "opticalblock.h"
#include "lowbeam.h"
#include "mainbeam.h"

class FrontOpticalBlock : public OpticalBlock
{
protected:
    FrontOpticalBlock(int);
};

#endif // FRONTOPTICALBLOCK_H
