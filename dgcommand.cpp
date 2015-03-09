/*
    DGCommand implementation
    (c) 2003 root-1 Software
*/

#include "dgcommand.h"

ostream& operator<< (ostream& output, DGCommand& cmd)
{
    switch (cmd)
    {
        case ATTACK:
            output << "Attack";
            break;
        case SPECIAL:
            output << "Special";
            break;
        case ITEM:
            output << "Item";
            break;
        case SUMMON:
            output << "Summon";
            break;
        case RETURN:
            output << "Return";
            break;
        case FUSE:
            output << "Fuse";
            break;
        case DEFUSE:
            output << "DeFuse";
            break;
        case TRANSFORM:
            output << "Transform";
            break;
        case RUSH:
            output << "Adrenaline";
            break;
        case STATUS:
            output << "Status";
            break;
        default:
            output << "Attack";
            break;
        }
    return output << flush;
}