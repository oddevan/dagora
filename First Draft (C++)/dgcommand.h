#ifndef dgcommand_H
#define dgcommand_H

/*
    DGCommand definition
    (c) 2003 root-1 Software
*/

#include <iostream.h>

const int MAX_DGCOMMAND = 10;

enum DGCommand { ATTACK, SPECIAL, ITEM, SUMMON, RETURN, FUSE, DEFUSE, TRANSFORM, RUSH, STATUS };

ostream &operator<< (ostream &output, DGCommand &cmd);

/*DGCommand CommandFromInt(int cmd)
{
    switch (cmd)
    {
        case 0: return ATTACK;
        case 1: return SPECIAL;
        case 2: return ITEM;
        case 3: return SUMMON;
        case 4: return RETURN;
        case 5: return FUSE;
        case 6: return DEFUSE;
        case 7: return TRANSFORM;
        case 8: return LIMIT;
    }
    return ATTACK;
}*/

//#include "dgcommand.cpp"

#endif